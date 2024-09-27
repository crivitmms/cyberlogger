#include "loglevel.hpp"

namespace cyberlogger
{
    bool Loglevel::printDebugdata() const
    {
        switch (_loglevel)
        {
        case UNKNOWN: return false;
        case TRACE: return true;
        case DEBUG: return true;
        case INFO: return false;
        case WARNING: return false;
        case ERROR: return false;
        case CRITICAL: return false;
        default: return false;
        }
    }

    std::string_view Loglevel::getLogLevelString() const
    {
        switch (_loglevel)
        {
        case UNKNOWN: return "UNKNOWN";
        case TRACE: return "TRACE";
        case DEBUG: return "DEBUG";
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        case CRITICAL: return "CRITICAL";
        default: return "UNKNOWN";
        }
    };

    std::string_view Loglevel::getLogLevelColourString() const
    {
        switch (_loglevel)
        {
        case UNKNOWN: return COLOUR_UNKNOWN;
        case TRACE: return COLOUR_TRACE;
        case DEBUG: return COLOUR_DEBUG;
        case INFO: return COLOUR_INFO;
        case WARNING: return COLOUR_WARNING;
        case ERROR: return COLOUR_ERROR;
        case CRITICAL: return COLOUR_CRITICAL;
        default: return COLOUR_UNKNOWN;
        }
    };

    int Loglevel::getID()
    {
        return LEVELID;
    }
    int Loglevel::getLogLevelID() const
    {
        return LEVELID;
    }
}   // namespace cyberlogger