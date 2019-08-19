/* ========================================
 Author: Caili LI caili@udel.edu
 ========================================== */

#include <chrono>
#include <atomic>
#include <thread>

#include <signal.h>

#include "modules/common/utilities/test_pattern_generation/TestPatternGenerator.hpp"
#include "modules/common/utilities/image_preview/ImagePreviewer.hpp"

std::atomic_bool running;

void my_handler(int s)
{
    running.store(false);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, my_handler);

    remote::common::utilities::TestPatternGenerator pattern_gen(1280, 720, 300, "Test 1");
    remote::common::utilities::ImagePreviewer previewer("test-pattern");

    running.store(true);
    previewer.Start();
    while (running.load())
    {
        pattern_gen.NextFrame();
        previewer.SetFrame(pattern_gen.GetFrame());
        if (!previewer.IsRunning())
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    previewer.Stop();

    return 0;
}
