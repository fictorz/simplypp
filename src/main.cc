#include <iostream>
#include <latch>
#include <memory>

#include "coroutines/coroutines.h"
#include "coroutines/executables.h"
#include "coroutines/timeout_awaitable.h"
#include "shapes/shape.h"
#include "util/logging.h"
#include "video_interfaces/video_interface.h"

using namespace std;
using namespace type_erasure;

// Next idea is to type erase the Drawer and specify which drawer we want to
// instantiate ie: Drawer drawer = std::make_unique<OPenGL>();
// drawer.drawAllShapes(shapes);
int main() {
    LOG(INFO) << "Drawing many circles and squares.";

    VideoInterface video_interface(OpenGLInterface{4.3});
    VideoInterface video_interface2(VulcanInterface{4.3});
    using Shapes = std::vector<Shape>;

    // Creating some shapes
    Shapes shapes;
    shapes.emplace_back(Circle{2.0});
    shapes.emplace_back(Square{1.5});
    shapes.emplace_back(Circle{4.2});

    // Drawing all shapes
    drawAllShapes(video_interface, shapes);
    drawAllShapes(video_interface2, shapes);

    // Fun coroutine exercises
    my_coroutine();
    my_coroutine_await();
    std::cout << "Coroutine completed\n";

    // Create 2 threads
    // do_with_timeout(std::chrono::milliseconds(20));
    constexpr int num_threads = 2;
    std::latch latches(num_threads);
    std::atomic<bool> finishedWork = {false};
    auto executeAsync = [&latches](std::vector<uint8_t> data, CancellationToken& token) {
        std::string strData(data.begin(), data.end());
        std::cout << "Data0: " << strData << std::endl;
        for (int i = 0; i < 5; ++i) {
            if (token.is_cancelled()) {
                std::cout << "[Task] Cancelled early\n";
                break;
            }

            std::cout << "Data" << i << ": " << strData << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        latches.count_down();
        std::cout << "[Task] Finished work\n";
    };

    do_with_executable(executeAsync, std::chrono::milliseconds(2));
    do_with_executable(executeAsync, std::chrono::milliseconds(200));

    latches.wait();
}