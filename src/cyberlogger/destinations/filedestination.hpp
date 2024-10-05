#pragma once

#include "../formatter/fileformatter.hpp"
#include "destination_interface.hpp"

#include "convertx/convertx.hpp"

#include <filesystem>
#include <fstream>

namespace cyberlogger
{
    using namespace ConvertX;
    class FileDestination : public ILogDestination
    {
    public:
        bool is_openfile_error = false;
        bool is_archive_error = false;

    private:
        std::fstream stream;
        const std::filesystem::path filename;
        const DataSize<DataUnit::BYTES> maxsize;
        const unsigned int maxlogs = 10;
        const std::filesystem::path archivefolder;
        const std::filesystem::path archivelogger;

        DataSize<DataUnit::BYTES> filesize()
        {
            return std::filesystem::file_size(filename);
        }

        void cleanArchives(const std::filesystem::path &newArchive)
        {
            if (!std::filesystem::exists(archivelogger))
            {
                std::fstream(archivelogger, std::ios::out);
            }

            std::vector<std::filesystem::path> archivelist;
            auto archivestream = std::fstream(archivelogger, std::ios::in);
            if (!archivestream.is_open())
            {
                is_archive_error = true;
                return;
            }
            is_archive_error = false;
            std::string line;
            while (std::getline(archivestream, line))
            {
                archivelist.emplace_back(line);
            }
            archivestream.close();
            while (archivelist.size() > maxlogs - 1)
            {
                std::filesystem::remove(archivelist.back());
                archivelist.pop_back();
            }
            archivestream = std::fstream(archivelogger, std::ios::out | std::ios::trunc);
            if (!archivestream.is_open())
            {
                is_archive_error = true;
                return;
            }
            is_archive_error = false;
            archivestream << newArchive.string() << "\n";
            for (const auto &file : archivelist)
            {
                archivestream << file.string() << "\n";
            }
            archivestream.close();
        }

        void archiveFile()
        {
            if (!std::filesystem::exists(filename))
            {
                return;
            }
            const auto now = std::chrono::system_clock::now();
            const auto time_t_now = std::chrono::system_clock::to_time_t(now);
            const std::string currenttime = fmt::format("{:%Y-%m-%d-%H:%M:%S}", *std::localtime(&time_t_now));
            std::filesystem::path archivename;

            auto archivestream = std::fstream(filename);
            if (!archivestream.is_open())
            {
                is_archive_error = true;
                return;
            }
            is_archive_error = false;
            std::string timestamp;
            if (!std::getline(archivestream, timestamp))
            {
                timestamp = "voidtime";
            }

            archivename = archivefolder / (filename.stem().string() + "_" + timestamp + "_" + currenttime + ".log");
            archivestream.close();
            std::filesystem::create_directory(archivefolder);
            std::filesystem::rename(filename, archivename);
            cleanArchives(archivename);
        }

        void openFile()
        {
            stream.open(filename, std::ios::out | std::ios::app);
            if (!stream.is_open())
            {
                is_openfile_error = true;
                return;
            }
            is_openfile_error = false;
            if (filesize().equal(0))
            {
                const auto now = std::chrono::system_clock::now();
                const auto time_t_now = std::chrono::system_clock::to_time_t(now);
                const std::string currenttime = fmt::format("{:%Y-%m-%d-%H:%M:%S}", *std::localtime(&time_t_now));
                stream << currenttime + "\n";
                stream.flush();
            }
        }

        void closeFile()
        {
            stream.flush();
            stream.close();
        }

        void checkfile()
        {
            if (filesize() > maxsize)
            {
                closeFile();
                archiveFile();
                openFile();
            }
        }

    public:
        FileDestination(const std::string_view &name, const std::filesystem::path &filePath, DataSize<DataUnit::BYTES> maxfilesize = 5_mib) :
            ILogDestination(name, std::make_unique<FileFormatter>()),
            filename(filePath),
            maxsize(maxfilesize),
            archivefolder(filePath.parent_path() / "oldlogs/"),
            archivelogger(archivefolder / "archives.txt")
        {
            archiveFile();
            openFile();
        }

        void printLog(const LogEntry &logEntry) override
        {
            auto it = supportedLevels.find(logEntry.logLevel->getLogLevelID());
            if (it != supportedLevels.end())
            {
                if (it->second.count(logEntry.logLevel->getLogLevel()) > 0)
                {
                    if (!stream.is_open())
                    {
                        openFile();
                        return;
                    }
                    stream << destformatter->format(logEntry);
                    checkfile();
                }
            }
        }
        ~FileDestination()
        {
            closeFile();
        }
    };
}   // namespace cyberlogger
