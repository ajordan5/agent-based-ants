#include "gtest/gtest.h"
#include "world.h"

TEST(WorldConstructor, WhenInitializingADefaultWorld_ExpectHomeAtOrigin)
{
    World w{};
    EXPECT_EQ(w.ant_population, 0);
    EXPECT_EQ(w.get_home()->x, 0.0);
    EXPECT_EQ(w.get_home()->y, 0.0);
    EXPECT_EQ(w.get_home()->food_count, 0);
}

TEST(WorldConstructor, WhenInitializingAWorld_ExpectHomeAtGivenLocation)
{
    World w{1, 2};
    EXPECT_EQ(w.ant_population, 0);
    EXPECT_EQ(w.get_home()->x, 1.0);
    EXPECT_EQ(w.get_home()->y, 2.0);
    EXPECT_EQ(w.get_home()->food_count, 0);
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

TEST(WorldAddAnts, WhenAddingAnts_ExpectAtHomeBase)
{
    World w{1, 2};
    w.add_many_ants(3);

    EXPECT_EQ(w.ant_population, 3);

    auto ant_poses = w.get_ants();

    for (auto a : ant_poses)
    {
        EXPECT_EQ(a->x, 1);
        EXPECT_EQ(a->y, 2);
        EXPECT_EQ(a->heading, 0);
    }
}

TEST(WorldAddAnts, WhenAddingAntsDefault_ExpectAtZero)
{
    World w;
    w.add_many_ants(8);

    EXPECT_EQ(w.ant_population, 8);

    auto ant_poses = w.get_ants();

    for (auto a : ant_poses)
    {
        EXPECT_EQ(a->x, 0);
        EXPECT_EQ(a->y, 0);
        EXPECT_EQ(a->heading, 0);
    }
}

TEST(AntDynamics, WhenUpdating_ExpectRandomTurn)
{
    World w{1, 2};
    w.add_many_ants(1);
    auto ant_poses = w.get_ants();

    EXPECT_EQ(w.ant_population, 1);

    w.update();

    for (auto a : ant_poses)
    {
        EXPECT_NE(a->x, 1);
        EXPECT_NE(a->y, 2);
        EXPECT_NE(a->heading, 0);
    }


}

class PrebuiltFood: public testing::Test
{
public:
    PrebuiltFood()
    {
        for (std::vector<int> l : expected_locs)
        {
            f.add_food(l[0], l[1]);
        }
    }

    ~PrebuiltFood()
    { }

protected:
    Food f;
    int goldTotalFood{4};
    std::vector<std::vector<int>> expected_locs{{1,1}, {3,2}, {7,7}, {7,1}};
};

TEST(FoodConstructor, WhenInitializingFood_ExpectEmpty)
{
    Food f;
    EXPECT_TRUE(f.get_locations()->empty());
}

TEST(FoodAdd, WhenAddingFood_ExpectNonEmptyAndCorrectLocations)
{
    Food f;
    f.add_food(1,1);
    EXPECT_TRUE(!f.get_locations()->empty());

    auto loc = *f.get_locations();
    EXPECT_EQ(1, loc.size());
    EXPECT_EQ(1, loc[1].size());
    EXPECT_TRUE(loc[1].count(1));

}

TEST_F(PrebuiltFood, GivenPrebuiltFood_ExpectCorrectLocations)
{
    auto locs = *f.get_locations();
    EXPECT_EQ(goldTotalFood, f.get_total());

    for (auto exp : expected_locs)
    {
        int x_loc = exp[0];
        int y_loc = exp[1];
        EXPECT_TRUE(locs[x_loc].count(y_loc));
    }
}

TEST_F(PrebuiltFood, GivenPrebuiltFood_WhenAddingExpectCorrectLocations)
{
    f.add_food(1,12);
    f.add_food(7,9);
    auto locs = *f.get_locations();
    EXPECT_EQ(goldTotalFood+2, f.get_total());

    for (auto exp : expected_locs)
    {
        int x_loc = exp[0];
        int y_loc = exp[1];
        EXPECT_TRUE(locs[x_loc].count(y_loc));
    }
    EXPECT_TRUE(locs[1].count(12));
    EXPECT_TRUE(locs[7].count(9));
}

TEST_F(PrebuiltFood, GivenPrebuiltFood_WhenAddingDuplicatesExpectNoChange)
{
    f.add_food(1,1);
    f.add_food(7,7);
    auto locs = *f.get_locations();
    EXPECT_EQ(goldTotalFood, f.get_total());

    for (auto exp : expected_locs)
    {
        int x_loc = exp[0];
        int y_loc = exp[1];
        EXPECT_TRUE(locs[x_loc].count(y_loc));
    }
}

TEST_F(PrebuiltFood, GivenPrebuiltFood_WhenDeletingExpectCorrectLocations)
{
    auto locs = *f.get_locations();
    EXPECT_EQ(goldTotalFood, f.get_total());
    EXPECT_FALSE(locs.empty());

    for (auto exp : expected_locs)
    {
        int x_loc = exp[0];
        int y_loc = exp[1];
        EXPECT_TRUE(locs[x_loc].count(y_loc));
        f.remove_food(x_loc, y_loc);
    }


    locs = *f.get_locations();
    EXPECT_TRUE(locs.empty());
    EXPECT_EQ(0, f.get_total());
}
