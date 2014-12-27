#include "InternetManager.h"
#include <tchar.h>

InternetManager::InternetManager()
{
	downloading = false;
}


InternetManager::~InternetManager()
{
}

bool InternetManager::IsDownloading()
{
	return downloading;
}

void InternetManager::DownloadPage(std::string subreddit, char** buffer)
{
	HINTERNET intSession = InternetOpenA("desktopChanger", INTERNET_OPEN_TYPE_DIRECT, 0, 0, 0);

	HINTERNET httpSession = InternetConnectA(intSession, "reddit.com", 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
	subreddit = "r/" + subreddit + ".json";
	HINTERNET httpRequest = HttpOpenRequestA(httpSession, "GET", subreddit.c_str(), 0, 0, 0, 0, 0);

	HttpSendRequestA(httpRequest, 0, 0, NULL, 1024);

	*buffer = new char[50000];

	DWORD length;
	char* tmpBuffer = *buffer;
	while (InternetReadFile(httpRequest, tmpBuffer, 1024, &length) && length)
	{
		tmpBuffer[length] = 0;
		tmpBuffer += length;
		length = 0;
	}

	InternetCloseHandle(httpRequest);
	InternetCloseHandle(httpSession);
	InternetCloseHandle(intSession);
}

HRESULT InternetManager::DownloadFile(std::string url, std::string path)
{
	downloading = true;
	HRESULT res = URLDownloadToFileA(NULL, url.c_str(), path.c_str(), 0, this);
	downloading = false;
	return res;
}

HRESULT InternetManager::OnProgress(ULONG ulProgress, ULONG ulProgressMax,
	ULONG ulStatusCode, LPCWSTR wszStatusText)
{
	_RPT2(0, "Downloading: %d / %d\n", ulProgress, ulProgressMax);
	return S_OK;
}


