#ifndef _Log_
#define _Log_

#include <iostream>
#include <fstream>

namespace Log
{
	enum Entry
	{
		FILE,
		CERR,
		BOTH
	};

	void Write(Entry LogType, std::string Message);
	void WriteObjectLog(Log::Entry LogType, unsigned int ObjectId, std::string Message);

	namespace
	{
		std::ofstream LogFile;
	}
}

#endif