#define CATCH_CONFIG_MAIN

#include <map>
#include <math.h>   // round
#include <catch2/catch.hpp>

#include "math/mathlib.hpp"
#include "coordinate/coordinatelib.hpp"

TEST_CASE( "Boost Normal Distribution", "[main]" )
{
    unsigned int oneSDCnt = 0, twoSDCnt = 0, threeSDCnt = 0;
    const double mean = 0.0, sd = 1.0;
    constexpr int NUM_SAMPLES = 1000;
    constexpr int expectedOneSDCnt = 0.68 * NUM_SAMPLES;
    constexpr int expectedTwoSDCnt = (0.95 - 0.68) * NUM_SAMPLES;
    constexpr int expectedThreeSDCnt = (0.997 - 0.95) * NUM_SAMPLES;
    constexpr int TOLERANCE = 0.05 * NUM_SAMPLES;

    // creates a histogram so we can know how many samples are there in each bin
    std::map<int, int> hist{};
    for (unsigned int i = 0; i < NUM_SAMPLES; i++)
    {
        auto number = boost_normal_distribution(mean, sd);
        ++hist[round(number)];
    }

    auto itr = hist.cbegin();
    while (itr != hist.cend())
    {
        // gathers the number of each 
        if (-1 * sd <= itr->first && itr->first < 1 * sd)
        {
            oneSDCnt += itr->second;
        }
        else if (-2 * sd <= itr->first && itr->first < 2 * sd)
        {
            twoSDCnt += itr->second;
        }
        else if (-3 * sd <= itr->first && itr->first < 3 * sd)
        {
            threeSDCnt += itr->second;
        }

        ++itr;
    }
    
    SECTION("One σ")
    {
        REQUIRE (oneSDCnt >= (expectedOneSDCnt - TOLERANCE));
        REQUIRE (oneSDCnt <= (expectedOneSDCnt + TOLERANCE));
    }

    SECTION("Two σ's")
    {
        REQUIRE (twoSDCnt >= (expectedTwoSDCnt - TOLERANCE));
        REQUIRE (twoSDCnt <= (expectedTwoSDCnt + TOLERANCE));
    }

    SECTION("Three σ's")
    {
        // makes sure the lower bound of expected three sigma's is greater than 0
        unsigned int expectedThreeSDCntLow = std::max((expectedThreeSDCnt - TOLERANCE), 0);
        REQUIRE (threeSDCnt >= expectedThreeSDCntLow);
        REQUIRE (threeSDCnt <= (expectedThreeSDCnt + TOLERANCE));
    }

    // SECTION("Can Create")
    // {
    //     constexpr double x = 1.2, y = 2.4;
    //     // TODO: fix the linker error
    //     Point p(1.2, 2.4);
    //     REQUIRE (p.x == Approx(x));
    //     REQUIRE (p.y == Approx(y));
    // }
}