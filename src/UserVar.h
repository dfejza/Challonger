#ifndef USERVAR_H
#define USERVAR_H

#include <QString>

enum api { anilist, google, imdb };

class UserVar {
	public:
		//TODO I dont know if making these static is the cleanest approach...
		static int apiChoice;
		// img search api specific variables
		static QString apiKey;
		static QString apiId;
		// Challonger specific variables
		static QString challongerKey;
		static QString tournamentId;
		static QString tournamentName;
};

#endif