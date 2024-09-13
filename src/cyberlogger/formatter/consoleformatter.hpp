#ifndef __CONSOLEFORMATTER_H__
#define __CONSOLEFORMATTER_H__

#include "format_interface.hpp"

#include "fmt/chrono.h"
#include "fmt/format.h"

namespace cyberlogger
{
    class ConsoleFormatter : public Iformatter
    {
    public:
        std::string format(const LogEntry *logEntry) const override
        {
            return fmt::format("{}[{}][{}][{}/{}] {}{}\n",
                               logEntry->logLevel->getLogLevelColourString(),
                               logEntry->timestamp,
                               logEntry->logLevel->getLogLevelString(),
                               logEntry->fileName,
                               logEntry->sourceLine,
                               logEntry->message,
                               COLOUR_DEFAULT
                               );
        }
    };
}   // namespace cyberlogger

#endif   // __CONSOLEFORMATTER_H__