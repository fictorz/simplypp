#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "proto/message_handler.h"

using namespace std;

// Next idea is to type erase the Drawer and specify which drawer we want to
// instantiate ie: Drawer drawer = std::make_unique<OPenGL>();
// drawer.drawAllShapes(shapes);
TEST(TestMessageHandler, basic) {
  proto::MyMessageHandler messageHandler;
  ASSERT_EQ(messageHandler.getName(), "test");
}
