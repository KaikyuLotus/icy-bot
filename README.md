# IcyBot

This is just a small training project and it's not intended for everyday use.

I'm focusing on code beauty as much as possible to be honest.

Take a look at this:

```c++
void helloWorld(Bot bot, Update update, std::vector<std::string> args) {
	int messageID = update.message.messageID;
	int chatID = update.message.chat.chatID;

	bot.sendChatAction(chatID, TYPING);

	bot.sendMessage(chatID, "*Hello World*")
		.add(Arguments::parseMode, Arguments::markdown)
		.add(Arguments::replyToMessage, messageID)
		.fire();
}

int main() {
	// Initialize your bot
	Bot bot = Bot("TOKEN");
	// Add a function in response to a /command
	bot.addCommandHandler("helloWorld", &helloWorld);
	// Start getting updates!
	bot.startPolling();
}
```

It's beautiful, isn't it?


## Dependencies
[cURL](https://github.com/curl/curl)

[JSON for Modern C++](https://github.com/nlohmann/json)



**Notice**:

I'm **new** to C++ 
