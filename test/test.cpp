
#include "cyberlogger/loglevel/loglevel.hpp"

#include "cyberlogger/logs/easy_logentry.hpp"
#include "cyberlogger/logs/logentry.hpp"

#include "cyberlogger/logger/logger.hpp"

#include "cyberlogger/formatter/consoleformatter.hpp"

#include "cyberlogger/destinations/streamdestination.hpp"
#include "cyberlogger/destinations/filedestination.hpp"

#include <iostream>
#include <sstream>

using namespace cyberlogger;



int main(/*int args, char ** */)
{
    {
    auto l = logger();

    l.startThread();


    auto x = LogEntryDefault("hej", Loglevel::Level::ERROR);

    auto os = std::make_shared<std::ostringstream>();
    auto os2 = std::make_unique<std::ostringstream>();

    

    auto iptr = LogEntry("hej", Loglevel(Loglevel::Level::ERROR));


    l.logdestinations.emplace_back(std::make_unique<StreamDestination>("test", std::vector<int>{0, 1, 2}, std::move(os2)));
    auto sd = std::make_unique<StreamDestination>("test2", std::vector<int>{0, 1, 2}, os);
    auto sd3 = std::make_unique<StreamDestination>("test3", std::vector<int>{0, 1, 2}, std::shared_ptr<std::ostream>(&std::cout,[](std::ostream*){}));

    auto fd = std::make_unique<FileDestination>("file",std::vector<int>{0, 1, 2}, "./test.txt");

    l.logdestinations.push_back(std::move(sd));
    l.logdestinations.push_back(std::move(sd3));
    l.logdestinations.push_back(std::move(fd));

    for (size_t i = 0; i < 2; i++)
    {
    
    l.log(LogEntryDefault("hej0", Loglevel::Level::UNKNOWN));
    l.log(LogEntryDefault("hej1", Loglevel::Level::TRACE));
    l.log(LogEntryDefault("hej2", Loglevel::Level::DEBUG));
    l.log(LogEntryDefault("hej3", Loglevel::Level::INFO));
    l.log(LogEntryDefault("hej4", Loglevel::Level::WARNING));
    l.log(x);
    l.log(LogEntryDefault("hej10", Loglevel::Level::CRITICAL));
    l.log(LogEntryDefault("hej10", 10));

    l.log(iptr);
    }

    std::string osstring = os->str();
    std::cout << osstring;

    }


    return 0;
}