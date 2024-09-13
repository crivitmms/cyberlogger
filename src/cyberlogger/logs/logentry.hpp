#ifndef __LOGENTRY_H__
#define __LOGENTRY_H__

#include "../loglevel/loglevel_interface.hpp"

#include "memory"

#include "chrono"

namespace cyberlogger
{
    struct LogEntry
    {
        std::string message;
        std::unique_ptr<ILogLevel> logLevel;
        std::chrono::system_clock::time_point timestamp;
        std::string fileName;
        int sourceLine;

        LogEntry(std::string msg, std::unique_ptr<ILogLevel> &&level, std::string_view file = "", int line = -1) :
            message(msg),
            logLevel(std::move(level)),
            timestamp(std::chrono::system_clock::now()),
            fileName(file),
            sourceLine(line) {};
        LogEntry(LogEntry &&other) noexcept :
            message(std::move(other.message)),
            logLevel(std::move(other.logLevel)),
            timestamp(std::move(other.timestamp)),
            fileName(std::move(other.fileName)),
            sourceLine(other.sourceLine)
        {
        }
    };

}   // namespace cyberlogger

#endif   // __LOGENTRY_H__
