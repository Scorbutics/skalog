#include <cassert>
#include "LogEntry.h"
#include "ColorStream.h"

std::size_t ska::LogEntry::InstanceCounter = 0u;

ska::loggerdetail::LogTimePoint ska::LogEntry::currentDateTime() {
    using namespace std::chrono; 
	auto nowTime = system_clock::now();
    const auto ms = duration_cast<milliseconds>( nowTime.time_since_epoch() ).count();
	auto t = system_clock::to_time_t(nowTime);
	#ifdef _MSC_VER
		tm buf;
		localtime_s(&buf, &t);
	#else
		tm buf = *std::localtime(&t);
	#endif
	
	return { buf, ms%1000 }; 
}

