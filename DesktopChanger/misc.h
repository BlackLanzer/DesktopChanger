#include <iostream>
#include <Windows.h>
#include "BackgroundImg.h"

// return the path of the exe file
std::string ExePath();

// return a BackgroundImg struct from the url of the image
BackgroundImg BackFromUrl(std::string url);
