#include "PlayerDatabase.h"
#include "PlayerFrame.h"

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
  std::string name = "";

  //Iterate through the array, and hash each member
  for (json::iterator it = o.begin(); it != o.end(); ++it) {
    participantId = it.value().at("participant").at("id");
    name = it.value().at("participant").at("name");

    pdb[new PlayerFrame(participantId,name)] = participantId;
  }

}

void  PlayerDatabase::getPlayerFrame(int participantId, PlayerFrame** playerFrame){
  playerFrame = pdb[participantId];
}
