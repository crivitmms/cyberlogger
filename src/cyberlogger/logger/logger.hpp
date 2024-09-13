#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "../destinations/destination_interface.hpp"
#include "../queue/queue.hpp"

#include <memory>
#include <vector>

namespace cyberlogger
{

    class Logger
    {
        Queue queue;
        bool threaded = false;
        std::vector<std::unique_ptr<ILogDestination>> logdestinations;

        void print(const LogEntry &entry);
        void add(LogEntry &entry);

    public:
        void startThread();
        void stopThread();

        void log(LogEntry &entry);
        void log(LogEntry &&entry);

        void addLogDestination(std::unique_ptr<ILogDestination> &&destination);

        template <typename DestinationType, typename... Args, typename = std::enable_if_t<std::is_base_of_v<ILogDestination, DestinationType>>>
        void emplaceLogDestination(Args &&...args)
        {
            logdestinations.emplace_back(std::make_unique<DestinationType>(std::forward<Args>(args)...));
        }
    };
}   // namespace cyberlogger

#endif   // __LOGGER_H__