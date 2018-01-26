#pragma once

class Photo {

public:
	std::string photoID;

	int fileSize{ 0 };
	int width{ 0 };
	int height{ 0 };

	Photo() {}

	Photo(json photo) {
		photoID = photo["file_id"].get<std::string>();
		fileSize = photo["file_size"].get<int>();
		width = photo["width"].get<int>();
		height = photo["height"].get<int>();
	}

};