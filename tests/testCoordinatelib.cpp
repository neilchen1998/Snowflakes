#define CATCH_CONFIG_MAIN

#include <cmath>   // round, sqrt
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

    constexpr double x1 = 1.2, y1 = 2.4;
    Point p1(x1, y1);

    SECTION("Can Create Using the Default Constructor with Custom Values")
    {
        REQUIRE (p1.x == Approx(x1));
        REQUIRE (p1.y == Approx(y1));
    }

    constexpr double x2 = 2.59, y2 = 21.4;
    Point p2(x2, y2);

    const double expectedD = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    SECTION("Distance between Two Points")
    {
        auto d = p1.Distance(p2);
        REQUIRE (d == Approx(expectedD));
    }

    const double expectedM = sqrt(x1*2 + y1*2);
    SECTION("Magnitude of a Point")
    {
        auto d = p1.Magnitude();
        REQUIRE (d == Approx(expectedM));
    }
}