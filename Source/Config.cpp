#include "stdafx.h"
#include "Config.h"

inline void Config::readFromFile(const std::string& filename)
{
	this->pars.clear();

	std::ifstream file(filename);

	if (!file.is_open())
		return;

	char c;

	std::string name;
	std::string val;

	while (!file.eof())
	{
		file.read(&c, sizeof(char));

		name.push_back(c);
	}
}
