#include <string>
#include <entities/methods/GetMe.hpp>
#include <entities/Update.hpp>
#include <core/Bot.hpp>
#include <entities/methods/SendMessage.hpp>
#include <entities/methods/SendPhoto.hpp>
#include <utils/Utils.hpp>
#include <entities/methods/SendAudio.hpp>
#include <entities/methods/SendDocument.hpp>
#include <entities/methods/SendVideo.hpp>
#include <entities/methods/SendAnimation.hpp>
#include <entities/methods/SendVoice.hpp>
#include <entities/methods/SendVideoNote.hpp>
#include <entities/methods/ForwardMessage.hpp>

using namespace CppTelegramBots;

void updateHandler(const Bot *bot, const Update *update) {
    Log::Debug("New update from " + update->message.user.firstName);
}

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

void forwardMessage(const Bot *bot, const Update *update) {
    long long fromChat = update->message.chat.id;
    long messageId = update->message.messageId;
    BaseResponse<Message> resp = bot->execute(ForwardMessage(fromChat, fromChat, messageId)
                                                      .disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendPhotoFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    std::string data = Utils::readFullFile("resources/test-media/uhd_test.jpg");
    BaseResponse<Message> resp = bot->execute(SendPhoto(toChat, InputFile("uhd_test.jpg", &data))
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendAudioFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    std::string data = Utils::readFullFile("resources/test-media/audio.ogg");
    BaseResponse<Message> resp = bot->execute(SendAudio(toChat, InputFile("audio.ogg", &data))
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendVoiceFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    std::string data = Utils::readFullFile("resources/test-media/audio.ogg");
    BaseResponse<Message> resp = bot->execute(SendVoice(toChat, InputFile("audio.ogg", &data))
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendDocumentFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    std::string data = Utils::readFullFile("resources/test-media/payload.zip");
    BaseResponse<Message> resp = bot->execute(SendDocument(toChat, InputFile("payload.zip", &data))
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendVideoFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    std::string data = Utils::readFullFile("resources/test-media/video.mp4");
    BaseResponse<Message> resp = bot->execute(SendVideo(toChat, InputFile("video.mp4", &data))
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendVideoNoteFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    std::string data = Utils::readFullFile("resources/test-media/video.mp4");
    BaseResponse<Message> resp = bot->execute(SendVideoNote(toChat, InputFile("video.mp4", &data))
                                                      .replyToMessageId(messageId)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void sendAnimationFile(const Bot *bot, const Update *update) {
    long long toChat = update->message.chat.id;
    long messageId = update->message.messageId;
    std::string data = Utils::readFullFile("resources/test-media/video.mp4");
    BaseResponse<Message> resp = bot->execute(SendAnimation(toChat, InputFile("video.mp4", &data))
                                                      .caption("Test: [Google](http://www.google.it/)")
                                                      ->replyToMessageId(messageId)
                                                      ->parseMode(Enums::ParseMode::MARKDOWN)
                                                      ->disableNotification()
                                                      ->disableWebPagePreview());
    if (!resp.ok) Log::Error(resp.description);
}

void executeBot(const std::string& token) {
    // Create your bot!
    Bot *currentBot = new Bot(token);

    // Add the updates handler, this handler will receive every update
    currentBot->setUpdateHandler(&updateHandler);

    // Add some handlers
    currentBot->addCommandHandler("start", &start);
    currentBot->addCommandHandler("snd", &sendMessage);
    currentBot->addCommandHandler("fwd", &forwardMessage);
    currentBot->addCommandHandler("imgf", &sendPhotoFile);
    currentBot->addCommandHandler("audf", &sendAudioFile);
    currentBot->addCommandHandler("docf", &sendDocumentFile);
    currentBot->addCommandHandler("vidf", &sendVideoFile);
    currentBot->addCommandHandler("anif", &sendAnimationFile);
    currentBot->addCommandHandler("voif", &sendVoiceFile);
    currentBot->addCommandHandler("vdnf", &sendVideoNoteFile);

    // Start polling updates
    currentBot->startPolling(true);

    /* startPolling is not blocking
       So we need to do something or the program will close
       If you don't have a blocking function to execute then just call idle() */
    currentBot->idle();
}

int main() {
    try {
        std::string token = Utils::getEnv("BOT_TOKEN");
        executeBot(token);
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
    return 0;
}