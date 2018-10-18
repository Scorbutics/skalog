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
		using LogCallback = std::function<void(const LogEntry&)>;

	public:
		LogEntry(LogCallback callback, loggerdetail::LogContext context, bool disabled = false) :
			id(InstanceCounter++),
			context(std::move(context)),
			date(currentDateTime()),
			callback(callback),
			disabled(disabled) {
		}

        LogEntry(const LogEntry&) = default;
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

        const tm& getDate() const {
            return date;
        }

        const std::size_t getId() const {
            return id;
        }

		LogEntry cloneMessage(LogCallback callback) const {
			auto result = LogEntry {std::move(callback), context };
			result.fullMessage << fullMessage.str();
			return result;
		}

    private:
        std::size_t id;
		LogCallback callback;
		loggerdetail::LogContext context;
        //Mutable used safely because LogEntry is only a short time wrapper-class that is destroyed at the end of the log line
        mutable std::stringstream fullMessage;
        tm date;
		bool disabled;

		static std::size_t InstanceCounter;
        static tm currentDateTime();
        
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

