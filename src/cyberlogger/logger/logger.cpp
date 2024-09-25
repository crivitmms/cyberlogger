#include "logger.hpp"

namespace cyberlogger
{
    void Logger::print(const LogEntry &entry)
    {
        for (const auto &dest : logdestinations)
        {
            dest->printLog(entry);
        }
    }

    void Logger::add(LogEntry &entry)
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

    void Logger::startThread()
    {
        threaded = true;
        queue.startThread(std::bind(&Logger::print, this, std::placeholders::_1));
    }

    void Logger::stopThread()
    {
        threaded = false;
        queue.stopThread();
    }

    bool Logger::isThreaded()
    {
        return threaded;
    }

    void Logger::log(LogEntry &entry)
    {
        add(entry);
    };
    void Logger::log(LogEntry &&entry)
    {
        add(entry);
    };

    void Logger::addLogDestination(std::unique_ptr<cyberlogger::ILogDestination> &&destination)
    {
        logdestinations.push_back(std::move(destination));
    }

    int Logger::getLogDestinationCount() const
    {
        return logdestinations.size();
    }

    void Logger::removeLogDestination(const std::string_view name)
    {
        std::erase_if(logdestinations, [name](const std::unique_ptr<cyberlogger::ILogDestination> &dest) { return name == dest->getName(); });
    }

    Logger::~Logger()
    {
        stopThread();
    }

}   // namespace cyberlogger
