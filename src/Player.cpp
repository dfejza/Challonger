#include "Player.h"

Player::Player(int id, std::string name)
{
	this->id = id;
	this->name = name;
}

Player::Player()
{
	this->id = 0;
	this->name = "";
}

int Player::getId()
{
	return this->id;
}

std::string Player::getName()
{
	return this->name;
}

std::string Player::getPicturePath()
{
	return this->picturePath;
}

void Player::setPicturePath(std::string pPath)
{
	this->picturePath = pPath;
}
