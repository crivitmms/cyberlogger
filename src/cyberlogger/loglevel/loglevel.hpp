#ifndef __LOGLEVELPROVIDER_H__
#define __LOGLEVELPROVIDER_H__

#include "loglevel_colours.hpp"
#include "loglevel_interface.hpp"

namespace cyberlogger
{
    class Loglevel : public ILogLevel
    {
    public:
        enum class Level : int
        {
            UNKNOWN,
            TRACE,
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            CRITICAL
        };

        Loglevel(const int loglevel) :
            ILogLevel(loglevel) {};
        Loglevel(const Level level) :
            ILogLevel((int) level) {};

        std::string_view getLogLevelString() const override;

        std::string_view getLogLevelColourString() const override;
    };
}   // namespace cyberlogger

#endif   // __LOGLEVELPROVIDER_H__