#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "../destinations/destination_interface.hpp"
#include "../queue/queue.hpp"

#include <memory>
#include <vector>

namespace cyberlogger
{

    class logger
    {
        Queue queue;
        bool threaded = false;

    private:
        void print(const LogEntry &entry)
        {
            for (const auto &dest : logdestinations)
            {
                dest->printLog(entry);
            }
        }

        void add(LogEntry &entry)
        {
            if (threaded)
            {
                queue.addQueue(entry);
            }
            else
            {
                print(entry);
            }
        }

    public:
        std::vector<std::unique_ptr<cyberlogger::ILogDestination>> logdestinations;

        void startThread()
        {
            threaded = true;
            queue.startThread(std::bind(&logger::print, this, std::placeholders::_1));
        }
        void stopThread()
        {
            threaded = false;
            queue.stopThread();
        }

        void log(LogEntry &entry)
        {
            print(entry);
        };
        void log(LogEntry &&entry)
        {
            print(entry);
        };
        logger() {};
    };
}   // namespace cyberlogger

#endif   // __LOGGER_H__