#pragma once

#include <vector>
#include <unordered_map>

#include "LogLevel.h"
#include "Tokenizer.h"
#include "LogTarget.h"

namespace ska {
    class LogEntry;

    template <class T>
    const LogEntry& operator<<(const LogEntry& logEntry, T&& logPart);

    namespace loggerdetail {
        class Logger {
            friend class ska::LogEntry;
        
        protected:
            Logger();
            Logger(std::ostream& output, LogFilter filter);
			
			LogLevel getLogLevel() const {
				return m_logLevel;
			}

        public:
            Logger(const Logger&) = delete;
			Logger& operator=(const Logger&) = delete;

			Logger(Logger&&) = default;
			Logger& operator=(Logger&&) = default;
			
            void configureLogLevel(const LogLevel& logLevel) {
                m_logLevel = logLevel;
            }
        
			void consumeNow(const LogEntry& self);

            void setPattern(LogLevel logLevel, std::string pattern) {
                auto existingLoglevel = m_pattern.find(logLevel);
                if(existingLoglevel != m_pattern.end()) {
                    m_pattern.erase(existingLoglevel);
                }
                m_pattern.emplace(logLevel, Tokenizer {std::move(pattern)});
            }

            void addOutputTarget(std::ostream& output, LogFilter filter = loggerdetail::GetIdentityLogFilter()) {
                m_output.emplace_back(output, filter);
            }

            ~Logger() = default;

        private:
            LogLevel m_logLevel;
            std::vector<LogTarget> m_output;
            std::unordered_map<LogLevel, Tokenizer> m_pattern;
            
            template <class T>
			friend const ska::LogEntry& ska::operator<<(const ska::LogEntry& logEntry, T&& logPart);
        };
        
    }
}
