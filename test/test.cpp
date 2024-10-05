#include "catch2/catch_test_macros.hpp"


#include "cyberlogger/loglevel/loglevel.hpp"

#include "cyberlogger/cyberlogger.hpp"
#include "cyberlogger/logs/logentry.hpp"

#include "cyberlogger/logger/logger.hpp"

#include "cyberlogger/formatter/consoleformatter.hpp"

#include "cyberlogger/destinations/filedestination.hpp"
#include "cyberlogger/destinations/streamdestination.hpp"

#include <iostream>
#include <sstream>

using namespace cyberlogger;

TEST_CASE("test ground") {
    {
        // auto l = Logger();
        auto l = CL_LOGGER;

        l->stopThread();
        // l->startThread();

        auto x = CL_LOGENTRYDEFAULT("hej", Loglevel::ERROR);

        auto os = std::make_shared<std::ostringstream>();
        auto os2 = std::make_unique<std::ostringstream>();

        auto iptr = LogEntry("hej", Loglevel(Loglevel::ERROR));

        l->emplaceLogDestination<StreamDestination>("test", std::move(os2));
        auto sd = std::make_unique<StreamDestination>("test2", os);

        // auto cout_log_destination = std::make_unique<StreamDestination>("cout", std::shared_ptr<std::ostream>(&std::cout, [](std::ostream *) {}));
        // cout_log_destination->addSupportedLevel(cyberlogger::Loglevel::getID(),{ cyberlogger::Loglevel::UNKNOWN , cyberlogger::Loglevel::TRACE , cyberlogger::Loglevel::DEBUG , cyberlogger::Loglevel::INFO , cyberlogger::Loglevel::WARNING , cyberlogger::Loglevel::ERROR , cyberlogger::Loglevel::CRITICAL });
        // LOGGER->addLogDestination(std::move(cout_log_destination));

        setupCoutLogging();

        // auto fd = std::make_unique<FileDestination>("file", "./test.txt");
        // fd->addSupportedLevel(DEFAULT_LOGLEVEL_CONF);
        // sd->addSupportedLevel(Loglevel::getID(), {Loglevel::UNKNOWN, Loglevel::ERROR });
        // fd->addSupportedLevel(Loglevel::getID(), {Loglevel::UNKNOWN, Loglevel::ERROR });

        l->addLogDestination(std::move(sd));
        // l.addLogDestination(std::move(fd));

        for (size_t i = 0; i < 100; i++)
        {

            LOG_UNKNOWN("hej0");
            LOG_TRACE("hej1");
            LOG_DEBUG("hej2");
            LOG_INFO("hej3");
            LOG_WARNING("hej4");
            l->log(x);
            LOG_CRITICAL("hej10");
            l->log(CL_LOGENTRYDEFAULT("hej10", 10));

            LOG_DEBUG("easy test log");

            l->log(iptr);
        }

        std::string osstring = os->str();
        std::cout << osstring;


        std::jthread([&]{
            SetThreadName("SHIT Thread");
            LOG_DEBUG("from thread");
        });



        
    }
}