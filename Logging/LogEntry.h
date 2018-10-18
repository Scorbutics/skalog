#pragma once

#include <sstream>
#include <cassert>
#include <optional>
#include "LogLevel.h"
#include "LogContext.h"
#include "Tokenizer.h"
#include "LoggerImpl.h"

namespace ska {

    class LogEntry {
		using LogCallback = std::function<void(LogEntry&)>;
    protected:
        LogEntry(LogCallback callback, loggerdetail::LogContext context) :
			LogEntry(std::move(context)) {
			this->callback = std::move(callback);
        }

		LogEntry(loggerdetail::LogContext context) :
			id(InstanceCounter++),
			context(std::move(context)),
			date(currentDateTime()) {
		}

    public:
        LogEntry(const LogEntry&) = delete;
        LogEntry& operator=(const LogEntry&) = delete;

        LogEntry(LogEntry&&) = default;
        LogEntry& operator=(LogEntry&&) = default;

		~LogEntry() {
			if (callback.has_value()) {
				//MUST NOT throw !
				fullMessage << "\n";
				callback.value()(*this);
				callback.reset();
			}
		}

		const loggerdetail::LogContext& getContext() const {
			return context;
		}

        std::string getMessage() const {
            return fullMessage.str();
        }

        const tm& getDate() const {
            return date;
        }

        const std::size_t getId() const {
            return id;
        }

    private:
        std::size_t id;
		std::optional<LogCallback> callback;
		loggerdetail::LogContext context;
        //Mutable used safely because LogEntry is only a short time wrapper-class that is destroyed at the end of the log line
        mutable std::stringstream fullMessage;
        tm date;
        
		static std::size_t InstanceCounter;
        static tm currentDateTime();
        
        template <class T>
        friend const LogEntry& operator<<(const LogEntry& logEntry, T&& logPart);

		template <LogLevel MinLevel, LogLevel MaxLevel, class LogMethod>
		friend class Logger;
    };
    
    template <class T>
    const LogEntry& operator<<(const LogEntry& logEntry, T&& logPart) {
        if (logEntry.logLevel >= logEntry.instance->m_logLevel) {
            logEntry.fullMessage << std::forward<T>(logPart);
        }
        return logEntry;
    }
    
}

