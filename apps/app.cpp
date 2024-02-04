#include <iostream>
#include <string>
#include <unordered_set>  // std::unordered_set
#include <string_view>  // std::string_view
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

#include <boost/program_options.hpp>    // boost::program_options
#include <opencv2/imgproc.hpp>  // CV_RGB

#include "math/mathlib.hpp"
#include "graph/graphlib.hpp"
#include "coordinate/generatorlib.hpp"
#include "coordinate/vectorlib.hpp"
#include "helper/fmtlib.hpp"

namespace po = boost::program_options;

#define ROWS 1024
#define COLS 1024
#define CENTER (ROWS/2)

#define PI 3.14159265
#define DEG_TO_RAD(deg) ((deg) * PI / 180.0 )

#define DEBUG_MODE 1

int main(int argc, char* argv[])
{
    std::string selectedSnowflake;
    std::string outputDir;
    unsigned int numImages;

    // creates options descriptions and default values
    po::options_description desc("Options:");
    desc.add_options()
        ("help,h", "Display this information")
        ("snowflake,s", po::value<std::string>(&selectedSnowflake)->value_name("<SNOWFLAKE_TYPE>")->default_value("crystal"), "the type of snowflake")
        ("output,o", po::value<std::string>(&outputDir)->value_name("<OUTPUT_DIR>")->default_value("outputs"), "the output directory")
        ("number,n", po::value<unsigned int>(&numImages)->value_name("<NUM_IMAGES>")->default_value(10), "number of images");   // (<long name>,<short name>, <argument(s)>, <description>)

    // creates the variables map and stores the inputs to the map
    po::variables_map vm;

    // makes "snowflake" token be the positional option, i.e., token with no option name
    po::positional_options_description p;
    p.add("snowflake", -1);
    
    // checks if the user inputs are valid
    try
    {
        // parses the arguments and writes the variables according to the variables map
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    
    // checks if the user selects --help
    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return EXIT_FAILURE;
    }

    // checks if we have the user input snowflake type
    std::unordered_set<std::string_view> snowflakeOptions({"crystal", "radiating-dendrite", "stellar-plate"});
    if (snowflakeOptions.find(selectedSnowflake) == snowflakeOptions.end())
    {
        std::cout << "Invalid input...\n";
        std::cout << "Please select one of the following snowflake types:\n";
        auto itr = snowflakeOptions.cbegin();
        while (itr != snowflakeOptions.cend())
        {
            std::cout << *itr << "\n";
            ++itr;
        }
        return EXIT_FAILURE;
    }

    // checks if the user does not provide any input
    if (vm["snowflake"].defaulted() || vm["output"].defaulted() || vm["images"].defaulted())
    {
        std::cout << "At least one of the options is not specified! Will use the default values...\n";
    }

    // main programme
    bool canSave;
    if (selectedSnowflake == "crystal")
    {
        const int mean = 45, sd = 10;
        int radiusHigh = 7;
        int radiusLow = 2;

        // renders snowflakes
        for (unsigned char render = 0; render < numImages; render++)
        {
            // creates a black canvas
            cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

            int numCrystals = boost_normal_distribution(mean, sd);
            const Vector mirror(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));

            DrawCrystalSnowflake(img, Vector(1, 1), numCrystals, radiusHigh, radiusLow, mirror);

            const std::string snowflakeName("Crystal-Snowflake");

            std::string label = "# of crystals: " + std::to_string(numCrystals) + " mirror: " + mirror.ToString();

            // put parameters on the image
            PutLabel(img, label);

            #if DEBUG_MODE

                DisplayImage("image", img);

                return EXIT_SUCCESS;

            #else
                // save image
                std::string filename = snowflakeName + "_" + std::to_string(render + 1) + ".jpg";
                canSave = SaveImage(outputDir + "/" + filename, img);
                if (!canSave)
                    return EXIT_FAILURE;
            #endif
        }
    }
    else if (selectedSnowflake == "radiating-dendrite")
    {
        const int mean = 200, sd = 20;

        // renders snowflakes
        for (unsigned char render = 0; render < numImages; render++)
        {
            // creates a black canvas
            cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

            const Vector mirror(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));
            const int armLength = boost_normal_distribution(mean, sd);
            const int armWidth = boost_normal_distribution(5, 1);
            const int nodeLength = 20;
            const int branchLength = 50;
            const double theta = DEG_TO_RAD(boost_normal_distribution(60, 10));
            const double rate = boost_normal_distribution(0.8, 0.1);

            DrawRadiatingDendriteSnowflake(img, mirror, armLength, armWidth, nodeLength, branchLength , theta, rate);

            const std::string snowflakeName("Radiating-Dendrite-Snowflake");

            std::string label = "armLength: " + std::to_string(armLength) + " armWidth: " + std::to_string(armWidth) + " theta: " + Formatter(theta) + " rate: " + Formatter(rate);

            // put parameters on the image
            PutLabel(img, label);

            #if DEBUG_MODE

                DisplayImage("image", img);

                return EXIT_SUCCESS;

            #else
                std::string filename = snowflakeName + "_" + std::to_string(render + 1) + ".jpg";
                canSave = SaveImage(outputDir + "/" + filename, img);
                if (!canSave)
                    return EXIT_FAILURE;
            #endif
        }
    }
    else if (selectedSnowflake == "stellar-plate")
    {
        // renders snowflakes
        for (unsigned char render = 0; render < numImages; render++)
        {
            // creates a black canvas
            cv::Mat img(ROWS, COLS, CV_8UC3, CV_RGB(0, 0, 0));

            const Vector v(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));
            const Vector w(boost_normal_distribution(1, 0.1), boost_normal_distribution(1, 0.1));

            int motherSide = boost_normal_distribution(100, 30);
            int sonSide = boost_normal_distribution(40, 10);

            // makes sure motherSide is greater than sonSide
            motherSide = (motherSide <= sonSide) ? sonSide + 10 : motherSide;

            DrawStellarPlateSnowflake(img, v.Unit(), w, motherSide, sonSide);

            const std::string snowflakeName("Stellar-Plate-Snowflake");

            std::string label = "motherSide: " + std::to_string(motherSide) + " sonSide: " + std::to_string(sonSide);

            // put parameters on the image
            PutLabel(img, label);

            #if DEBUG_MODE

                DisplayImage(snowflakeName, img);

                return EXIT_SUCCESS;

            #else

                // save image
                std::string filename = snowflakeName + "_" + std::to_string(render + 1) + ".jpg";
                canSave = SaveImage(outputDir + "/" + filename, img);
                if (!canSave)
                    return EXIT_FAILURE;
            #endif
        }
    }

    return EXIT_SUCCESS;
}