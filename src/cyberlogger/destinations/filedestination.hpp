#ifndef __FILEDESTINATION_H__
#define __FILEDESTINATION_H__

#include "../formatter/fileformatter.hpp"
#include "destination_interface.hpp"

#include <filesystem>
#include <fstream>

namespace cyberlogger
{
    class FileDestination : public ILogDestination
    {
        std::fstream stream;
        std::filesystem::path filename;

        void openFile()
        {
            stream.open(filename, std::ios::out | std::ios::app);
            if(!stream.is_open())
            {
                throw std::runtime_error("file not open");
            }
        }

    public:
        FileDestination(const std::string_view &name, const std::filesystem::path &filePath) :
            ILogDestination(name, std::make_unique<FileFormatter>()),
            filename(filePath)
        {
            openFile();
        }
        void printLog(const LogEntry &logEntry) override
        {
            auto it = supportedLevels.find(logEntry.logLevel->getLogLevelID());
            if(it != supportedLevels.end())
            {
                if(it->second.count(logEntry.logLevel->getLogLevel()) > 0)
                {
                    stream << destformatter->format(logEntry);
                }
            }
        }
        ~FileDestination()
        {
            stream.flush();
        }
    };
}   // namespace cyberlogger

#endif   // __FILEDESTINATION_H__