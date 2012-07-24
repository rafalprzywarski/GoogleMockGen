#include "Interface2Mock.hpp"
#include <gtest/gtest.h>

using namespace testing;

TEST(Interface2MockTest, methods)
{
    Interface2Mock mock;
    EXPECT_CALL(mock, method1()).WillOnce(Return(3));
    ASSERT_EQ(3, static_cast<Interface2&>(mock).method1());
    EXPECT_CALL(mock, method2()).WillOnce(Return(3.7f));
    ASSERT_EQ(3.7f, static_cast<Interface2&>(mock).method2());
}
