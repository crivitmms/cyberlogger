#pragma once

#include "string"

#include "../logs/logentry.hpp"

namespace cyberlogger
{
    class Iformatter {
    public:
        virtual ~Iformatter() = default;
        virtual std::string format(const LogEntry &logEntry) const = 0;
    };

}   // namespace cyberlogger
