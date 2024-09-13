#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "../logs/logentry.hpp"

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace cyberlogger
{
    constexpr std::chrono::milliseconds DEFAULT_WAIT_TIME{100};
    class Queue
    {
        std::queue<LogEntry> logs;
        std::mutex mutex;
        std::condition_variable cv;
        std::jthread printThread;
        std::chrono::milliseconds waitTimeout;
        long unsigned int notifyThreshold;
        std::function<void(LogEntry &logEntry)> _printFunction;

        void threadTask(std::stop_token stopToken)
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
        }

    public:
        Queue()
        {
            _printFunction = [](LogEntry &logEntry) {
            };
        }

        void startThread(const std::function<void(LogEntry &logEntry)> &printFunction, long unsigned int threshold = 100,
                         std::chrono::milliseconds waittime = DEFAULT_WAIT_TIME)
        {
            stopThread();
            waitTimeout = waittime;
            notifyThreshold = threshold;
            _printFunction = printFunction;
            printThread = std::jthread(std::bind(&Queue::threadTask, this, std::placeholders::_1));
        };

        void stopThread()
        {
            if (printThread.joinable())
            {
                printThread.request_stop();
                cv.notify_one();
                printThread.join();
            }
        };

        void addQueue(LogEntry &entry)
        {
            std::unique_lock<std::mutex> lock(mutex);
            logs.emplace(std::move(entry));
            if (logs.size() >= notifyThreshold)
            {
                lock.unlock();
                cv.notify_one();
            }
        }

        ~Queue()
        {
            stopThread();
        }
    };
}   // namespace cyberlogger

#endif   // __QUEUE_H__