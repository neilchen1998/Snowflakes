#include <filesystem>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "graph/graphlib.hpp"
#include "coordinate/vectorlib.hpp"

#define FILLED -1
#define ROWS 1024
#define COLS 1024
#define CENTER (ROWS/2)

void DisplayImage(const std::string& windowName, cv::Mat& img)
{
    cv::imshow(windowName, img);
    cv::waitKey(0);

    return;
}

void DrawAllCircles(cv::Mat& img, const std::vector<Circle>& circles)
{
    auto itr = circles.cbegin();
    while (itr != circles.cend())
    {
        cv::circle(img, cv::Point(itr->c.x + CENTER, itr->c.y + CENTER), itr->radius, CV_RGB(itr->r, itr->g, itr->b), FILLED);
        ++itr;
    }
}

bool SaveImage(const std::string& filename, cv::Mat& img)
{
    // checks if the folder exists
    std::filesystem::path p(filename);
    if (std::filesystem::exists(p.parent_path()))
    {
        cv::imwrite(filename, img);
        return true;
    }
    else
        return false;
}
