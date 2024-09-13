#ifndef __CONSOLEDESTINATION_H__
#define __CONSOLEDESTINATION_H__

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
        StreamDestination(const std::string_view &name, const std::vector<int> &loglevels, const std::shared_ptr<std::ostream> &stream) :
            ILogDestination(name, loglevels, std::make_unique<ConsoleFormatter>()),
            _stream(stream)
        {
        }
        void printLog(const LogEntry &logEntry) override
        {
            *_stream << destformatter->format(logEntry);
        }
    };
}   // namespace cyberlogger

#endif   // __CONSOLEDESTINATION_H__