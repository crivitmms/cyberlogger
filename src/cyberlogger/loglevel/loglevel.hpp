#ifndef __LOGLEVELPROVIDER_H__
#define __LOGLEVELPROVIDER_H__

#include "loglevel_colours.hpp"
#include "loglevel_interface.hpp"

namespace cyberlogger
{
    class Loglevel : public ILogLevel
    {
        static constexpr int LEVELID = 0;

    public:
        static constexpr int UNKNOWN = 0;
        static constexpr int TRACE = 1;
        static constexpr int DEBUG = 2;
        static constexpr int INFO = 3;
        static constexpr int WARNING = 4;
        static constexpr int ERROR = 5;
        static constexpr int CRITICAL = 6;

        Loglevel(const int loglevel) :
            ILogLevel(loglevel) {};

        bool printDebugdata() const override;

        std::string_view getLogLevelString() const override;
        std::string_view getLogLevelColourString() const override;
        static int getID();
        int getLogLevelID() const override;
    };
}   // namespace cyberlogger

#endif   // __LOGLEVELPROVIDER_H__