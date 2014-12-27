#pragma once

#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"
#include "rapidjson\reader.h"
#include <vector>

class UrlHandler {
private:
	int urlN = 0;
	bool isUrl = false; // true when it finds an url
	bool isImageUrl(const char* url); // true if the url end with .jpg or .png

public:
	//char* urls[30];
	std::vector<std::string> urls;
	UrlHandler();
	~UrlHandler();
	int getUrlN();
	void reset();

	bool Null() { return true; }
	bool Bool(bool b) { return true; }
	bool Int(int i) { return true; }
	bool Uint(unsigned u) { return true; }
	bool Int64(int64_t i) { return true; }
	bool Uint64(uint64_t u) { return true; }
	bool Double(double d) { return true; }
	bool String(const char* str, rapidjson::SizeType length, bool copy);
	bool StartObject() { return true; }
	bool Key(const char* str, rapidjson::SizeType length, bool copy);
	bool EndObject(rapidjson::SizeType memberCount) { return true; }
	bool StartArray() { return true; }
	bool EndArray(rapidjson::SizeType elementCount) { return true; }
};

class JsonManager
{
	char jsonStream[50000];
	UrlHandler handler;

public:
	JsonManager(const char* input);
	JsonManager();
	~JsonManager();
	std::string getUrl(int index);
	void parseInput();
	void setInput(const char* input);
	int getUrlN();
	void reset();
};
