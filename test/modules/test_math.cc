import math;

#include <gtest/gtest.h>

TEST(MathTest, Addition) {
    EXPECT_EQ(add(2, 3), 5);
}

TEST(MathTest, Subtraction) {
    EXPECT_EQ(sub(10, 4), 6);
}