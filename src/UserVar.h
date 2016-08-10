#ifndef USERVAR_H
#define USERVAR_H

#include <string>

enum api { anilist, google, imdb };

class UserVar {
	public:
		//TODO I dont know if making these static is the cleanest approach...
		static int apiChoice;
		// img search api specific variables
		static std::string apiKey;
		static std::string apiId;
		// Challonger specific variables
		static std::string challongerKey;
		static std::string tournamentId;
};

#endif