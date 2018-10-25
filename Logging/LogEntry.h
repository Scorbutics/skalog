#pragma once

#include <sstream>
#include <cassert>
#include <optional>
#include <ctime>
#include <chrono>
#include "LogLevel.h"
#include "LogContext.h"
#include "Tokenizer.h"
#include "LoggerImpl.h"

namespace ska {
	
	namespace loggerdetail {
		struct LogTimePoint {
			tm date;
			std::size_t milliseconds;
		};
	}
	
    class LogEntry {
		using LogCallback = std::function<void(const LogEntry&)>;

	public:
		LogEntry(LogCallback callback, loggerdetail::LogContext context, bool disabled = false) :
			id(InstanceCounter++),
			context(std::move(context)),
			date(currentDateTime()),
			callback(callback),
			disabled(disabled) {
		}

		LogEntry(const LogEntry& e) {
			id = e.id;
			context = e.context;
			date = e.date;
			callback = e.callback;
			disabled = e.disabled;
			fullMessage << e.fullMessage.rdbuf();
		}
		LogEntry(LogEntry&&) = default;
        
		LogEntry& operator=(const LogEntry&) = delete;
		LogEntry& operator=(LogEntry&&) = delete;

		~LogEntry() {
			if (!disabled) {
				//MUST NOT throw !
				fullMessage << "\n";
				callback(*this);
				disabled = true;
			}
		}

		const loggerdetail::LogContext& getContext() const {
			return context;
		}

        std::string getMessage() const {
            return fullMessage.str();
        }

        const loggerdetail::LogTimePoint& getDate() const {
            return date;
        }

        std::size_t getId() const {
            return id;
        }

		void resetCallback(){
			callback = LogCallback {};
			disabled = true;
		}

    private:
        std::size_t id;
		loggerdetail::LogContext context;
        //Mutable used safely because LogEntry is only a short time wrapper-class that is destroyed at the end of the log line
        mutable std::stringstream fullMessage;
        loggerdetail::LogTimePoint date;
		LogCallback callback;
        bool disabled;

		static std::size_t InstanceCounter;
        static loggerdetail::LogTimePoint currentDateTime();
        
        template <class T>
        friend const LogEntry& operator<<(const LogEntry& logEntry, T&& logPart);

		template <LogLevel MinLevel, LogLevel MaxLevel, class LogMethod>
		friend class Logger;
    };
    
    template <class T>
    const LogEntry& operator<<(const LogEntry& logEntry, T&& logPart) {
		if (logEntry.disabled) {
			return logEntry;
		}

        logEntry.fullMessage << std::forward<T>(logPart);
        return logEntry;
    }
    
}

