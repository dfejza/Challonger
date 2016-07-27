
#include <json.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

using json = nlohmann::json;

//lets use hashtable for now, not threaded atm
class PlayerDatabase{
public:
  PlayerDatabase(json o);
  void createDatabase(json o);
  void getPlayerFrame(int participantId, PlayerFrame** playerFrame);
private:
  //g++ -std=c++0x main.cpp?
  unordered_map <int, PlayerFrame> pdb;//maybe make this a pointer?
}
