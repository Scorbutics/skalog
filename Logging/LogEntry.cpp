#include <ctime>
#include <cassert>
#include <iomanip>
#include "LogEntry.h"
#include "ColorStream.h"

std::size_t ska::LogEntry::InstanceCounter = 0u;

tm ska::LogEntry::currentDateTime() {
	auto t = std::time(nullptr);
#ifdef _MSC_VER
	tm buf;
	localtime_s(&buf, &t);
#else
	tm buf = *std::localtime(&t);
#endif
	return buf;
}

