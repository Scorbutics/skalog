#include "LogSync.h"
#include "LoggerImpl.h"

void ska::LogSync::log(const LogEntry& entry, loggerdetail::Logger& logger) {
	logger.consumeNow(entry);
}
