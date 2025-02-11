#include "AniListParser.h"
const std::string ANILIST_API_URL = "https://anilist.co/api/";
const std::string AUTHENTICATION_SUFFIX = "auth/access_token";
const std::string SEARCH_SUFFIX = "character/search/";

AniListParser::AniListParser()
{
	clientId = UserVar::apiId.toStdString();//"brah-gkee1";
	clientSecrete = UserVar::apiKey.toStdString();//"oVNN5Ky9wJdoyMPpcZV2b2DlfpwJYz";
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

	//TODO DEBUG REASONS ONLY
	for (size_t pos = charName.find('(');
		pos != std::string::npos;
		pos = charName.find('(', pos))
	{
		charName = charName.substr(0, pos);
		break;
	}

	std::string test = ANILIST_API_URL + SEARCH_SUFFIX + charName;
	auto s = cpr::Get(cpr::Url{ANILIST_API_URL+SEARCH_SUFFIX+charName},
		cpr::Parameters{ { "access_token", token } });
	nlohmann::json p = nlohmann::json::parse(s.text);

	//if empty search result
	if ((s.text.size() < 8)) {
		return "http://anilist.co/img/dir/character/reg/42093.jpg";
	}

	// If an empty search result, p.at(0) wont exist
	try
	{
		auto accessString = p.at(0).at("image_url_lge");
		std::string temp = accessString;
		char *cstr = new char[temp.length() + 1];
		strcpy(cstr, temp.c_str());
		return accessString;
	}
	catch (std::exception &e)
	{
		return "http://anilist.co/img/dir/character/reg/42093.jpg";
	}

	return "http://anilist.co/img/dir/character/reg/42093.jpg";
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
