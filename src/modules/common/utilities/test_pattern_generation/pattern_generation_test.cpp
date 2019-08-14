/* ========================================
 Author: Caili LI caili@udel.edu
 ========================================== */

#include <string>

#include <opencv2/highgui/highgui.hpp>

#include "TestPatternGenerator.hpp"

int main(int argc, char const *argv[])
{
    remote::common::utilities::TestPatternGenerator pattern_gen(1280, 720, 300, "Test 1");
    cv::namedWindow("test-pattern", CV_WINDOW_AUTOSIZE);
    while (true)
    {
        pattern_gen.NextFrame();
        cv::Mat frame = pattern_gen.GetFrame();

        cv::imshow("test-pattern", frame);

        if (cv::waitKey(33) == 27) // Wait for 'esc' key press to exit
        {
            break;
        }
    }

    return 0;
}
