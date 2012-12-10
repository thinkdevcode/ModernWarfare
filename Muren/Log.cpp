#include "Log.h"

namespace Log
{
	void Write(Log::Entry LogType, std::string Message)
	{
		LogFile.open("MorenLog.txt", std::ios::app | std::ios::out);
		if (LogFile.is_open())
		{
			if ((LogType == FILE) || (LogType == BOTH))
			{
				LogFile << Message.c_str() << std::endl;
				LogFile.flush();
			}
			LogFile.close();
		}
	}
	void WriteObjectLog(Log::Entry LogType, unsigned int ObjectId, std::string Message)
	{
		LogFile.open("MorenLog.txt", std::ios::app | std::ios::out);
		if (LogFile.is_open())
		{
			if ((LogType == FILE) || (LogType == BOTH))
			{
				LogFile << "Object[" << ObjectId << "] " << Message.c_str() << std::endl;
				LogFile.flush();
			}
			LogFile.close();
		}
	}
}