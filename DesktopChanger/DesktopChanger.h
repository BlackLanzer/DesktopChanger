#pragma once 

#include <iostream>
#include <Windows.h>
#include <ctime>
#include "InternetManager.h"
#include "JsonManager.h"
#include "BackgroundImg.h"
#include "misc.h"

// return an image url taken from the subreddit.
// Empty string if fail
std::string getImageUrlFromReddit(std::string subreddit);

// download an image from urlImg. Returns the path of the image
// or an empty string if fail
std::string downloadImage(std::string urlImg);

void setBackground(std::string imgPath);