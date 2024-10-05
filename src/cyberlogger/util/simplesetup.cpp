#include "../destinations/streamdestination.hpp"
#include "../loglevel/loglevel.hpp"
#include "singletonwrap.hpp"
#include "../logger/logger.hpp"

#include "iostream"

#include "simplesetup.hpp"

namespace cyberlogger
{
    void setupCoutLogging()
    {
        auto cout_log_destination = std::make_unique<StreamDestination>("cout", std::shared_ptr<std::ostream>(&std::cout, [](std::ostream *) {}));
        cout_log_destination->addSupportedLevel(cyberlogger::Loglevel::getID(),
                                                {cyberlogger::Loglevel::UNKNOWN,
                                                 cyberlogger::Loglevel::TRACE,
                                                 cyberlogger::Loglevel::DEBUG,
                                                 cyberlogger::Loglevel::INFO,
                                                 cyberlogger::Loglevel::WARNING,
                                                 cyberlogger::Loglevel::ERROR,
                                                 cyberlogger::Loglevel::CRITICAL, 10});
        cyberlogger::SingleTonWrapper<cyberlogger::Logger>::getInstance()->addLogDestination(std::move(cout_log_destination));
    }
}