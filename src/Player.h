#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
	Player(int id, std::string name);
	Player();
	int getId();
	std::string getName();
	std::string getPicturePath();
private:
	int id;
	int wins;
	int losses;
	std::string name;
	std::string picturePath;
};

#endif