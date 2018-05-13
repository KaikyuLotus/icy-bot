# IcyBot

**This is just a small training project and it's not intended for everyday use.**
Please feel free to give me some tips.
This is my first "big" C++ project.

## Examples

### Hello World Command
```c++
void helloWorld(Bot* bot, Update update) {
	int messageID = update.message.messageID;
	int chatID = update.message.chat.chatID;

	bot->sendChatAction(chatID, TYPING).fire();

	bot->sendMessage(chatID, "*Hello World*")
		.add(Arguments::parseMode, Arguments::markdown)
		.add(Arguments::replyToMessage, messageID)
		.fire();
}

int main() {
	// Initialize your bot
	Bot bot = Bot("TOKEN");
	
	// Add a function in response to /helloWorld
	bot.addCommandHandler("helloWorld", &helloWorld);
	
	// Start getting updates!
	bot.startPolling();
	
	bot.idle();
}
```

### Echo Bot
```c++
void updateHandler(Bot* bot, Update update) {
	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();
	bot->sendMessage(update.message.chat.chatID, update.message.text).fire();
}

int main() {
	Bot bot = Bot("TOKEN");
	
	// Add the updates handler, this handler will receive every update
	bot->setUpdateHandler(&updateHandler);
	
	bot.startPolling();
	bot.idle();
	
	return 0;
}
```

### Multiple Bots
```c++
// Sample function
void start(Bot* bot, Update update) {
	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();
	bot->sendMessage(update.message.chat.chatID, "Start!").fire();
}

int main() {
	// Initialize your bots
	Bot bot1 = Bot("TOKEN1");
	Bot bot2 = Bot("TOKEN2");
	
	// Add your commands-functions
	bot1.addCommandHandler("start", &start);
	bot2.addCommandHandler("start", &start);
	
	// Start getting updates with both bots!
	bot1.startPolling();
	bot2.startPolling();

	bot1.idle();
	
	return 0;
}
```

### Handle Errors
```c++
void errorHandler(Bot* bot, Update update, std::string func, std::string error) {
	Log::Error("Handled error: '" + error + "' in command '" + func + "'");
	Log::Debug("Last error has been caused by:\n'" + update.update_json.dump(2) + "'");
}

// Sample function
void generateError(Bot* bot, Update update) {
	bot->sendChatAction(update.message.chat.chatID, TYPING).fire();
	bot->sendMessage(update.message.chat.chatID, "Generating error...").fire();
	
	// throw a test error
	throw std::overflow_error("Divide by zero exception");
}

int main() {
	Bot bot = Bot("TOKEN");
	bot.addCommandHandler("generateError", &generateError);
	
	// Add our error handler
	bot.addErrorHandler(&errorHandler);
	
	bot.startPolling();
	bot.idle();
	
	return 0;
}
```

## Dependencies
[cURL](https://github.com/curl/curl)

[JSON for Modern C++](https://github.com/nlohmann/json)



**Notice**:

I'm **new** to C++ 
