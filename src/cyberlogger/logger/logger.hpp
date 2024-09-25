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
        std::vector<std::unique_ptr<ILogDestination>> logdestinations;
        Queue queue;
        bool threaded = false;

        void print(const LogEntry &entry);
        void add(LogEntry &entry);

    public:
        void startThread();
        void stopThread();
        bool isThreaded();

        void log(LogEntry &entry);
        void log(LogEntry &&entry);

        void addLogDestination(std::unique_ptr<ILogDestination> &&destination);

        template <typename DestinationType, typename... Args, typename = std::enable_if_t<std::is_base_of_v<ILogDestination, DestinationType>>>
        void emplaceLogDestination(Args &&...args)
        {
            logdestinations.emplace_back(std::make_unique<DestinationType>(std::forward<Args>(args)...));
        }

        int getLogDestinationCount() const;
        void removeLogDestination(const std::string_view name);

        ~Logger();
    };
}   // namespace cyberlogger

#endif   // __LOGGER_H__