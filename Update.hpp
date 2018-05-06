#pragma once

class Update {

public:

	long updateID{ 0 };
	Message message;
	Message replyTo;

	Update(json update) {
		updateID = update["update_id"].get<long>();
		message = Message(update["message"].get<json>());
		if (message.isReply) {
			replyTo = Message(update["message"].get<json>()["reply_to_message"].get<json>());
		}
	}
};