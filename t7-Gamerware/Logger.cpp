#include "Logger.h"

namespace RCE
{

	std::map< int, std::string> log_s = {};

	static char logInput[255] = "";

	void AddToLog(std::string output)
	{
		log_s[(int)log_s.size() + 1] = output.c_str();

	}

}