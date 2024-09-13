#include "queue.hpp"

namespace cyberlogger
{

    void Queue::threadTask(std::stop_token stopToken)
    {
        while (!stopToken.stop_requested())
        {
            std::unique_lock<std::mutex> lock(mutex);
            if (!cv.wait_for(lock, waitTimeout, [this, &stopToken] { return !logs.empty() || stopToken.stop_requested(); }))
            {
                continue;
            }
            std::vector<LogEntry> entries;
            entries.reserve(logs.size());
            while (!logs.empty())
            {
                entries.push_back(std::move(logs.front()));   // Move log entry to local vector
                logs.pop();
            }
            lock.unlock();

            for (auto &entry : entries)
            {
                _printFunction(entry);
            }
        }
        while (!logs.empty())
        {
            _printFunction(logs.front());
            logs.pop();
        }
    };

    void Queue::startThread(const std::function<void(LogEntry &logEntry)> &printFunction, long unsigned int threshold,
                            std::chrono::milliseconds waittime)
    {
        stopThread();
        waitTimeout = waittime;
        notifyThreshold = threshold;
        _printFunction = printFunction;
        printThread = std::jthread(std::bind(&Queue::threadTask, this, std::placeholders::_1));
    };

    void Queue::stopThread()
    {
        if (printThread.joinable())
        {
            printThread.request_stop();
            cv.notify_one();
            printThread.join();
        }
    };

    void Queue::addQueue(LogEntry &entry)
    {
        std::unique_lock<std::mutex> lock(mutex);
        logs.emplace(std::move(entry));
        if (logs.size() >= notifyThreshold)
        {
            lock.unlock();
            cv.notify_one();
        }
    };

    Queue::~Queue()
    {
        stopThread();
    };

}   // namespace cyberlogger