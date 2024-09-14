
#include "cyberlogger/cyberlogger.hpp"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("Logger Default Initialization") {
    cyberlogger::Logger logger;

    REQUIRE_FALSE(logger.isThreaded());
    REQUIRE(logger.getLogDestinationCount() == 0);
}


TEST_CASE("Logger Add Log Destination") {
    cyberlogger::Logger logger;
    auto oss = std::make_shared<std::ostringstream>();

    auto destination = std::make_unique<cyberlogger::StreamDestination>("test", oss);
    logger.addLogDestination(std::move(destination));

    // Assert that the destination is added
    REQUIRE(logger.getLogDestinationCount() == 1);
}