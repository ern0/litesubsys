#pragma once 

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream> 
#include <time.h>
#include <algorithm>
#include <mutex>

#include <cstddef>
#include <utility>
#include <string>

#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)
#define __INFO__ (__FILE__ ":" STRINGIZE(__LINE__))
//#define __INFO_F__ (__FILE__ "::" ((const char *)__func__) ":" STRINGIZE(__LINE__))
#define __INFO_M__(MSG) (__FILE__ ":" STRINGIZE(__LINE__) ":" MSG)

namespace com_c
{
/// actual time
static std::string time2String()
{
	
	std::time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	std::time(&rawtime);
	timeinfo = std::localtime(&rawtime);

	std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S | ", timeinfo);
	std::string str(buffer);

	return str;
}

constexpr char mConstLogFile[] = "logging.txt";

class Logging
{
public:
	Logging(Logging&& move)               = delete;
    Logging& operator=(Logging&& move)    = delete;
    void swap(Logging& other)             = delete;
    Logging(Logging const&)               = delete;
    Logging& operator=(Logging const&)    = delete;

	/// logger config
	/// @param type: what will be the tag, like [INFO]	
	/// @param tostdout: if it true will show the messages in the stdout, false only logging.txt
	Logging(std::string type, bool tostdout) : mType(type), mToStdout(tostdout){};
protected:
	Logging() = delete;
	virtual ~Logging(){};

	/// type of logging
	std::string mType;

	/// logging to stdout
	bool mToStdout;

public:
	void operator<<(const std::string& str) 
	{
		if(mToStdout)
			std::cout << mType << " " << str << "\n";

		std::lock_guard<std::mutex> guard(m);

		std::string name = mConstLogFile;
		std::fstream file;
		file.open(name.c_str(), std::fstream::out | std::fstream::app);
		file << mType << " " << time2String() << str << "\n";
		file.close();
	}

	void operator<<(const char& chr) 
	{
		if(mToStdout)
			std::cout << mType << " " << chr << "\n";

		std::lock_guard<std::mutex> guard(m);

		std::string name = mConstLogFile;
		std::fstream file;
		file.open(name.c_str(), std::fstream::out | std::fstream::app);
		file << mType << " " << time2String() << chr << "\n";
		file.close();
	}

private:	
	std::mutex m;

};

class InfoLogging : public Logging
{
public:
InfoLogging() : Logging("[INFO]", true){};
~InfoLogging(){};
};

class DebugLogging : public Logging
{
public:
DebugLogging() : Logging("[DEBUG]", false){};
~DebugLogging(){};
};

class ErrorLogging : public Logging
{
public:
ErrorLogging() : Logging("[ERROR]", true){};
~ErrorLogging(){};
};

static InfoLogging		INFOLOGGING;
static DebugLogging		DEBUGLOGGING;
static ErrorLogging		ERRORLOGGING;

}