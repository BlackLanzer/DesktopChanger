#include "JsonManager.h"
#include <regex>
#include <string>

JsonManager::JsonManager(const char* input)
{
	strcpy_s(jsonStream, 50000, input);
	//handler = UrlHandler();

	int i;
	//for (i = 0; i < 30; i++)
	//	handler.urls[i] = new char(500);
}

JsonManager::JsonManager() : JsonManager("")
{ }

JsonManager::~JsonManager()
{

}

std::string JsonManager::getUrl(int index)
{
	if (index < getUrlN())
		return handler.urls[index];

	return 0;
}

void JsonManager::setInput(const char* input)
{
	strcpy_s(jsonStream, 50000, input);
}

void JsonManager::parseInput()
{
	rapidjson::Reader reader;
	rapidjson::StringStream s = rapidjson::StringStream(jsonStream);
	reader.Parse(s, handler);
}

int JsonManager::getUrlN()
{
	return handler.getUrlN();
}

void JsonManager::reset()
{
	handler.reset();
}

UrlHandler::UrlHandler()
{ }

int UrlHandler::getUrlN()
{
	return urlN;
}

bool UrlHandler::String(const char* str, rapidjson::SizeType length, bool copy) {
	if (isUrl)
	{
		isUrl = false;
		if (isImageUrl(str))
		{
			//urls[urlN] = new char(length + 1);
			//strcpy_s(urls[urlN++], length + 1, str);
			urls.push_back(std::string(str));
			urlN++;
		}
	}
	return true;
}

bool UrlHandler::Key(const char* str, rapidjson::SizeType length, bool copy) {
	if (strcmp(str, "url") == 0)
	{
		isUrl = true;
	}
	return true;
}

bool UrlHandler::isImageUrl(const char* url)
{
	if (std::regex_search(url, std::regex("\.jpg$")) || std::regex_search(url, std::regex("\.png$")))
		return true;
	return false;
}

void UrlHandler::reset()
{
	urlN = 0;
	isUrl = false;
	urls.clear();
}

UrlHandler::~UrlHandler()
{ }
