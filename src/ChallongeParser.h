#pragma once
#include <cpr\cpr.h>
#include <json.hpp>
#include <string>
// TODO: Build an index of the participants. Make it a hashmap, challongeAPI already hashes it (see playerX-id)
// TODO: Keep statistics on them. Download all their portraits at the start, thus poll locallys
//https://openbracket:cnGhQzQf4yc4P6OxmsoxKWaOFEMtQa1kHpDIMy8L@api.challonge.com/v1/tournaments/asfasfasdfasdfasdf/participants.json

using json = nlohmann::json;
const std::string challongeApiBaseUrl = "https://api.challonge.com/v1/"; //TODO make a global list of const

class ChallongeParser {
public:
	ChallongeParser();
	void incPlayerOneScore();//keep an internal counter. When counter reachers # of voters, then place a PUT rest request.
	void incPlayerTwoScore();
	void pushWinner(); //TODO make it bool, in case push fails?

private:
	json matchIndex;//all matches
	json currentMatch;//Not sure if I want to juggle a large json file or just fetch matches individually.
	std::string tournamentId;
	std::string apiKey;
	int playerOneScore;
	int playerTwoScore;
	int currentMatch;
};