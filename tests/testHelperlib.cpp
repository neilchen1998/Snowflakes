#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "helper/fmtlib.hpp"

TEST_CASE( "Formatter", "[main]" )
{
    const double x = 1.123456;
    const double y = 125.123456;

    SECTION("Default Precision")
    {
        REQUIRE (Formatter(x) == "1.12");
        REQUIRE (Formatter(y) == "125");
    }

    SECTION("Custom Precision")
    {
        const int p = 4;
        REQUIRE (Formatter(x, p) == "1.123");
        REQUIRE (Formatter(y, p) == "125.1");
    }
}