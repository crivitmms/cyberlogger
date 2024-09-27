#ifndef __FILEFORMATTER_H__
#define __FILEFORMATTER_H__

#include "format_interface.hpp"

#include "fmt/chrono.h"
#include "fmt/format.h"

namespace cyberlogger
{
    class FileFormatter : public Iformatter
    {
    public:
        std::string format(const LogEntry &logEntry) const override
        {
            if (logEntry.logLevel->printDebugdata())
            {
                return fmt::format("[{}][{:8}][{:15}][{}:{}] {}\n",
                                   logEntry.timestamp,
                                   logEntry.logLevel->getLogLevelString(),
                                   logEntry.threadName,
                                   logEntry.fileName,
                                   logEntry.sourceLine,
                                   logEntry.message);
            }
            else
            {
                return fmt::format("[{}][{}][{}:{}] {}\n",
                                   logEntry.timestamp,
                                   logEntry.logLevel->getLogLevelString(),
                                   logEntry.fileName,
                                   logEntry.sourceLine,
                                   logEntry.message);
            }
        }
    };
}   // namespace cyberlogger
#endif   // __FILEFORMATTER_H__