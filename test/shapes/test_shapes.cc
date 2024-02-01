#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "shapes/shape.h"
#include "util/logging.h"
#include "video_interfaces/video_interface.h"

using namespace std;
using namespace type_erasure;

TEST(TestShapes, anotherTest) {
    LOG(INFO) << "Another test";
}