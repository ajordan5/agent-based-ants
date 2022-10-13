#include "gtest/gtest.h"
#include "world.h"

TEST(WorldConstructor, WhenInitializingADefaultWorld_ExpectHomeAtOrigin)
{
    World w{};
    EXPECT_EQ(w.ant_population, 0);
    EXPECT_EQ(w.get_home()->x, 0.0);
    EXPECT_EQ(w.get_home()->y, 0.0);
}

TEST(WorldConstructor, WhenInitializingAWorld_ExpectHomeAtGivenLocation)
{
    World w{1, 2};
    EXPECT_EQ(w.ant_population, 0);
    EXPECT_EQ(w.get_home()->x, 1.0);
    EXPECT_EQ(w.get_home()->y, 2.0);
}

TEST(AntConstructor, WhenInitializingAnt_ExpectPoseAtGivenLocation)
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

TEST(AntConstructor, WhenInitializingDefaultAnt_ExpectPoseAtZero)
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

TEST(WorldAddAnts, WhenAddingAnts_ExpectOkay)
{
    World w{1, 2};
    w.add_many_ants(3);

    EXPECT_EQ(w.ant_population, 3);
}
