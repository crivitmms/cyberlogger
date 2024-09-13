#ifndef __LOGLEVEL_COLOURS_H__
#define __LOGLEVEL_COLOURS_H__

#include "string"

namespace cyberlogger
{

    inline constexpr const std::string_view COLOUR_DEFAULT = "\033[0m";     // Default color
    inline constexpr const std::string_view COLOUR_UNKNOWN = "\033[90m";    // Dark gray color for UNKNOWN
    inline constexpr const std::string_view COLOUR_TRACE = "\033[34m";      // Blue color for TRACE
    inline constexpr const std::string_view COLOUR_DEBUG = "\033[36m";      // Cyan color for DEBUG
    inline constexpr const std::string_view COLOUR_INFO = "\033[32m";       // Green color for INFO
    inline constexpr const std::string_view COLOUR_WARNING = "\033[33m";    // Yellow color for WARNING
    inline constexpr const std::string_view COLOUR_ERROR = "\033[31m";      // Red color for ERROR
    inline constexpr const std::string_view COLOUR_CRITICAL = "\033[35m";   // Magenta color for CRITICAL

}   // namespace cyberlogger

#endif   // __LOGLEVEL_COLOURS_H__