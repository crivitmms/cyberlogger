#include "../destinations/streamdestination.hpp"
#include "../destinations/filedestination.hpp"
#include "../loglevel/loglevel.hpp"
#include "singletonwrap.hpp"
#include "../logger/logger.hpp"

#include "iostream"
#include "filesystem"

#include "simplesetup.hpp"

namespace cyberlogger
{
    void setupCoutLogging()
    {
        auto log_destination = std::make_unique<StreamDestination>("cout", std::shared_ptr<std::ostream>(&std::cout, [](std::ostream *) {}));
        log_destination->addSupportedLevel(cyberlogger::Loglevel::getID(),
                                                {cyberlogger::Loglevel::UNKNOWN,
                                                 cyberlogger::Loglevel::TRACE,
                                                 cyberlogger::Loglevel::DEBUG,
                                                 cyberlogger::Loglevel::INFO,
                                                 cyberlogger::Loglevel::WARNING,
                                                 cyberlogger::Loglevel::ERROR,
                                                 cyberlogger::Loglevel::CRITICAL, 10});
        cyberlogger::SingleTonWrapper<cyberlogger::Logger>::getInstance()->addLogDestination(std::move(log_destination));
    }

    void setupFileLogging(const std::filesystem::path &file)
    {
        auto log_destination = std::make_unique<FileDestination>(file.stem().string(), file);
        log_destination->addSupportedLevel(cyberlogger::Loglevel::getID(),
                                                {cyberlogger::Loglevel::UNKNOWN,
                                                 cyberlogger::Loglevel::TRACE,
                                                 cyberlogger::Loglevel::DEBUG,
                                                 cyberlogger::Loglevel::INFO,
                                                 cyberlogger::Loglevel::WARNING,
                                                 cyberlogger::Loglevel::ERROR,
                                                 cyberlogger::Loglevel::CRITICAL, 10});
        cyberlogger::SingleTonWrapper<cyberlogger::Logger>::getInstance()->addLogDestination(std::move(log_destination));
    }
}