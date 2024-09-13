#ifndef __FORMAT_INTERFACE_H__
#define __FORMAT_INTERFACE_H__

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

#endif   // __FORMAT_INTERFACE_H__