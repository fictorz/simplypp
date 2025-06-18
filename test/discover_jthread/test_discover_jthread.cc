#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "proto/message_handler.h"

using namespace std;

TEST(TestMessageHandler, basic) {
  proto::MyMessageHandler messageHandler;
  test
  ASSERT_EQ(messageHandler.getName(), "test");
}
