#ifndef __CONSOLEFORMATTER_H__
#define __CONSOLEFORMATTER_H__

#include "../loglevel/loglevel_colours.hpp"
#include "format_interface.hpp"

#include "fmt/chrono.h"
#include "fmt/format.h"

namespace cyberlogger
{
    class ConsoleFormatter : public Iformatter
    {
    public:
        std::string format(const LogEntry &logEntry) const override
        {
            if (logEntry.logLevel->printDebugdata())
            {
                return fmt::format("{}[{}][{:8}][{:15}][{}:{}] {}{}\n",
                                   logEntry.logLevel->getLogLevelColourString(),
                                   logEntry.timestamp,
                                   logEntry.logLevel->getLogLevelString(),
                                   logEntry.threadName,
                                   logEntry.fileName,
                                   logEntry.sourceLine,
                                   logEntry.message,
                                   COLOUR_DEFAULT);
            }
            else
            {
                return fmt::format("{}[{}][{:8}][{:15}] {}{}\n",
                                   logEntry.logLevel->getLogLevelColourString(),
                                   logEntry.timestamp,
                                   logEntry.logLevel->getLogLevelString(),
                                   logEntry.threadName,
                                   logEntry.message,
                                   COLOUR_DEFAULT);
            }
        }
    };
}   // namespace cyberlogger

#endif   // __CONSOLEFORMATTER_H__