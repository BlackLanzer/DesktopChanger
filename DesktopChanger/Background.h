#include <iostream>

struct Background
{
	std::string name;
	std::string extension;
	Background(std::string _name, std::string _extension)
	{
		name = _name;
		extension = _extension;
	}
};