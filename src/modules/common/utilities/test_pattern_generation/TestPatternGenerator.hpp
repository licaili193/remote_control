/* ========================================
 Author: Caili LI caili@udel.edu
 ========================================== */

#include <vector>
#include <string>
#include <random>

#include <opencv2/core/core.hpp>

namespace remote
{
namespace common
{
namespace utilities
{
class TestPatternGenerator
{
    size_t width_;
    size_t height_;
    size_t period_;
    std::string name_;

    cv::Mat canvas_;
    size_t index_;

    int color_up_;
    int color_down_;

    static std::random_device dev;
    static std::mt19937 generator;
    static std::uniform_int_distribution<int> dice;
    static std::vector<cv::Scalar> colors;

public:
    TestPatternGenerator(size_t width, size_t height, size_t period, std::string name);

    void NextFrame();
    const cv::Mat &GetFrame();
};
} // namespace utilities
} // namespace common
} // namespace remote
