/* ========================================
 Author: Caili LI caili@udel.edu
 ========================================== */

#include <opencv2/imgproc/imgproc.hpp>

#include "modules/common/utilities/test_pattern_generation/TestPatternGenerator.hpp"

namespace remote
{
namespace common
{
namespace utilities
{
std::vector<cv::Scalar> TestPatternGenerator::colors = {
    cv::Scalar(255, 0, 0),
    cv::Scalar(0, 255, 0),
    cv::Scalar(0, 0, 255),
    cv::Scalar(255, 255, 0),
    cv::Scalar(255, 0, 255),
    cv::Scalar(0, 255, 255)};

std::random_device TestPatternGenerator::dev;
std::mt19937 TestPatternGenerator::generator(TestPatternGenerator::dev());
std::uniform_int_distribution<int> TestPatternGenerator::dice(0, 4);

TestPatternGenerator::TestPatternGenerator(size_t width, size_t height, size_t period, std::string name)
{
    width_ = width;
    height_ = height;
    period_ = period;
    name_ = name;

    index_ = period;

    color_up_ = 0;
    color_down_ = 1;
}

void TestPatternGenerator::NextFrame()
{
    if (index_ == period_)
    {
        index_ = 0;
        color_down_ = color_up_;
        int dice_result = dice(generator);
        color_up_ = (dice_result < color_down_) ? dice_result : (dice_result + 1);
    }

    size_t up_height = height_ * index_ / period_;
    canvas_ = cv::Mat(height_, width_, CV_8UC3, colors[color_down_]);
    if (up_height > 0)
    {
        cv::Mat up_canvas(up_height, width_, CV_8UC3, colors[color_up_]);
        up_canvas.copyTo(canvas_(cv::Rect(0, 0, width_, up_height)));
    }
    cv::putText(canvas_, name_, cv::Point(40, 80), cv::FONT_HERSHEY_DUPLEX, 2.0, cv::Scalar(255, 255, 255), 2);

    index_++;
}

const cv::Mat &TestPatternGenerator::GetFrame()
{
    return canvas_;
}

} // namespace utilities
} // namespace common
} // namespace remote
