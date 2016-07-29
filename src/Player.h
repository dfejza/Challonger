#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
	Player(int id, std::string name, std::string url, std::string path);
	Player();
	int getId();
	std::string getName();
	std::string getPicturePath();
	void setPicturePath(std::string pPath);
private:
	int id;
	int wins;
	int losses;
	std::string name;
	std::string pictureUrl;
	std::string picturePath;
};

#endif