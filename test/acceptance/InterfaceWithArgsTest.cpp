#include "InterfaceWithArgsMock.hpp"
#include <gtest/gtest.h>

namespace
{

const char *ccf()
{
    return 0;
}

}

TEST(InterfaceWithArgsMockTest, methods)
{
    InterfaceWithArgsMock mock;
    EXPECT_CALL(mock, m1(7));
    static_cast<InterfaceWithArgs&>(mock).m1(7);
    EXPECT_CALL(mock, m2(true, 3.2));
    static_cast<InterfaceWithArgs&>(mock).m2(true, 3.2);
    EXPECT_CALL(mock, m3('a', "b", ccf));
    static_cast<InterfaceWithArgs&>(mock).m3('a', "b", ccf);
}
