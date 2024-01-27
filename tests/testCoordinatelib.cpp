#define CATCH_CONFIG_MAIN

#include <cmath>   // round
#include <catch2/catch.hpp>

#include "coordinate/coordinatelib.hpp"

TEST_CASE( "Coordinate", "Point" )
{   
    Point p0 = Point();
    SECTION("Can Create Using the Default Constructor")
    {
        REQUIRE (p0.x == Approx(0));
        REQUIRE (p0.y == Approx(0));
    }

    constexpr double x = 1.2, y = 2.4;
    Point p1(1.2, 2.4);

    SECTION("Can Create Using the Default Constructor with Custom Values")
    {
        REQUIRE (p1.x == Approx(x));
        REQUIRE (p1.y == Approx(y));
    }

    const double expectedD = sqrt(x*2 + y*2);
    SECTION("Distance between Two Points")
    {
        auto d = p1.Distance(p0);
        REQUIRE (d == Approx(expectedD));
    }
}