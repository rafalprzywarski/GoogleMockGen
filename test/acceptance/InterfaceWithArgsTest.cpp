#include "InterfaceWithArgsMock.hpp"
#include <gtest/gtest.h>

TEST(InterfaceWithArgsMockTest, methods)
{
    InterfaceWithArgsMock mock;
    EXPECT_CALL(mock, m1(7));
    static_cast<InterfaceWithArgs&>(mock).m1(7);
}
