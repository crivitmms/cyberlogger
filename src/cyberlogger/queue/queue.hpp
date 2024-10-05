#pragma once

#include "../logs/logentry.hpp"

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

namespace cyberlogger
{
    class Queue
    {
        std::queue<LogEntry> logs;
        std::mutex mutex;
        std::condition_variable cv;
        std::jthread printThread;
        std::chrono::milliseconds waitTimeout;
        long unsigned int notifyThreshold;
        std::function<void(LogEntry &logEntry)> _printFunction = []([[maybe_unused]] LogEntry &logEntry) {
        };
        void threadTask(std::stop_token stopToken);
    public:
        static constexpr std::chrono::milliseconds DEFAULT_WAIT_TIME{100};

        void startThread(const std::function<void(LogEntry &logEntry)> &printFunction, long unsigned int threshold = 100,
                         std::chrono::milliseconds waittime = DEFAULT_WAIT_TIME);
        void stopThread();
        void addQueue(LogEntry &entry);

        ~Queue();
    };
}   // namespace cyberlogger

