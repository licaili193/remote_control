/* ========================================
 Author: Caili LI caili@udel.edu
 ========================================== */

#include <thread>
#include <string>
#include <mutex>
#include <atomic>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace remote
{
namespace common
{
namespace utilities
{
class ImagePreviewer
{
    std::atomic_bool running_;
    std::string name_;
    cv::Mat frame_;

    std::mutex mu_;

    void run();

public:
    ImagePreviewer(std::string name);
    ~ImagePreviewer();

    void SetFrame(const cv::Mat frame);
    bool Start();
    bool IsRunning();
    void Stop();
};
} // namespace utilities
} // namespace common
} // namespace remote
