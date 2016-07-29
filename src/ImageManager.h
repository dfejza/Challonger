#pragma once

#define _WINSOCKAPI_
#include <curl/curl.h>
#include <string>
//#include<windows.h>

class ImageManager {
public:
	ImageManager();
	std::string downloadImage(std::string url, int playerId);
private:
	CURL *curl;

};