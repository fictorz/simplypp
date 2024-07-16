#include <gtest/gtest.h>

#include "example_class.h"

using example::submodule::ExampleClass;

TEST(TestExampleClass, ExampleClassBasics) {
    EXPECT_EQ(2,example::submodule::ExampleClass::bitwiseAnd(2,3));
}