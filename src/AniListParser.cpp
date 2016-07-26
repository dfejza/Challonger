#include "AniListParser.h"

//// Get access key from Anilist API
//auto r = cpr::Post(cpr::Url{ "https://anilist.co/api/auth/access_token" },
//	cpr::Payload{ { "grant_type", "client_credentials" },{ "client_id", "brah-gkee1" },{ "client_secret", "oVNN5Ky9wJdoyMPpcZV2b2DlfpwJYz" } });
//// Parse response into a JSON
//json o = json::parse(r.text);
//
//
//// Try finding the access token
//// TODO First check status token!
//// TODO Make a renew token function!
//auto accessString = o.at("access_token");
//std::string test2 = accessString;
//
////Knowing the token, find the chater img directory
//auto s = cpr::Get(cpr::Url{ "https://anilist.co/api/character/search/revy" },
//	cpr::Parameters{ { "access_token", test2 } });
//json p = json::parse(s.text);
//// Response an object inside an array
//accessString = p.at(0).at("image_url_lge");
//test2 = accessString;
//p1->setPicture(QString::fromStdString(test2));


AniListParser::AniListParser()
{
	//TODO grab the user's API key from some dialogue
}

std::string AniListParser::getCharacterImg(std::string charName)
{
	return std::string();
}

void AniListParser::renewToken()
{
}
