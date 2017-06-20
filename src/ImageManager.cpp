#include "ImageManager.h"


ImageManager::ImageManager()
{
	curl = curl_easy_init();
}



size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

//TODO this class is messy, clean it
std::string ImageManager::downloadImage(std::string url, int playerId)
{
	
	FILE *fp;
	CURLcode res;
	char outfilename[FILENAME_MAX];

	char * writable = new char[url.size() + 1];
	std::copy(url.begin(), url.end(), writable);
	writable[url.size()] = '\0'; // don't forget the terminating 0


	//Make the dir
	std::wstring str = L"assets\\" + std::to_wstring(playerId);
	const wchar_t *str1 = str.c_str();

	CreateDirectory(str.c_str(), NULL);

	char *url1 = writable;

	strcpy(outfilename, "assets\\");
	strcat(outfilename, std::to_string(playerId).c_str());
	strcat(outfilename, "\\pic.jpg");
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(outfilename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url1);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
		fclose(fp);
	}
	delete[] writable;
	return outfilename;
}
