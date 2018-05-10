#pragma once
class Sticker {
public:
	std::string fileID;
	std::string emoji;
	std::string setName;

	int fileSize;
	int height;
	int width;

	Sticker() { }

	Sticker(json sticker) {
		emoji = sticker["emoji"].get<std::string>();
		fileID = sticker["file_id"].get<std::string>();

		fileSize = sticker["file_size"].get<int>();
		height = sticker["height"].get<int>();
		width = sticker["width"].get<int>();
		setName = sticker["set_name"].get<std::string>();
	}
};