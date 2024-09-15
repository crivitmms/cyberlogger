
#include "cyberlogger/cyberlogger.hpp"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("Logger Default Initialization")
{
    cyberlogger::Logger logger;

    REQUIRE_FALSE(logger.isThreaded());
    REQUIRE(logger.getLogDestinationCount() == 0);
}

TEST_CASE("Logger Add/Delete Log Destination")
{
    cyberlogger::Logger logger;

    auto destname1 = "test1";
    auto destname2 = "test2";
    auto oss = std::make_shared<std::ostringstream>();

    SECTION("Add Log Destinations")
    {
        auto destination = std::make_unique<cyberlogger::StreamDestination>(destname1, oss);
        logger.addLogDestination(std::move(destination));

        REQUIRE(logger.getLogDestinationCount() == 1);

        logger.emplaceLogDestination<cyberlogger::StreamDestination>(destname2, oss);

        REQUIRE(logger.getLogDestinationCount() == 2);

        SECTION("Delete Log Destinations")
        {
            logger.removeLogDestination(destname1);
            REQUIRE(logger.getLogDestinationCount() == 1);

            logger.removeLogDestination("randomname");
            REQUIRE(logger.getLogDestinationCount() == 1);

            logger.removeLogDestination(destname2);
            REQUIRE(logger.getLogDestinationCount() == 0);
        }
    }
}

TEST_CASE("Threaded logging")
{
    cyberlogger::Logger logger;
    auto oss = std::make_shared<std::ostringstream>();
    auto destination = std::make_unique<cyberlogger::StreamDestination>("threadtest", oss);
    destination->addSupportedLevel(cyberlogger::Loglevel::getID(), {cyberlogger::Loglevel::UNKNOWN, cyberlogger::Loglevel::ERROR});
    logger.addLogDestination(std::move(destination));

    auto msg1 = "test message 1";
    auto msg2 = "test message 2";

    SECTION("Start/Stop threading")
    {
        logger.startThread();
        REQUIRE(logger.isThreaded() == true);
        logger.stopThread();
        REQUIRE(logger.isThreaded() == false);
    }

    SECTION("logs")
    {
        logger.log(cyberlogger::LogEntry(msg1, cyberlogger::Loglevel(cyberlogger::Loglevel::UNKNOWN)));
        logger.log(cyberlogger::LogEntry(msg2, cyberlogger::Loglevel(cyberlogger::Loglevel::ERROR)));

        std::string logstring = oss->str();

        REQUIRE(logstring.find(msg1) != std::string::npos);
        REQUIRE(logstring.find(msg2) != std::string::npos);

        REQUIRE(logstring.find(msg1) < logstring.find(msg2));
    }

    SECTION("log threading")
    {
        logger.startThread();

        REQUIRE(logger.isThreaded() == true);

        logger.log(cyberlogger::LogEntry(msg1, cyberlogger::Loglevel(cyberlogger::Loglevel::UNKNOWN)));
        logger.log(cyberlogger::LogEntry(msg2, cyberlogger::Loglevel(cyberlogger::Loglevel::ERROR)));

        logger.stopThread();

        REQUIRE(logger.isThreaded() == false);

        std::string logstring = oss->str();

        REQUIRE(logstring.find(msg1) != std::string::npos);
        REQUIRE(logstring.find(msg2) != std::string::npos);

        REQUIRE(logstring.find(msg1) < logstring.find(msg2));
    }
}
