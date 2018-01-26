#pragma once

class User {
public:
	long long userID{0};

	std::string name{ "" };
	std::string last_name{ "" };

	User(json user) {
		userID = user["id"].get<long long>();
		name = user["first_name"].get<std::string>();

		if (std::find(user.begin(), user.end(), "last_name") != user.end()) {
			last_name = user["last_name"].get<std::string>();
		}
	}

	User() {};
};