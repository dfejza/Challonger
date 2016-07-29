
#include <json.hpp>
#include <iostream>
#include <string>
#include <map>
#include "Player.h"
#include "AniListParser.h"
#include "ImageManager.h"

using json = nlohmann::json;

//lets use hashtable for now, not threaded atm
class PlayerDatabase{
public:
  PlayerDatabase(json o);
  void createDatabase(json o);
  void getPlayer(int participantId, Player** player);
private:
  //g++ -std=c++0x main.cpp?
	std::map <int, Player*> pdb;//maybe make this a pointer?
	AniListParser *aniList;
	ImageManager *imgManager;
};
