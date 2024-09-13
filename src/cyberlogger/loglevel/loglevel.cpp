#include "loglevel.hpp"

namespace cyberlogger
{
    std::string_view Loglevel::getLogLevelString() const
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
    };

    std::string_view Loglevel::getLogLevelColourString() const
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
    };
}   // namespace cyberlogger