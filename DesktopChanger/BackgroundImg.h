#include <iostream>

struct BackgroundImg
{
	std::string name;
	std::string extension;

	BackgroundImg(std::string _name, std::string _extension)
	{
		name = _name;
		extension = _extension;
	}
};