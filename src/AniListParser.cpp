#include "AniListParser.h"
const std::string ANILIST_API_URL ="https://anilist.co/api/";
const std::string AUTHENTICATION_SUFFIX ="auth/access_token/";
const std::string SEARCH_SUFFIX ="character/search/";

clientId = "brah-gkee1";
clientSecrete = "oVNN5Ky9wJdoyMPpcZV2b2DlfpwJYz";

AniListParser::AniListParser()
{
	AniListParser::renewToken();
}

//
std::string AniListParser::getCharacterImg(std::string charName)
{
	//Knowing the token, find the chater img directory
	auto s = cpr::Get(cpr::Url{ANILIST_API_URL+SEARCH_SUFFIX+charName},
		cpr::Parameters{ { "access_token", token } });
	json p = json::parse(s.text);
	// Response an object inside an array
	auto accessString = p.at(0).at("image_url_lge");

	return accessString;
}

//TODO Make a timer for this guy
void AniListParser::renewToken()
{
	// Get access key from Anilist API
	auto r = cpr::Post(cpr::Url{ANILIST_API_URL+AUTHENTICATION_SUFFIX},
	cpr::Payload{ { "grant_type", "client_credentials" },{ "client_id", clientId },{ "client_secret",clientSecrete} });
	// Parse response into a JSON
	json o = json::parse(r.text);

	// Try finding the access token
	// TODO First check status token!
	auto accessString = o.at("access_token");
	token = accessString;
}
