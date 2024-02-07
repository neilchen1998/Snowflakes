#include <boost/math/distributions/normal.hpp> // for normal_distribution
#include <boost/random.hpp> // for mt19937 and variate_generator

double boost_normal_distribution(double mean, double sd)
{
    static boost::mt19937 rng; // random number generator, declared as static
    boost::normal_distribution<> nd(mean, sd);
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<>> var_nor(rng, nd);

    return var_nor();
}

int boost_uniform_int_distribution(int max, int min)
{
    static boost::mt19937 rng; // random number generator, declared as static
    boost::random::uniform_int_distribution<> uni(min, max);

    return uni(rng);
}