#pragma once

#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <map>
#include <json.hpp>
#include <entities/methods/BaseMethod.hpp>
#include <entities/methods/GetMe.hpp>
#include <entities/methods/GetUpdates.hpp>
#include <core/Requests.hpp>

#include "utils/Errors.hpp"
#include "utils/Utils.hpp"
#include "utils/Log.hpp"
#include "entities/BaseResponse.hpp"
#include "entities/Chat.hpp"
#include "entities/User.hpp"
#include "entities/Sticker.hpp"
#include "entities/Photo.hpp"
#include "entities/Message.hpp"
#include "entities/Update.hpp"
#include "RequestResult.hpp"

namespace CppTelegramBots {

    static bool stopProgram = false;

    class Bot {
    public:
        long offset{};

        long long ID{};
        std::string name{};
        std::string username{};

        explicit Bot(const std::string &token) {
            this->botToken = token;

            Log::Debug("Executing first get me");
            auto response = execute(GetMe());

            if (!response.ok) {
                throw Errors::TokenException("'" + token + "' is not a valid token.", token);
            }

            this->ID = response.result.id;
            this->name = response.result.firstName;
            this->username = response.result.username;

            Log::Info(std::string{"bot " + name + " started."});
        }

        void addCommandHandler(const std::string &command,
                               void(*commandHandler)(Bot *bot, const Update &update,
                                                     std::vector<std::string> args)) {
            Log::Debug("Adding a command handler with args to the command " + command);
            commandHandlersArgs.emplace_back(command, commandHandler);
        }

        // I get a Function is not implemented here, but it is...
        void addCommandHandler(const std::string &command, void (*commandHandler)(Bot *bot, const Update &update)) {
            Log::Debug("Adding a command handler to the command " + command);
            commandHandlers.emplace_back(command, commandHandler);
        }

        void setErrorHandler(void(*errorHandler)(Bot *bot, const Update &update, const std::string &func, const std::string &error)) {
            errorHandlerFoo = errorHandler;
        }

        void setUpdateHandler(void(*updateHandler)(Bot *bot, const Update &update)) {
            updateHandlerFoo = updateHandler;
        }

        void startPolling(bool clean) {
            if (clean) cleanUpdates();
            _startPolling();
        }

        void stopPolling() {
            if (shouldStop) {
                Log::Warn("bot " + name + " already stopped.");
                return;
            }
            shouldStop = true;
            Log::Info("bot " + name + " stopped.");
        }

        void idle() {
            while (!shouldStop) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                if (stopProgram) {
                    stopPolling();
                }
            }

            // Tell to Telegram that we've read the last update before closing
            execute(GetUpdates().offset(offset));
        }

        void defaultUpdateHandlerFoo(Bot *bot, const Update &update) {
            Log::Debug("Unhandled update #" + std::to_string(update.updateId));
        }

        void defaultErrorHandlerFoo(Bot *bot, const Update &update, const std::string &func,
                                    const std::string &error) {
            // Log::Error("update '" + update.update_json.dump() + "' caused error " + error + " (in command '" + func + "')");
        }

        int getElapsedTime() {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::steady_clock::now() - updateStartTime).count();
        }

        /// Executes a BaseMethod and returns BaseResponse<T> depending on the method
        /// \tparam T
        /// \param method
        /// \return
        template<typename T>
        BaseResponse<T> execute(BaseMethod<BaseResponse<T>> method) {
            try {
                Log::Debug("Starting request execution");
                auto resp = requester.fire(method, botToken.c_str()).as_json();
                if (!resp.ok) {
                    Log::Warn("Request not ok: " + resp.description);
                }
                return resp;
            } catch (const std::exception &exce) {
                Log::Error("Error in the request: " + std::string(exce.what()));
                throw exce;
            } catch (const std::string &exce) {
                Log::Error("String error in the request: " + exce);
                throw exce;
            } catch (...) {
                Log::Error("Critical error in the request");
                throw Errors::ExecutorException("Critical error in the request");
            }
        }

        /// Usefull for executing a BaseMethod without checking the BaseResult
        /// \tparam T
        /// \param method
        /// \return
        template<typename T>
        T fire(BaseMethod<BaseResponse<T>> method) {
            return execute(method).result;
        }


    private:
        // Used for executing requests
        Requests requester = Requests();

        bool shouldStop{false};

        std::string botToken;
        std::string commandSymbol{"/"};

        std::chrono::steady_clock::time_point updateStartTime;

        std::vector<std::pair<std::string, void (*)(Bot *, const Update &,
                                                    std::vector<std::string>)>> commandHandlersArgs{
                std::vector<std::pair<std::string, void (*)(Bot *, const Update &,
                                                            std::vector<std::string>)>>()
        };

        std::vector<std::pair<std::string, void (*)(Bot *, const Update &)>> commandHandlers{
                std::vector<std::pair<std::string, void (*)(Bot *, const Update &)>>()
        };

        void (*updateHandlerFoo)(Bot *bot, const Update &update) {nullptr};

        void
        (*errorHandlerFoo)(Bot *bot, const Update &update, const std::string &func,
                           const std::string &error) {
                nullptr};

        void cleanUpdates() {
            // Telegram gives us only the last update using -1
            auto updates = execute(GetUpdates().offset(-1)).result;

            Log::Debug("Calculating clean offset");
            offset = updates.empty() ? 0 : updates.back().updateId + 1;
        }

        void _startPolling() {
            Log::Debug("Starting polling for bot @" + username);
            std::thread updater(&Bot::pollingTask, this);
            updater.detach();
        }

        void handleUpdate(Update *update) {
            std::string functionExecuted = "unknown";

            try {

                if (!startsWith(update->message.text, "/")) {
                    functionExecuted = "updateHandler";
                    if (updateHandlerFoo == nullptr)
                        defaultUpdateHandlerFoo(this, *update);
                    else
                        updateHandlerFoo(this, *update);
                    return;
                }

                std::vector<std::string> parts = split(update->message.text);

                for (const auto &commandHandler : commandHandlers) {
                    if (commandSymbol + commandHandler.first != parts[0]) continue;

                    functionExecuted = commandHandler.first;
                    commandHandler.second(this, *update);
                    Log::Debug("@" + update->message.user.username + " used '" + commandHandler.first + "'");
                    return;
                }

                for (const auto &commandHandlersWithArgs : commandHandlersArgs) {
                    if (commandSymbol + commandHandlersWithArgs.first != parts[0]) continue;

                    functionExecuted = commandHandlersWithArgs.first;
                    commandHandlersWithArgs.second(this, *update, parts);
                    Log::Debug(
                            "@" + update->message.user.username + " used '" + commandHandlersWithArgs.first +
                            "'");
                }

                // Catch all std::exceptions
            } catch (const std::exception &e) {
                Log::Error("Unknown exception during the update handling: " + std::string(e.what()));
//            if (errorHandlerFoo == NULL)
//                defaultErrorHandlerFoo(this, update->update_json.get<nlohmann::json>(), functionExecuted, e.what());
//            else
//                errorHandlerFoo(this, update->update_json.get<nlohmann::json>(), functionExecuted, e.what());

                // Catch any other error
            } catch (...) {
                Log::Error("Critical exception during the update handling");
//            if (errorHandlerFoo == NULL)
//                defaultErrorHandlerFoo(this, update->update_json.get<nlohmann::json>(), functionExecuted,
//                                       "Unknown error...");
//            else
//                errorHandlerFoo(this, update->update_json.get<nlohmann::json>(), functionExecuted, "Unknown error...");
            }
        }

        void elaborateUpdates(const std::vector<Update>& updates) {
            for (Update update : updates) {
                offset = update.updateId + 1;

                try {
                    updateStartTime = std::chrono::steady_clock::now();
                    handleUpdate(&update);
                    auto end = std::chrono::steady_clock::now();
                    auto elaps = std::chrono::duration_cast<std::chrono::nanoseconds>(end - updateStartTime);
                    Log::Debug(
                            "update #" + std::to_string(update.updateId) + " handled in " +
                            std::to_string(elaps.count()) +
                            " ns");
                } catch (std::exception &e) {
                    Log::Error(e.what());
                    continue;
                } catch (...) {
                    Log::Error("Critical error!");
                    continue;
                }
            }
        }

        void pollingTask() {
            while (!shouldStop) {
                try { // Scope
                    auto resp = execute(GetUpdates().timeout(120).offset(offset)).result;
                    elaborateUpdates(resp);
                } catch (std::exception &exc) {
                    Log::Error("Exception " + std::string(exc.what()));
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                } catch (...) {
                    Log::Error("Critical error! Exiting...");
                    return;
                }
            }
        }
    };
}