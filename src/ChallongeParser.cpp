#include "ChallongeParser.h"

//TODO seperate REST interfacing with manipulation of json file into different classes

ChallongeParser::ChallongeParser() :
	playerOneScore(0),
	playerTwoScore(0),
	currentMatch(0),
	numPlayers(3)//TODO Set this during init config screen
{
	tournamentId = "asfasfasdfasdfasdf";
	matchIndex = "";
	apiKey = "cnGhQzQf4yc4P6OxmsoxKWaOFEMtQa1kHpDIMy8L";

	auto s = cpr::Get(cpr::Url{CHALLONGE_API_BASE_URL+TOURNAMENTS_SUFFIX+tournamentId+"/matches.json"},
		cpr::Parameters{ { "api_key", apiKey } });
	/*
	s.status_code type int
	0 - no internet?
    200 - OK
    401 - Unauthorized (Invalid API key or insufficient permissions)
    404 - Object not found within your account scope
    406 - Requested format is not supported - request JSON or XML only
    422 - Validation error(s) for create or update method
    500 - Something went wrong on our end. If you continually receive this, please contact us.

	*/
	matchIndex = json::parse(s.text);

	auto j = cpr::Get(cpr::Url{CHALLONGE_API_BASE_URL+TOURNAMENTS_SUFFIX+tournamentId+"/participants.json"},
		cpr::Parameters{ { "api_key", apiKey } });
	participantIndex = json::parse(j.text);

	db = new PlayerDatabase(participantIndex);
}

// What if the tournament is halfway done? Lets get the interna
// book keeping up to date
void ChallongeParser::getCaughtUp()
{
	auto s = cpr::Get(cpr::Url{CHALLONGE_API_BASE_URL+TOURNAMENTS_SUFFIX+tournamentId+"/matches.json"},
		cpr::Parameters{ { "api_key", apiKey } });
	json temp = json::parse(s.text);
	while(matchIndex.at(currentMatch).at("match").at("state")=="open"){
		currentMatch++;
	}
	auto checkRound = matchIndex.at(currentMatch).at("match").at("suggested_play_order")-1;
	//TODO compare contents of checkRound with matchIndex
}

void ChallongeParser::incPlayerOneScore()
{
	playerOneScore++;
	if(playerOneScore+playerTwoScore==numPlayers)
		pushWinner();
}

void ChallongeParser::incPlayerTwoScore()
{
	playerTwoScore++;
	if(playerOneScore+playerTwoScore==numPlayers)
		pushWinner();
}

std::string ChallongeParser::fetchPlayerOneName(){
	int playerId = matchIndex.at(currentMatch).at("match").at("player1_id");
	//TODO need to make a function where the players are stored by their hash. this current method doesnt work.
	return participantIndex.at(std::to_string(playerId)).at("match").at("name");
}

std::string ChallongeParser::fetchPlayerTwoName(){
	int playerId = matchIndex.at(currentMatch).at("match").at("player1_id");
	return participantIndex.at(std::to_string(playerId)).at("name");
}



void ChallongeParser::pushWinner()
{
	std::string winner = "";
	std::string currentMatchId = matchIndex.at(currentMatch).at("match").at("id");
	//TODO what is there are an uneven amount of players?
	if(playerOneScore>playerTwoScore){
		winner = "player1_id";
	}else{
		winner = "player2_id";
	}
	std::string winnerId = matchIndex.at(currentMatch).at("match").at(winner);
	//TODO for matchfield, take scores ints and make a string out of them
	auto r = cpr::Post(cpr::Url{CHALLONGE_API_BASE_URL+TOURNAMENTS_SUFFIX+tournamentId+"/matches/"+ currentMatchId +".json"},
	cpr::Payload{ { "api_key", apiKey},{ "match[scores_csv]", "3,0" },{ "match[winner_id]",winnerId}});

	currentMatch++;
	//TODO call a function to take us to the next match.
}
