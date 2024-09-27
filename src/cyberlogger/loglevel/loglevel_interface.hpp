#ifndef __LOGLEVEL_INTERFACE_H__
#define __LOGLEVEL_INTERFACE_H__

#include "iostream"
#include "string"

namespace cyberlogger
{
    class ILogLevel
    {
    protected:
        int _loglevel;

    public:
        virtual ~ILogLevel() = default;
        constexpr ILogLevel(const int loglevel) :
            _loglevel(loglevel) {};
        constexpr int getLogLevel() const
        {
            return _loglevel;
        };
        virtual bool printDebugdata() const = 0;
        virtual std::string_view getLogLevelString() const = 0;
        virtual std::string_view getLogLevelColourString() const = 0;
        virtual int getLogLevelID() const = 0;
    };
}   // namespace cyberlogger

#endif   // __LOGLEVEL_INTERFACE_H__