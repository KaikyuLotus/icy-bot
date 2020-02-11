#include <string>
#include <entities/methods/GetMe.hpp>
#include <entities/Update.hpp>
#include <core/Bot.hpp>
#include <entities/methods/SendMessage.hpp>
#include <entities/methods/SendPhoto.hpp>
#include <utils/Utils.hpp>

#include <cpprest/http_client.h>

using namespace CppTelegramBots;

void updateHandler(const Bot *bot, const Update *update) { }

void start(const Bot *bot, const Update *update) {

    std::string text = "Hello " + update->message.user.firstName;
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;

    BaseResponse<Message> response = bot->execute(SendMessage(toChat, text.c_str()).replyToMessageId(messageId));
    if (!response.ok) {
        Log::Error("Could not send message: " + response.description);
    }

}


void sendMessage(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    BaseResponse<Message> resp = bot->execute(SendMessage(toChat, "Test: [Google](http://www.google.it/)")
                                                      .replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendPhotoFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    std::string imageData = Utils::readFullFile("resources/images/uhd_test.jpg");
    BaseResponse<Message> resp = bot->execute(SendPhoto(toChat, InputFile("uhd_test.jpg", &imageData))
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

int main() {

    std::string tokenString = Utils::readStringFile("resources/token.txt");
    if (tokenString.empty()) {
        Log::Error("Token file was not found or probably empty.");
        return 3;
    }

    Bot *currentBot;

    try {
        // Create your bot!
        currentBot = new Bot(tokenString);
    } catch (Errors::RequestsException &exc) {
        Log::Error("Exception while creating bot: " + std::string(exc.what()));
        return 1;
    } catch (std::exception &exc) {
        Log::Error("Exception while creating bot: " + std::string(exc.what()));
        return 2;
    } catch (...) {
        Log::Error("Unknown fatal exception while creating bot");
        return 3;
    }

    // Add the updates handler, this handler will receive every update
    currentBot->setUpdateHandler(&updateHandler);

    // Add some handlers
    currentBot->addCommandHandler("start", &start);
    currentBot->addCommandHandler("snd", &sendMessage);
    currentBot->addCommandHandler("imgf", &sendPhotoFile);

    // Start polling updates
    currentBot->startPolling(true);

    /* startPolling is not blocking
       So we need to do something or the program will close
       If you don't have a blocking function to execute then just call idle() */
    currentBot->idle();

    return 0;
}