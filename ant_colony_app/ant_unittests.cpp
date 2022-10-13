#include "gtest/gtest.h"
#include "world.h"

TEST(WorldConstructor, ExpectOK)
{
    World w{};
    EXPECT_TRUE(true);
}

TEST(AntConstructor, ExpectOK)
{
    Ant* a = new Ant{1.0,2.0,3.0};
    double x = a->x;
    double y = a->y;
    double heading = a->heading;

    EXPECT_EQ(x, 1.0);
    EXPECT_EQ(y, 2.0);
    EXPECT_EQ(heading, 3.0);

    delete a;

}

TEST(AntConstructor, ExpectDefaultOK)
{
    Ant* a = new Ant;
    double x = a->x;
    double y = a->y;
    double heading = a->heading;

    EXPECT_EQ(x, 0.0);
    EXPECT_EQ(y, 0.0);
    EXPECT_EQ(heading, 0.0);

    delete a;

}
