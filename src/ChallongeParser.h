#pragma once
#include <cpr\cpr.h>
#include <json.hpp>
#include <string>
#include "PlayerDatabase.h"
#include "Player.h"
// TODO: Build an index of the participants. Make it a hashmap, challongeAPI already hashes it (see playerX-id)
// TODO: Keep statistics on them. Download all their portraits at the start, thus poll locallys
//https:	//openbracket:cnGhQzQf4yc4P6OxmsoxKWaOFEMtQa1kHpDIMy8L@api.challonge.com/v1/tournaments/asfasfasdfasdfasdf/participants.json

using json = nlohmann::json;
const std::string CHALLONGE_API_BASE_URL = "https://api.challonge.com/v1/"; //TODO make a global list of const
const std::string TOURNAMENTS_SUFFIX = "tournaments/";

class ChallongeParser {
public:
	ChallongeParser();
	void getCaughtUp();
	void incPlayerOneScore();//keep an internal counter. When counter reachers # of voters, then place a PUT rest request.
	void incPlayerTwoScore();
	void loadPlayers(Player** p1, Player** p2);
	/*
	std::string fetchPlayerOneName();
	std::string fetchPlayerTwoName();
	*/


private:
	void pushWinner(); //TODO make it bool, in case push fails?

	PlayerDatabase *db;
	json matchIndex;//all matches
	json participantIndex;
	std::string tournamentId;
	std::string apiKey;
	int playerOneScore;
	int playerTwoScore;
	int numPlayers;
	int currentMatch;
};
