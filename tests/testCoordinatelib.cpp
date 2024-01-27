#define CATCH_CONFIG_MAIN

#include <cmath>   // round, sqrt
#include <catch2/catch.hpp>

#include "coordinate/vectorlib.hpp"

TEST_CASE( "Coordinate", "Vector" )
{   
    Vector v0 = Vector();
    SECTION("Can Create Using the Default Constructor")
    {
        REQUIRE (v0.x == Approx(0));
        REQUIRE (v0.y == Approx(0));
    }

    constexpr double x1 = 1.2, y1 = 2.4;
    Vector v1(x1, y1);

    SECTION("Can Create Using the Default Constructor with Custom Values")
    {
        REQUIRE (v1.x == Approx(x1));
        REQUIRE (v1.y == Approx(y1));
    }

    constexpr double x2 = 2.59, y2 = 21.4;
    Vector v2(x2, y2);

    const double expectedD = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
    SECTION("Distance between Two Vectors")
    {
        auto d = v1.Distance(v2);
        REQUIRE (d == Approx(expectedD));
    }

    const double expectedM = sqrt(x1*2 + y1*2);
    SECTION("Magnitude of a Vector")
    {
        auto d = v1.Magnitude();
        REQUIRE (d == Approx(expectedM));
    }

    SECTION("Univt Vector")
    {
        auto u = v1.Unit();
        REQUIRE (u.x == Approx(x1 / expectedM));
        REQUIRE (u.y == Approx(y1 / expectedM));
    }

    constexpr double x3 = 2.59, y3 = 21.4;
    Vector v3(x3, y3);

    SECTION("Adding Two Vectors")
    {
        // ensures that new v3 equals to old v3 plus v2
        auto ret = v3 + v2;
        REQUIRE (ret.x == Approx(x3 + x2));
        REQUIRE (ret.y == Approx(y3 + y2));

        // ensures that v2 remains the same
        REQUIRE (v2.x == Approx(x2));
        REQUIRE (v2.y == Approx(y2));

        // ensures that v3 remains the same
        REQUIRE (v3.x == Approx(x3));
        REQUIRE (v3.y == Approx(y3));
    }

    SECTION("Subtracting Two Vectors")
    {
        // ensures that new v3 equals to old v3 plus v2
        auto ret = v3 - v2;
        REQUIRE (ret.x == Approx(x3 - x2));
        REQUIRE (ret.y == Approx(y3 - y2));

        // ensures that v2 remains the same
        REQUIRE (v2.x == Approx(x2));
        REQUIRE (v2.y == Approx(y2));

        // ensures that v3 remains the same
        REQUIRE (v3.x == Approx(x3));
        REQUIRE (v3.y == Approx(y3));
    }

    constexpr double x4 = 2.59, y4 = 21.4;
    Vector v4(x4, y4);

    SECTION("Adding Two Vectors (+=)")
    {
        // ensures that new v3 equals to old v3 plus v2
        v4 += v2;
        REQUIRE (v4.x == Approx(x4 + x2));
        REQUIRE (v4.y == Approx(y4 + y2));

        // ensures that v2 remains the same
        REQUIRE (v2.x == Approx(x2));
        REQUIRE (v2.y == Approx(y2));
    }

    constexpr double x5 = 52.2, y5 = 728.4;
    Vector v5(x5, y5);

    SECTION("Subtracting Two Vectors (-=)")
    {
        // ensures that new v3 equals to old v3 plus v2
        v5 -= v2;
        REQUIRE (v5.x == Approx(x5 - x2));
        REQUIRE (v5.y == Approx(y5 - y2));

        // ensures that v2 remains the same
        REQUIRE (v2.x == Approx(x2));
        REQUIRE (v2.y == Approx(y2));
    }

    constexpr double x6 = 1.2, y6 = 94.4;
    constexpr double c = 4.2;
    Vector v6(x6, y6);

    SECTION("Multiplying a Scalar")
    {
        // ensures that we can multiple a positive scalar
        auto ret = v6 * c;
        REQUIRE (ret.x == Approx(x6 * c));
        REQUIRE (ret.y == Approx(y6 * c));

        // ensures that we can multiple a negative scalar
        ret = v6 * -c;
        REQUIRE (ret.x == Approx(x6 * -c));
        REQUIRE (ret.y == Approx(y6 * -c));

        // ensures that we can multiple a negative scalar
        ret = c * v6;
        REQUIRE (ret.x == Approx(x6 * c));
        REQUIRE (ret.y == Approx(y6 * c));
    }

    SECTION("Multiplying a Scalar (*=)")
    {
        // ensures that we can multiple a positive scalar
        v6 *= c;
        REQUIRE (v6.x == Approx(x6 * c));
        REQUIRE (v6.y == Approx(y6 * c));

        // ensures that we can multiple a negative scalar
        v6 *= -c;
        REQUIRE (v6.x == Approx(x6 * c * -c));
        REQUIRE (v6.y == Approx(y6 * c * -c));
    }

    SECTION("Comparing Two Vectors")
    {
        // same vector
        auto v6_copied = Vector(x6, y6);
        REQUIRE (v6 == v6_copied);

        // different x and y values
        REQUIRE (v6 != v5);

        // same x value, different y value
        auto v6_x = Vector(x6, 1.2);
        REQUIRE (v6 != v6_x);
        
        // same y value, different x value
        auto v6_y = Vector(4.9, y6);
        REQUIRE (v6 != v6_y);
    }
}
