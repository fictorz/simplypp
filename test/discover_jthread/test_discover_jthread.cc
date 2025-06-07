#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "proto/message_handler.h"

using namespace std;

TEST(TestJThread, basic) {
  proto::MyMessageHandler messageHandler;
  ASSERT_EQ(messageHandler.getName(), "test");
}
