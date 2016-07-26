#pragma once

#include <cpr\cpr.h>
#include <string>

class AniListParser {
public:
	AniListParser();//init the token
	std::string getCharacterImg(std::string charName);
	void renewToken();//TODO somehow know when to renew token. Create a timer/sleep 

private:
	std::string token;
	std::string clientId;
	std::string clientSecrete;
	int renewTime;


};