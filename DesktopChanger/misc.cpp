#include "misc.h"

std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos + 1);
}

BackgroundImg BackFromUrl(std::string url)
{
	return BackgroundImg("background", url.substr(url.length() - 4, url.npos));
}