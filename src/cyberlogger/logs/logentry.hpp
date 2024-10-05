#pragma once

#include "../loglevel/loglevel_interface.hpp"
#include "../util/threadname.hpp"

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
        std::string threadName;

        LogEntry(std::string_view msg, std::unique_ptr<ILogLevel> &&level, std::string_view file = "", int line = -1) :
            message(msg),
            logLevel(std::move(level)),
            timestamp(std::chrono::system_clock::now()),
            fileName(file),
            sourceLine(line),
            threadName(ThreadName())
        {
        }

        template <typename T, typename = std::enable_if_t<std::is_base_of_v<ILogLevel, T>>>
        LogEntry(std::string_view msg, T &level, std::string_view file = "", int line = -1) :
            message(msg),
            logLevel(std::make_unique<T>(level)),
            timestamp(std::chrono::system_clock::now()),
            fileName(file),
            sourceLine(line),
            threadName(ThreadName())
        {
        }

        template <typename T, typename = std::enable_if_t<std::is_base_of_v<ILogLevel, T>>>
        LogEntry(std::string_view msg, T &&level, std::string_view file = "", int line = -1) :
            message(msg),
            logLevel(std::make_unique<T>(std::move(level))),
            timestamp(std::chrono::system_clock::now()),
            fileName(file),
            sourceLine(line),
            threadName(ThreadName())
        {
        }

        LogEntry(LogEntry &&other) noexcept :
            message(std::move(other.message)),
            logLevel(std::move(other.logLevel)),
            timestamp(std::move(other.timestamp)),
            fileName(std::move(other.fileName)),
            sourceLine(other.sourceLine),
            threadName(std::move(other.threadName))
        {
        }

        LogEntry(const LogEntry &) = delete;              // Disable copy constructor
        LogEntry &operator=(const LogEntry &) = delete;   // Disable copy assignment

        ~LogEntry()
        {
        }

        private:
        std::string ThreadName()
        {
            return GetThreadName();
        }
    };

}   // namespace cyberlogger


