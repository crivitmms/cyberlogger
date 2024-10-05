#pragma once

#include "../formatter/consoleformatter.hpp"
#include "destination_interface.hpp"

#include <iostream>
#include <string>

namespace cyberlogger
{
    class StreamDestination : public ILogDestination
    {
        std::shared_ptr<std::ostream> _stream;

    public:
        StreamDestination(const std::string_view &name, const std::shared_ptr<std::ostream> &stream) :
            ILogDestination(name, std::make_unique<ConsoleFormatter>()),
            _stream(stream)
        {
        }
        void printLog(const LogEntry &logEntry) override
        {
            auto it = supportedLevels.find(logEntry.logLevel->getLogLevelID());
            if (it != supportedLevels.end())
            {
                if (it->second.count(logEntry.logLevel->getLogLevel()) > 0)
                {
                    *_stream << destformatter->format(logEntry);
                }
            }
        }
    };
}   // namespace cyberlogger
