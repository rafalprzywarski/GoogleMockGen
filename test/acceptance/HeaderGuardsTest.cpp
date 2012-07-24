#include "Interface1Mock.hpp"
#include "Interface1Mock.hpp"

#include "Interface2Mock.hpp"

TEST(HeaderGuardsTest, bothIncluded)
{
    Interface1Mock();
    Interface2Mock();
}

#define INTERFACEWITHARGSMOCK_HPP
#include "InterfaceWithArgsMock.hpp" // should not include

class InterfaceWithArgsMock // verify no include
{
};