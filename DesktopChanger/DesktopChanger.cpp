#include "DesktopChanger.h"


std::string getImageUrlFromReddit(std::string subreddit)
{
	JsonManager jsonMan;

	// get and parse json page from reddit
	char* jsonPage = NULL;
	InternetManager::DownloadPage(subreddit, &jsonPage);
	jsonMan.setInput(jsonPage);
	jsonMan.parseInput();

	// if it doesn't find urls exit
	if (jsonMan.getUrlN() == 0)
		return "";

	// random and download the background
	srand(time(NULL));
	int indexRand = rand() % jsonMan.getUrlN();
	std::string urlImg = jsonMan.getUrl(indexRand);
	_RPT3(0, "Random: %d/%d, Url: %s\n", indexRand, jsonMan.getUrlN(), urlImg.c_str());

	delete jsonPage;
	return urlImg;
}

std::string downloadImage(std::string urlImg)
{
	CreateDirectoryA("download", NULL);

	InternetManager inetMan;
	std::string path = ExePath(); // absolute path of exe

	BackgroundImg back = BackFromUrl(urlImg);
	std::string imgPath = path + std::string("download\\background") + back.extension;
	// if the download fail return nothing
	if (inetMan.DownloadFile(urlImg, imgPath) != S_OK)
		return "";
	_RPT1(0, "File downloaded in %s\n", imgPath.c_str());

	return imgPath;
}

void setBackground(std::string imgPath)
{
	/*
	DWORD ftyp = GetFileAttributesA("download");
	while (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA("download", NULL);
		ftyp = GetFileAttributesA("download");
	}
	*/
	_RPT1(0, "Path: %s\n", imgPath.c_str());
	SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)imgPath.c_str(), SPIF_UPDATEINIFILE);
}