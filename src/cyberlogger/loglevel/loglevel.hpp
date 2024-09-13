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
            ILogLevel((int)level) {};

        constexpr std::string_view getLogLevelString() const override
        {
            switch (static_cast<Level>(_loglevel))
            {
            case Level::UNKNOWN: return "UNKNOWN";
            case Level::TRACE: return "TRACE";
            case Level::DEBUG: return "DEBUG";
            case Level::INFO: return "INFO";
            case Level::WARNING: return "WARNING";
            case Level::ERROR: return "ERROR";
            case Level::CRITICAL: return "CRITICAL";
            default: return "UNKNOWN";
            }
        }

        constexpr std::string_view getLogLevelColourString() const override
        {
            switch (static_cast<Level>(_loglevel))
            {
            case Level::UNKNOWN: return COLOUR_UNKNOWN;
            case Level::TRACE: return COLOUR_TRACE;
            case Level::DEBUG: return COLOUR_DEBUG;
            case Level::INFO: return COLOUR_INFO;
            case Level::WARNING: return COLOUR_WARNING;
            case Level::ERROR: return COLOUR_ERROR;
            case Level::CRITICAL: return COLOUR_CRITICAL;
            default: return COLOUR_UNKNOWN;
            }
        }
    };
}   // namespace cyberlogger

#endif   // __LOGLEVELPROVIDER_H__