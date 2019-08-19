/* ========================================
 Author: Caili LI caili@udel.edu
 ========================================== */

#include <chrono>

#include "modules/common/utilities/image_preview/ImagePreviewer.hpp"

namespace remote
{
namespace common
{
namespace utilities
{
ImagePreviewer::ImagePreviewer(std::string name)
{
    name_ = name;
    running_.store(false);
}

ImagePreviewer::~ImagePreviewer()
{
    running_.store(false);
}

void ImagePreviewer::SetFrame(const cv::Mat frame)
{
    std::lock_guard<std::mutex> guard(mu_);
    frame.copyTo(frame_);
}

bool ImagePreviewer::Start()
{
    if (running_.load())
        return false;
    running_.store(true);
    std::thread worker(&ImagePreviewer::run, this);
    worker.detach();
    return true;
}

void ImagePreviewer::Stop()
{
    running_.store(false);
}

bool ImagePreviewer::IsRunning()
{
    return running_.load();
}

void ImagePreviewer::run()
{
    cv::namedWindow(name_, CV_WINDOW_AUTOSIZE);
    while (running_.load())
    {
        {
            std::lock_guard<std::mutex> guard(mu_);
            cv::imshow(name_, frame_);
        }
        if (cv::waitKey(5) == 27) // Wait for 'esc' key press to exit
        {
            running_.store(false);
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    cv::destroyWindow(name_);
}
} // namespace utilities
} // namespace common
} // namespace remote
