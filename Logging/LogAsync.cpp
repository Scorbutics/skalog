#include "LogAsync.h"
#include "LoggerImpl.h"

void ska::LogPayload::operator()() {
	if (entry.has_value()) {
		assert(logger != nullptr);
		logger->consumeNow(entry.value());
	} else {
		lambda();
	}
}