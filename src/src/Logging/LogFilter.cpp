#include "LogFilter.h"

ska::LogFilter ska::loggerdetail::GetIdentityLogFilter() { 
    return [](const ska::LogEntry&) {
        return true;
    };
}
