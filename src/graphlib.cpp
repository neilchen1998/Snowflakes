#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

void DisplayImage(const std::string& windowName, cv::Mat img)
{
    cv::imshow(windowName, img);
    cv::waitKey(0);

    return;
}
