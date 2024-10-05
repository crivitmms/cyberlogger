#pragma once

#include "../formatter/format_interface.hpp"

#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

namespace cyberlogger
{
    class ILogDestination
    {
    protected:
        std::unordered_map<int, std::set<int>> supportedLevels;
        std::unique_ptr<Iformatter> destformatter;
        std::string destname;

    public:
        ILogDestination(const std::string_view &name, std::unique_ptr<Iformatter> formatter) :
            destformatter(std::move(formatter)),
            destname(name) {};

        std::string_view getName() const
        {
            return destname;
        }
        void addSupportedLevel(int logLevelId, int level)
        {
            supportedLevels[logLevelId].insert(level);
        }
        void addSupportedLevel(int logLevelId, std::vector<int> levels)
        {
            for (auto &&level : levels)
            {
                supportedLevels[logLevelId].insert(level);
            }
        }

        // check if loglevel is in list
        virtual void printLog(const LogEntry &logEntry) = 0;
        virtual ~ILogDestination() = default;
    };
}   // namespace cyberlogger
