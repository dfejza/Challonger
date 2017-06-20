#include "PlayerDatabase.h"

PlayerDatabase::PlayerDatabase(json o, QProgressDialog** pb){
	aniList = new AniListParser();
	imgManager = new ImageManager();
	progressBar = *pb;
	createDatabase(o);
}

BOOL DirectoryExists(const char* dirName) {
	DWORD attribs = ::GetFileAttributesA(dirName);
	if (attribs == INVALID_FILE_ATTRIBUTES) {
		return false;
	}
	return (attribs & FILE_ATTRIBUTE_DIRECTORY);
}

// Json o is the json object containg the raw data
void PlayerDatabase::createDatabase(json o){
  //o.at(std::to_string(playerId)).at("match").at("name");
  //    m["foo"] = 42;
  //    cout << m["foo"] << endl;
  // special iterator member functions for objects
  int participantId = 0;
  std::string url = "";
  std::string path = "";

  progressBar->setMaximum(std::distance(o.begin(), o.end()-1));
  //Iterate through the array, and hash each member
 //#pragma omp parallel for
  for (json::iterator it = o.begin(); it != o.end(); ++it) {
	//progressBar = (double)std::distance(o.begin(), it) / (double)std::distance(o.begin(), o.end());
	progressBar->setValue(std::distance(o.begin(), it));
    participantId = it.value().at("participant").at("id");
	auto name1 = it.value().at("participant").at("name");
	std::string name = name1;

	std::string spath = "assets\\" + std::to_string(participantId);
	char const* ca = spath.c_str();

	//download all the pictures if it doesnt exist
	if (!DirectoryExists(ca)) {
		url = aniList->getCharacterImg(name);
		path = imgManager->downloadImage(url, participantId);
	}
	else
	{
		path = spath+"\\pic.jpg";
	}

    //pdb[participantId] = new PlayerFrame(participantId, name);
	pdb[participantId] = new Player(participantId, name, url, path);
  }
  progressBar->setValue(std::distance(o.begin(), o.end() - 1));
}

void  PlayerDatabase::getPlayer(int participantId, Player** player){
  *player = pdb.at(participantId);
}
