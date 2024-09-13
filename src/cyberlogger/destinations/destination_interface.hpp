#ifndef __DESTINATION_INTERFACE_H__
#define __DESTINATION_INTERFACE_H__

#include "../formatter/format_interface.hpp"

#include <iostream>
#include <memory>
#include <vector>

namespace cyberlogger
{
    class ILogDestination
    {
    protected:
        std::string destname;
        std::vector<int> destLoglevelList;
        std::unique_ptr<Iformatter> destformatter;

    public:
        ILogDestination(const std::string_view &name, const std::vector<int> &loglevels, std::unique_ptr<Iformatter> formatter) :
            destformatter(std::move(formatter)),
            destLoglevelList(std::move(loglevels)),
            destname(name) {};

        std::string_view getName() const
        {
            return destname;
        }

        // check if loglevel is in list
        virtual void printLog(const LogEntry &logEntry) = 0;
        virtual ~ILogDestination() = default;
    };
}   // namespace cyberlogger

#endif   // __DESTINATION_INTERFACE_H__