#include "ChallongeParser.h"
//TODO seperate REST interfacing with manipulation of json file into different classes

ChallongeParser::ChallongeParser(PlayerFrame** p1f, PlayerFrame** p2f ) :
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

	//make empy player shells
	p1 = new Player();
	p2 = new Player();

	auto j = cpr::Get(cpr::Url{CHALLONGE_API_BASE_URL+TOURNAMENTS_SUFFIX+tournamentId+"/participants.json"},
		cpr::Parameters{ { "api_key", apiKey } });
	participantIndex = json::parse(j.text);

	db = new PlayerDatabase(participantIndex);

	p1frame = *p1f;
	p2frame = *p2f;

	getCaughtUp();
	loadPlayers(&p1, &p2);
}

// What if the tournament is halfway done? Lets get the internal
// book keeping up to date
void ChallongeParser::getCaughtUp()
{
	std::string complete = "complete";
	while(complete.compare(matchIndex.at(currentMatch).at("match").at("state")) == 0){
		currentMatch++;
	}
	//auto checkRound = matchIndex.at(currentMatch).at("match").at("suggested_play_order")-1;
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

std::string ChallongeParser::getP1PicPath()
{
	return p1->getPicturePath();
}

std::string ChallongeParser::getP2PicPath()
{
	return p2->getPicturePath();
}

std::string ChallongeParser::getP1Name()
{
	return p1->getName();
}

std::string ChallongeParser::getP2Name()
{
	return p2->getName();
}

void ChallongeParser::pushWinner()
{
	std::string winner = "";
	int currentMatchId = matchIndex.at(currentMatch).at("match").at("id");
	//TODO what is there are an uneven amount of players?
	if(playerOneScore>playerTwoScore){
		winner = "player1_id";
	}else{
		winner = "player2_id";
	}
	int winnerId = matchIndex.at(currentMatch).at("match").at(winner);
	//TODO for matchfield, take scores ints and make a string out of them
	auto r = cpr::Put(cpr::Url{CHALLONGE_API_BASE_URL+TOURNAMENTS_SUFFIX+tournamentId+"/matches/"+ std::to_string(currentMatchId) +".json"},
	
		cpr::Payload{ { "api_key", apiKey},{ "match[scores_csv]",
		(std::to_string(playerOneScore)+"-"+std::to_string(playerTwoScore)) },
		{ "match[winner_id]",std::to_string(winnerId)}});

	currentMatch++;
	playerOneScore = 0;
	playerTwoScore = 0;

	loadPlayers(&p1, &p2);
	//todo sleep timer of 3 seconds?

}

void ChallongeParser::loadPlayers(Player** p1p, Player** p2p){
	db->getPlayer(matchIndex.at(currentMatch).at("match").at("player1_id"), p1p);
	db->getPlayer(matchIndex.at(currentMatch).at("match").at("player2_id"), p2p);

	p1frame->updateFrame(QString::fromStdString(p1->getPicturePath()), QString::fromStdString(p1->getName()));
	p2frame->updateFrame(QString::fromStdString(p2->getPicturePath()), QString::fromStdString(p2->getName()));
}
