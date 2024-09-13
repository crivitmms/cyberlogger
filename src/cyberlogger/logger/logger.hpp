#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "../destinations/destination_interface.hpp"

#include <memory>
#include <vector>

namespace cyberlogger
{

    class logger
    {
        // TODO: queue
        // TODO: thread handler

    public:
        std::vector<std::unique_ptr<cyberlogger::ILogDestination>> logdestinations;
    
        void log(std::unique_ptr<LogEntry> &&entry)
        {
            for(const auto &dest : logdestinations)
            {
                dest->printLog(entry.get());
            }
        };
        logger() {};
    };
}   // namespace cyberlogger

#endif   // __LOGGER_H__