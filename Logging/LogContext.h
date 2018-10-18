#pragma once

#include <string>
#include "LogLevel.h"

namespace ska {
	namespace loggerdetail {
		struct LogContext {
			LogLevel logLevel;
			std::string className;

			//!! static memory data !!
			const char* functionName = nullptr;
			const char* filename = nullptr;
			
			long line = 0;
		};
	}
}