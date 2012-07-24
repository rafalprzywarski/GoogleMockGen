#include "Interface1Mock.hpp"
#include <gtest/gtest.h>

TEST(Interface1MockTest, f)
{
    Interface1Mock mock;
    EXPECT_CALL(mock, f());
    static_cast<Interface1&>(mock).f();
}
