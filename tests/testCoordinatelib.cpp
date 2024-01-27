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

    SECTION("Univt Vector")
    {
        auto u = p1.Unit();
        REQUIRE (u.x == Approx(x1 / expectedM));
        REQUIRE (u.y == Approx(y1 / expectedM));
    }

    constexpr double x3 = 2.59, y3 = 21.4;
    Point p3(x3, y3);

    SECTION("Adding Two Vectors")
    {
        auto ret = p3 + p2;

        // ensures that new p3 equals to old p3 plus p2
        REQUIRE (ret.x == Approx(x3 + x2));
        REQUIRE (ret.y == Approx(y3 + y2));

        // ensures that p2 remains the same
        REQUIRE (p2.x == Approx(x2));
        REQUIRE (p2.y == Approx(y2));

        // ensures that p3 remains the same
        REQUIRE (p3.x == Approx(x3));
        REQUIRE (p3.y == Approx(y3));
    }

    SECTION("Subtracting Two Vectors")
    {
        auto ret = p3 - p2;

        // ensures that new p3 equals to old p3 plus p2
        REQUIRE (ret.x == Approx(x3 - x2));
        REQUIRE (ret.y == Approx(y3 - y2));

        // ensures that p2 remains the same
        REQUIRE (p2.x == Approx(x2));
        REQUIRE (p2.y == Approx(y2));

        // ensures that p3 remains the same
        REQUIRE (p3.x == Approx(x3));
        REQUIRE (p3.y == Approx(y3));
    }

    constexpr double x4 = 2.59, y4 = 21.4;
    Point p4(x4, y4);

    SECTION("Adding Two Vectors (+=)")
    {
        p4 += p2;

        // ensures that new p3 equals to old p3 plus p2
        REQUIRE (p4.x == Approx(x4 + x2));
        REQUIRE (p4.y == Approx(y4 + y2));

        // ensures that p2 remains the same
        REQUIRE (p2.x == Approx(x2));
        REQUIRE (p2.y == Approx(y2));
    }

    constexpr double x5 = 52.2, y5 = 728.4;
    Point p5(x5, y5);

    SECTION("Subtracting Two Vectors (-=)")
    {
        p5 -= p2;

        // ensures that new p3 equals to old p3 plus p2
        REQUIRE (p5.x == Approx(x5 - x2));
        REQUIRE (p5.y == Approx(y5 - y2));

        // ensures that p2 remains the same
        REQUIRE (p2.x == Approx(x2));
        REQUIRE (p2.y == Approx(y2));
    }

    constexpr double x6 = 1.2, y6 = 94.4;
    constexpr double c = 4.2;
    Point p6(x6, y6);

    SECTION("Multiplying a Scalar")
    {
        auto ret = p6 * c;

        // ensures that we can multiple a positive scalar
        REQUIRE (ret.x == Approx(x6 * c));
        REQUIRE (ret.y == Approx(y6 * c));

        ret = p6 * -c;

        // ensures that we can multiple a negative scalar
        REQUIRE (ret.x == Approx(x6 * -c));
        REQUIRE (ret.y == Approx(y6 * -c));

        ret = c * p6;

        // ensures that we can multiple a negative scalar
        REQUIRE (ret.x == Approx(x6 * c));
        REQUIRE (ret.y == Approx(y6 * c));
    }

    SECTION("Multiplying a Scalar (*=)")
    {
        p6 *= c;

        // ensures that we can multiple a positive scalar
        REQUIRE (p6.x == Approx(x6 * c));
        REQUIRE (p6.y == Approx(y6 * c));

        p6 *= -c;

        // ensures that we can multiple a negative scalar
        REQUIRE (p6.x == Approx(x6 * c * -c));
        REQUIRE (p6.y == Approx(y6 * c * -c));
    }

    SECTION("Comparing Two Points")
    {
        // same point
        auto p6_copied = Point(x6, y6);
        REQUIRE (p6 == p6_copied);

        // different x and y values
        REQUIRE (p6 != p5);

        // same x value, different y value
        auto p6_x = Point(x6, 1.2);
        REQUIRE (p6 != p6_x);
        
        // same y value, different x value
        auto p6_y = Point(4.9, y6);
        REQUIRE (p6 != p6_y);
    }
}
