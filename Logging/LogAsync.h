#pragma once

#include <optional>

#include "ActiveObject.h"
#include "LogEntry.h"

namespace ska {
	namespace loggerdetail {
		class Logger;
	}

	class LogPayload {
	public:
		LogPayload(std::function<void()> f) : lambda(std::move(f)) {}
		LogPayload(LogEntry e, loggerdetail::Logger& logger) : entry(std::move(e)), logger(&logger) {}

		void operator()();

	private:
		std::optional<LogEntry> entry;
		loggerdetail::Logger* logger = nullptr;
		std::function<void()> lambda;
	};

    class LogAsync {
    private:
        ActiveObject<LogPayload> m_commander;
    public:
		void log(const LogEntry& entry, loggerdetail::Logger& logger) {
			//Copy the entry in the commander
			m_commander.send(LogPayload{ entry, logger });
        }
    };
}

