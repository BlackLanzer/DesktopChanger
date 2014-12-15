#pragma once

#include <iostream>
class InternetManager
{
	std::string url;
	bool downloading;

public:
	InternetManager();
	~InternetManager();
	void DownloadFile(std::string path);
	void GetPage(char* buffer);
	bool IsDownloading();
};

