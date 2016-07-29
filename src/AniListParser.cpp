#include "AniListParser.h"
const std::string ANILIST_API_URL ="https://anilist.co/api/";
const std::string AUTHENTICATION_SUFFIX ="auth/access_token";
const std::string SEARCH_SUFFIX ="character/search/";



AniListParser::AniListParser()
{
	clientId = "brah-gkee1";
	clientSecrete = "oVNN5Ky9wJdoyMPpcZV2b2DlfpwJYz";
	AniListParser::renewToken();
}

std::string AniListParser::getCharacterImg(std::string charName)
{
	//Knowing the token, find the chater img directory
	//Replace the spaces
	for (size_t pos = charName.find(' ');
		pos != std::string::npos;
		pos = charName.find(' ', pos))
	{
		charName.replace(pos, 1, "%20");
	}

	auto s = cpr::Get(cpr::Url{ANILIST_API_URL+SEARCH_SUFFIX+charName},
		cpr::Parameters{ { "access_token", token } });
	nlohmann::json p = nlohmann::json::parse(s.text);
	// Response an object inside an array
	auto accessString = p.at(0).at("image_url_lge");
	std::string temp = accessString;
	char *cstr = new char[temp.length() + 1];
	strcpy(cstr, temp.c_str());

	return accessString;
}

//TODO Make a timer for this guy
void AniListParser::renewToken()
{
	// Get access key from Anilist API
	auto r = cpr::Post(cpr::Url{ANILIST_API_URL+AUTHENTICATION_SUFFIX},
	cpr::Payload{ { "grant_type", "client_credentials" },{ "client_id", clientId },{ "client_secret",clientSecrete} });
	// Parse response into a JSON
	nlohmann::json o = nlohmann::json::parse(r.text);

	// Try finding the access token
	// TODO First check status token!
	token = o.at("access_token");
}
