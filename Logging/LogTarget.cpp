#include <cassert>

//setfill, setw
#include <iomanip>

#include "LogTarget.h"
#include "LogEntry.h"
#include "ColorStream.h"

bool ska::loggerdetail::LogTarget::isATarget(const ska::LogEntry& entry) {
    return m_filter(entry);
}

bool ska::loggerdetail::LogTarget::applyTokenOnOutput(const ska::LogEntry& entry, const Token& token) {
    if(!isATarget(entry)) {
        return false;
    }

    auto& output = m_output;
    const auto& date = entry.getDate(); 
    const std::string& logMessage = entry.getMessage();

	switch(token.type()) {
		case TokenType::Color :
			if(m_supportsColoring) {
				output << (static_cast<EnumColorStream>(token.length()));
			}
			break;
		
		case TokenType::Value :
			output << logMessage;
			break;

		case TokenType::Year :
			output << (date.date.tm_year + 1900);
			break;
		
		case TokenType::Month :
			output << std::setfill('0') << std::setw(2) << (date.date.tm_mon + 1);
			break;
		
		case TokenType::Day :
			output << std::setfill('0') << std::setw(2) << date.date.tm_mday;
			break;
		
		case TokenType::Hour :
			output << std::setfill('0') << std::setw(2) << date.date.tm_hour;
			break;
		
		case TokenType::Minute :
			output << std::setfill('0') << std::setw(2) << date.date.tm_min;
			break;
		
		case TokenType::Second :
			output << std::setfill('0') << std::setw(2) << date.date.tm_sec;
			break;
	
        case TokenType::MilliSecond :
            output << std::setfill('0') << std::setw(3) << date.milliseconds;
            break;

        case TokenType::Identifier:
            output << entry.getId();
            break;

		case TokenType::Class:
            output << std::setfill(' ') << std::setw(token.length()) << entry.getContext().className;
			break;
	    
        case TokenType::File:
            output << std::setfill(' ') << std::setw(token.length()) << entry.getContext().file;
            break;
        
        case TokenType::Function:
            output << std::setfill(' ') << std::setw(token.length()) << entry.getContext().function;
            break;

        case TokenType::Line:
            output << std::setfill('0') << std::setw(token.length()) << entry.getContext().line;
            break;

		case TokenType::Literal:
		    output << token.value();
			break;

		case TokenType::Empty:
			break;

		default:
			assert(false);
	}
    return true;
}

