#include "PlayerDatabase.h"

PlayerDatabase::PlayerDatabase(json o){

  createDatabase(o);
}

// Json o is the json object containg the raw data
void PlayerDatabase::createDatabase(json o){
  //o.at(std::to_string(playerId)).at("match").at("name");
  //    m["foo"] = 42;
  //    cout << m["foo"] << endl;
  // special iterator member functions for objects
  int participantId = 0;
  

  //Iterate through the array, and hash each member
  for (json::iterator it = o.begin(); it != o.end(); ++it) {
    participantId = it.value().at("participant").at("id");
	auto name1 = it.value().at("participant").at("name");
	std::string name = name1;
    //pdb[participantId] = new PlayerFrame(participantId, name);
	pdb[participantId] = new Player(participantId, name);
  }

}

void  PlayerDatabase::getPlayer(int participantId, Player** player){
  *player = pdb.at(participantId);
}
