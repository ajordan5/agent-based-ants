#include "gtest/gtest.h"
#include "world.h"

TEST(WorldConstructor, ExpectOK)
{
    World w{};
    EXPECT_TRUE(true);
}
