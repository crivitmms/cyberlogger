#include "catch2/catch_test_macros.hpp"


#include "cyberlogger/loglevel/loglevel.hpp"

#include "cyberlogger/logs/easy_logentry.hpp"
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
        auto l = Logger();

        l.stopThread();
        l.startThread();

        auto x = LogEntryDefault("hej", Loglevel::ERROR);

        auto os = std::make_shared<std::ostringstream>();
        auto os2 = std::make_unique<std::ostringstream>();

        auto iptr = LogEntry("hej", Loglevel(Loglevel::ERROR));

        l.emplaceLogDestination<StreamDestination>("test", std::move(os2));
        auto sd = std::make_unique<StreamDestination>("test2", os);
        auto sd3 =
            std::make_unique<StreamDestination>("test3", std::shared_ptr<std::ostream>(&std::cout, [](std::ostream *) {}));

        // auto fd = std::make_unique<FileDestination>("file", "./test.txt");
        // sd->addSupportedLevel(Loglevel::getID(), {Loglevel::UNKNOWN, Loglevel::ERROR });
        // fd->addSupportedLevel(Loglevel::getID(), {Loglevel::UNKNOWN, Loglevel::ERROR });

        l.addLogDestination(std::move(sd));
        l.addLogDestination(std::move(sd3));
        // l.addLogDestination(std::move(fd));

        for (size_t i = 0; i < 2; i++)
        {

            l.log(LogEntryDefault("hej0", Loglevel::UNKNOWN));
            l.log(LogEntryDefault("hej1", Loglevel::TRACE));
            l.log(LogEntryDefault("hej2", Loglevel::DEBUG));
            l.log(LogEntryDefault("hej3", Loglevel::INFO));
            l.log(LogEntryDefault("hej4", Loglevel::WARNING));
            l.log(x);
            l.log(LogEntryDefault("hej10", Loglevel::CRITICAL));
            l.log(LogEntryDefault("hej10", 10));

            l.log(iptr);
        }

        std::string osstring = os->str();
        std::cout << osstring;
    }
}