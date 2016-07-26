#include "ChallongeParser.h"
tournamentId = "asfasfasdfasdfasdf";
matchIndex = "";
apiKey = "cnGhQzQf4yc4P6OxmsoxKWaOFEMtQa1kHpDIMy8L";

//TODO seperate REST interfacing with manipulation of json file into different classes

ChallongeParser::ChallongeParser() :
	playerOneScore(0),
	playerTwoScore(0),
	currentMatch(0),
	numPlayers(3)//TODO Set this during init config screen
{
	auto s = cpr::Get(cpr::Url{CHALLONGE_API_BASE_URL+TOURNAMENTS_SUFFIX+tournamentId+"/matches.json"},
		cpr::Parameters{ { "access_token", token } });
	matchIndex = json::parse(s.text);

	auto j = cpr::Get(cpr::Url{CHALLONGE_API_BASE_URL+TOURNAMENTS_SUFFIX+tournamentId+"/participants.json"},
		cpr::Parameters{ { "access_token", token } });
	participantIndex = json::parse(j.text);
}

// What if the tournament is halfway done? Lets get the interna
// book keeping up to date
void ChallongeParser::getCaughtUp()
{
	auto s = cpr::Get(cpr::Url{CHALLONGE_API_BASE_URL+TOURNAMENTS_SUFFIX+tournamentId+"/matches.json"},
		cpr::Parameters{ { "access_token", token } });
	json temp = json::parse(s.text);
	while(matchIndex.at(currentMatch).at("state")=="open"){
		matchIndex++;
	}
	auto checkRound = matchIndex.at(currentMatch).at("suggested_play_order")-1;
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
	playerTwpScore++;
	if(playerOneScore+playerTwoScore==numPlayers)
		pushWinner();
}

std::string ChallongeParser::fetchPlayerOneName(){
	auto playerId = matchIndex.at(currentMatch).at("player1_id");
	return participantIndex.at(playerId).at("name");
}

std::string ChallongeParser::fetchPlayerTwoName(){
	auto playerId = matchIndex.at(currentMatch).at("player1_id");
	return participantIndex.at(playerId).at("name");
}



void ChallongeParser::pushWinner()
{
	std:string winner = "";
	//TODO what is there are an uneven amount of players?
	if(playerOneScore>playerTwoScore){
		winner = "player1_id";
	}else{
		winner = "player2_id";
	}
	auto winnerId = matchIndex.at(currentMatch).at(winner);

	//TODO for matchfield, take scores ints and make a string out of them
	auto r = cpr::Post(cpr::Url{CHALLONGE_API_BASE_URL+TOURNAMENTS_SUFFIX+tournamentId+"/matches/"+matchIndex.at(currentMatch).at("id")+".json"},
	cpr::Payload{ { "api_key", apiKey},{ "match[scores_csv]", "3,0" },{ "match[winner_id]",winnerId}});

	currentMatch++;
	//TODO call a function to take us to the next match.
}
