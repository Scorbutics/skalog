#include <chrono>
#include <cassert>
#include "LogEntry.h"
#include "ColorStream.h"

std::size_t ska::LogEntry::InstanceCounter = 0u;

tm ska::LogEntry::currentDateTime() {
	
    using namespace std::chrono; 
    milliseconds ms = duration_cast< milliseconds >( system_clock::now().time_since_epoch() );
    std::size_t absoluteTime = ms.count(); 
    
	return buf;
}

