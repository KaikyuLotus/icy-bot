#pragma once

class Update {

public:

	long updateID{ 0 };
	Message message;

	Update(json update) {
		updateID = update["update_id"].get<long>();
		message = Message(update["message"].get<json>());
	}
};