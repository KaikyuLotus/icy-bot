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

        std::string name{};
        std::string username{};

        explicit Bot(const std::string &token) {
            if (token.empty()) {
                throw Errors::TokenException("'" + token + "' is not a valid token.", token);
            }

            this->botToken = token;

            Log::Debug("Executing first get me");
            auto response = execute(&GetMe());

            if (!response.ok) {
                throw Errors::TokenException("'" + token + "' is not a valid token.", token);
            }

            this->name = response.result.firstName;
            this->username = response.result.username;

            Log::Info(std::string{"bot " + name + " started."});
        }

        void addCommandHandler(const std::string &command,
                               void(*commandHandler)(const Bot *bot, const Update *update,
                                                     std::vector<std::string> args)) {
            Log::Debug("Adding a command handler with args to the command " + command);
            commandHandlersArgs.emplace_back(command, commandHandler);
        }

        // I get a Function is not implemented here, but it is...
        void addCommandHandler(const std::string &command, void (*commandHandler)(const Bot *bot, const Update *update)) {
            Log::Debug("Adding a command handler to the command " + command);
            commandHandlers.emplace_back(command, commandHandler);
        }

        void setUpdateHandler(void(*updateHandler)(const Bot *bot, const Update *update)) {
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

        /// Executes a BaseMethod and returns BaseResponse<T> depending on the method
        /// \tparam T
        /// \param method
        /// \return
        template<typename T>
        BaseResponse<T> execute(BaseMethod<BaseResponse<T>>* method) const {
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

    private:
        // Used for executing requests
        Requests requester = Requests();

        bool shouldStop{false};

        std::string botToken;
        std::string commandSymbol{"/"};

        std::vector<std::pair<std::string, void (*)(const Bot*, const Update*, std::vector<std::string>)>> commandHandlersArgs{
                std::vector<std::pair<std::string, void (*)(const Bot*, const Update*, std::vector<std::string>)>>()
        };

        std::vector<std::pair<std::string, void (*)(const Bot*, const Update*)>> commandHandlers{
                std::vector<std::pair<std::string, void (*)(const Bot*, const Update*)>>()
        };

        void (*updateHandlerFoo)(const Bot *bot, const Update* update) {nullptr};

        void cleanUpdates() {
            // Telegram gives us only the last update using -1
            auto updates = execute(GetUpdates().offset(-1)).result;

            Log::Debug("Calculating clean offset");
            offset = updates.empty() ? 0 : updates.back().updateId + 1;
        }

        void _startPolling() {
            Log::Debug("Starting polling for bot @" + username);
            std::thread updater(&Bot::_pollingTask, this);
            updater.detach();
        }

        void _handleUpdate(Update *update) {
            if (!Utils::startsWith(update->message.text, "/")) {
                if (updateHandlerFoo != nullptr) {
                    updateHandlerFoo(this, update);
                }
                return;
            }

            std::vector<std::string> parts = Utils::split(update->message.text);

            for (const auto &commandHandler : commandHandlers) {
                if (commandSymbol + commandHandler.first != parts[0]) continue;
                commandHandler.second(this, update);
                Log::Debug("@" + update->message.user.username + " used '" + commandHandler.first + "'");
                return;
            }

            for (const auto &commandHandlersWithArgs : commandHandlersArgs) {
                if (commandSymbol + commandHandlersWithArgs.first != parts[0]) continue;

                commandHandlersWithArgs.second(this, update, parts);
                Log::Debug("@" + update->message.user.username + " used '" + commandHandlersWithArgs.first + "'");
                return;
            }
        }

        void elaborateUpdates(const std::vector<Update>& updates) {
            for (Update update : updates) {
                offset = update.updateId + 1;

                try {
                    auto bench = Utils::benchmarkVoid([&]() {
                        _handleUpdate(&update);
                    });
                    Log::Debug("update #" + std::to_string(update.updateId) + " handled in " + std::to_string(bench.second) + " ns");
                } catch (std::exception &e) {
                    Log::Error(e.what());
                    continue;
                } catch (...) {
                    Log::Error("Critical error!");
                    continue;
                }
            }
        }

        void _pollingTask() {
            while (!shouldStop) {
                try { // Scope
                    auto resp = execute(GetUpdates().timeout(120)->offset(offset)).result;
                    elaborateUpdates(resp);
                } catch (std::exception &exc) {
                    Log::Error("Exception in the polling task: " + std::string(exc.what()));
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                } catch (...) {
                    Log::Error("Critical error! Exiting...");
                    return;
                }
            }
        }
    };
}