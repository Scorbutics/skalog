#pragma once

#include "LogEntry.h"
#include "LoggerImpl.h"
#include "LogLevel.h"

#include "LogSync.h"

namespace ska {

	template<class T>
	class LoggerClassFormatter;
	
	template<class T>
	class LoggerClassLevel {
    public:
        static constexpr const auto level = LogLevel::Debug;
    };

    namespace loggerdetail {
        struct EmptyProxy {};
        template <class T>
        const EmptyProxy& operator<<(const EmptyProxy& logEntry, T&& logPart) {
            return logEntry;
        }
    }
    
	template <LogLevel MinLevel = LogLevel::Debug, LogLevel MaxLevel = LogLevel::Error, class LogMethod = LogSync>
    class Logger : public loggerdetail::Logger {
	private:
		loggerdetail::LogEntry<LogMethod> log(const char* className) {
			return loggerdetail::LogEntry<LogMethod>{ *this, logLevel, m_logMethod, className };
		}

	public:
        Logger(std::ostream& output, LogFilter filter) :
            loggerdetail::Logger(output, std::move(filter)) {
        }
        
		

		template<LogLevel logLevel>
		auto slog(const char* className) {
			if constexpr (logLevel >= LoggerClassLevel<Wrapped>::level &&
				(logLevel >= MinLevel && logLevel <= MaxLevel)) {
				return log(className);
			} else {
				return loggerdetail::EmptyProxy{};
			}
		}

		template <LogLevel logLevel, class Wrapped>
		auto log() {
			return this->template slog<logLevel>(LoggerClassFormatter<Wrapped>::className);
		}

        ~Logger() = default;
    
    private:
        LogMethod m_logMethod;
    };
}

#ifndef SKA_DONT_USE_LOG_DEFINE
#define SKA_LOGC(logger, level, currentClass) logger.slog<ska::LogLevel::##level>(#currentClass)

#ifdef __PRETTY_FUNCTION__
#define SKA_CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#define SKA_CURRENT_FUNCTION __FUNCSIG__ 
#else
#define SKA_CURRENT_FUNCTION __func__
#endif

#endif