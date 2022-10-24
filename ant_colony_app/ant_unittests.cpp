#include "gtest/gtest.h"
#include "world.h"

#define NEAR_TOL 0.001
#define PI 3.14159

TEST(WorldConstructor, WhenInitializingADefaultWorld_ExpectHomeAtCenter)
{
    World w{};
    std::pair<double, double> bounds = w.get_bounds();
    double goldenX = bounds.first/2;
    double goldenY = bounds.second/2;
    EXPECT_EQ(0, w.get_ant_population());
    EXPECT_EQ(goldenX, w.get_home()->x);
    EXPECT_EQ(goldenY, w.get_home()->y);
    EXPECT_EQ(0, w.get_home()->food_count);
}

TEST(WorldConstructor, WhenInitializingAWorld_ExpectHomeAtGivenLocation)
{
    World w{1, 2};
    EXPECT_EQ(w.get_ant_population(), 0);
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

    EXPECT_EQ(w.get_ant_population(), 3);

    auto ant_poses = w.get_ants();

    for (auto a : ant_poses)
    {
        EXPECT_EQ(a->x, 1);
        EXPECT_EQ(a->y, 2);
        EXPECT_EQ(a->heading, 0);
    }
}

TEST(WorldAddAnts, WhenAddingAntAtLocation_ExpectAtGivenLocation)
{
    World w;
    w.add_ant(3, 4);

    EXPECT_EQ(w.get_ant_population(), 1);

    auto ant_poses = w.get_ants();

    EXPECT_EQ(ant_poses[0]->x, 3);
    EXPECT_EQ(ant_poses[0]->y, 4);
    EXPECT_EQ(ant_poses[0]->heading, 0);
    EXPECT_EQ(ant_poses[0]->hasFood, false);

}

TEST(WorldAddAnts, WhenAddingPrebuiltAnt_ExpectAtGivenState)
{
    Ant a{1, 2, 3};
    World w;
    w.add_ant(a);

    EXPECT_EQ(w.get_ant_population(), 1);

    auto ant_poses = w.get_ants();

    EXPECT_EQ(ant_poses[0]->x, 1);
    EXPECT_EQ(ant_poses[0]->y, 2);
    EXPECT_EQ(ant_poses[0]->heading, 3);
    EXPECT_EQ(ant_poses[0]->hasFood, false);

}

TEST(WorldAddAnts, WhenAddingAntsDefault_ExpectAtZero)
{
    World w;
    w.add_many_ants(8);
    std::pair<double, double> bounds = w.get_bounds();
    double goldenX = bounds.first/2;
    double goldenY = bounds.second/2;
    auto ant_poses = w.get_ants();

    EXPECT_EQ(w.get_ant_population(), 8);

    for (auto a : ant_poses)
    {
        EXPECT_EQ(goldenX, a->x);
        EXPECT_EQ(goldenY, a->y);
        EXPECT_EQ(0, a->heading);
    }
}

class AntSpy : public Ant
{
public:
    double getDistanceTraveled() {return speed*timeStep;}
};

TEST(AntDynamics, GivenDefaultAntWhenPropogatingDynamics_ExpectMoveInX)
{
    AntSpy a;
    double distanceTraveled = a.getDistanceTraveled();
    a.propogate_dynamics({1000,1000});

    double goldenX{distanceTraveled};
    double goldenY{0};

    EXPECT_NEAR(goldenX, a.x, NEAR_TOL);
    EXPECT_NEAR(goldenY, a.y, NEAR_TOL);

}

TEST(AntDynamics, GivenAntPointingDownWhenPropogatingDynamics_ExpectMoveInY)
{
    AntSpy a;
    a.heading = 1.5707;
    double distanceTraveled = a.getDistanceTraveled();
    a.propogate_dynamics({1000,1000});

    double goldenY{distanceTraveled};
    double goldenX{0};

    EXPECT_NEAR(goldenX, a.x, NEAR_TOL);
    EXPECT_NEAR(goldenY, a.y, NEAR_TOL);

}

TEST(AntDynamics, GivenPointedAntWhenPropogatingDynamics_ExpectCorrectLocation)
{
    AntSpy a;
    a.heading = 0.8;
    double distanceTraveled = a.getDistanceTraveled();
    a.propogate_dynamics({1000,1000});

    double goldenX{distanceTraveled*0.6967};
    double goldenY{distanceTraveled*0.7174};

    EXPECT_NEAR(goldenX, a.x, NEAR_TOL);
    EXPECT_NEAR(goldenY, a.y, NEAR_TOL);

}

TEST(AntDynamics, GivenAntNotAtZeroWhenPropogatingDynamics_ExpectCorrectLocation)
{
    AntSpy a;
    a.x = 56;
    a.y = 173;
    a.heading = 0.3;
    double distanceTraveled = a.getDistanceTraveled();
    a.propogate_dynamics({1000,1000});

    double goldenX{56 + distanceTraveled*0.9553};
    double goldenY{173 + distanceTraveled*0.2955};

    EXPECT_NEAR(goldenX, a.x, NEAR_TOL);
    EXPECT_NEAR(goldenY, a.y, NEAR_TOL);

}

TEST(AntBounceDynamics, GivenAntGoingOutOfRightBounds_ExpectAntToBounce)
{
    AntSpy a;
    a.x = 999.9;
    a.y = 173;
    a.heading = 1.3;
    double distanceTraveled = a.getDistanceTraveled();

    std::pair<double,double> bounds{1000,1000};
    a.propogate_dynamics(bounds);

    double goldenX{1000};
    double goldenY{173 + distanceTraveled*0.9636};
    double goldenHeading{PI - 1.3};

    EXPECT_NEAR(goldenX, a.x, NEAR_TOL);
    EXPECT_NEAR(goldenY, a.y, NEAR_TOL);
    EXPECT_NEAR(goldenHeading, a.heading, NEAR_TOL);

}

TEST(AntBounceDynamics, GivenAntGoingOutOfLeftBounds_ExpectAntToBounce)
{
    AntSpy a;
    a.x = 0.1;
    a.y = 600;
    a.heading = 2.55;
    double distanceTraveled = a.getDistanceTraveled();

    std::pair<double,double> bounds{1000,1000};
    a.propogate_dynamics(bounds);

    double goldenX{0};
    double goldenY{600 + distanceTraveled*0.5577};
    double goldenHeading{PI - 2.55};

    EXPECT_NEAR(goldenX, a.x, NEAR_TOL);
    EXPECT_NEAR(goldenY, a.y, NEAR_TOL);
    EXPECT_NEAR(goldenHeading, a.heading, NEAR_TOL);

}

TEST(AntBounceDynamics, GivenAntGoingOutOfTopBounds_ExpectAntToBounce)
{
    AntSpy a;
    a.x = 10;
    a.y = 0.05;
    a.heading = -0.5;
    double distanceTraveled = a.getDistanceTraveled();

    std::pair<double,double> bounds{1000,1000};
    a.propogate_dynamics(bounds);

    double goldenX{10 + distanceTraveled*0.8776};
    double goldenY{0};
    double goldenHeading{2*PI + 0.5};

    EXPECT_NEAR(goldenX, a.x, NEAR_TOL);
    EXPECT_NEAR(goldenY, a.y, NEAR_TOL);
    EXPECT_NEAR(goldenHeading, a.heading, NEAR_TOL);

}

TEST(AntBounceDynamics, GivenAntGoingOutOfBottomBounds_ExpectAntToBounce)
{
    AntSpy a;
    a.x = 100;
    a.y = 999;
    a.heading = 1.8;
    double distanceTraveled = a.getDistanceTraveled();

    std::pair<double,double> bounds{1000,1000};
    a.propogate_dynamics(bounds);

    double goldenX{100 + distanceTraveled*-0.2272};
    double goldenY{1000};
    double goldenHeading{2*PI - 1.8};

    EXPECT_NEAR(goldenX, a.x, NEAR_TOL);
    EXPECT_NEAR(goldenY, a.y, NEAR_TOL);
    EXPECT_NEAR(goldenHeading, a.heading, NEAR_TOL);

}

TEST(FoodConstructor, WhenInitializingFood_ExpectEmpty)
{
    Food f;
    EXPECT_TRUE(f.get_locations().empty());
}

TEST(FoodAdd, WhenAddingFood_ExpectNonEmptyAndCorrectLocations)
{
    Food f;
    f.add(1,1);
    EXPECT_TRUE(!f.get_locations().empty());

    auto loc = f.get_locations();
    EXPECT_EQ(1, loc.size());
    EXPECT_EQ(1, loc[1].size());
    EXPECT_TRUE(f.contains(1,1));

}


class PrebuiltFood: public testing::Test
{
public:
    PrebuiltFood()
    {
        for (std::vector<int> l : expected_locs)
        {
            f.add(l[0], l[1]);
        }
    }

    ~PrebuiltFood()
    { }

protected:
    Food f;
    int goldTotalFood{4};
    std::vector<std::vector<int>> expected_locs{{1,1}, {3,2}, {7,7}, {7,1}};
};

TEST_F(PrebuiltFood, GivenPrebuiltFood_ExpectCorrectLocations)
{
    auto locs = f.get_locations();
    EXPECT_EQ(goldTotalFood, f.get_total());

    for (auto exp : expected_locs)
    {
        int x_loc = exp[0];
        int y_loc = exp[1];
        EXPECT_TRUE(f.contains(x_loc, y_loc));
    }
}

TEST_F(PrebuiltFood, GivenPrebuiltFood_WhenAddingExpectCorrectLocations)
{
    f.add(1,12);
    f.add(7,9);
    auto locs = f.get_locations();
    EXPECT_EQ(goldTotalFood+2, f.get_total());

    for (auto exp : expected_locs)
    {
        int x_loc = exp[0];
        int y_loc = exp[1];
        EXPECT_TRUE(f.contains(x_loc, y_loc));
    }
    EXPECT_TRUE(f.contains(1, 12));
    EXPECT_TRUE(f.contains(7, 9));
}

TEST_F(PrebuiltFood, GivenPrebuiltFood_WhenAddingDuplicatesExpectNoChange)
{
    f.add(1,1);
    f.add(7,7);
    auto locs = f.get_locations();
    EXPECT_EQ(goldTotalFood, f.get_total());

    for (auto exp : expected_locs)
    {
        int x_loc = exp[0];
        int y_loc = exp[1];
        EXPECT_TRUE(f.contains(x_loc, y_loc));
    }
}

TEST_F(PrebuiltFood, GivenPrebuiltFood_WhenDeletingExpectCorrectLocations)
{
    auto locs = f.get_locations();
    EXPECT_EQ(goldTotalFood, f.get_total());
    EXPECT_FALSE(locs.empty());

    for (auto exp : expected_locs)
    {
        int x_loc = exp[0];
        int y_loc = exp[1];
        EXPECT_TRUE(f.contains(x_loc, y_loc));
        f.remove(x_loc, y_loc);
    }


    locs = f.get_locations();
    EXPECT_TRUE(locs.empty());
    EXPECT_EQ(0, f.get_total());
}

TEST_F(PrebuiltFood, GivenPrebuiltFood_WhenSearchingRightExpectNearestFood)
{
    Ant* a = new Ant{0,0,0};
    std::pair<int,int> result = f.search(a->x, a->y, a->heading);
    EXPECT_EQ(1, result.first);
    EXPECT_EQ(1, result.second);

}

TEST_F(PrebuiltFood, GivenPrebuiltFood_WhenSearchingLeftExpectNearestFood)
{
    Ant* a = new Ant{9,2,3.14};
    std::pair<int,int> result = f.search(a->x, a->y, a->heading);
    EXPECT_EQ(7, result.first);
    EXPECT_EQ(1, result.second);

}

TEST_F(PrebuiltFood, GivenPrebuiltFood_WhenSearchingUpExpectNearestFood)
{
    Ant* a = new Ant{2,4,-1.2};
    std::pair<int,int> result = f.search(a->x, a->y, a->heading);
    EXPECT_EQ(3, result.first);
    EXPECT_EQ(2, result.second);

}

TEST_F(PrebuiltFood, GivenPrebuiltFood_WhenSearchingDownExpectNearestFood)
{
    Ant* a = new Ant{7,6,1.7};
    std::pair<int,int> result = f.search(a->x, a->y, a->heading);
    EXPECT_EQ(7, result.first);
    EXPECT_EQ(7, result.second);
}

TEST(AntToFood, GivenFoodCloseToAnt_ExpectAntAtFood)
{
    Ant a{0,0,0};
    std::pair<double,double> target{1, 1};
    std::pair<double,double> bounds{10, 10};
    a.to_target(target, bounds);

    EXPECT_EQ(1, a.x);
    EXPECT_EQ(1, a.y);
    EXPECT_NEAR(.7854, a.heading, .001);

}


TEST(AntToHome, GivenAntWithFood_ExpectAntTowardsFood)
{
    Ant a{40,70,0};
    a.hasFood = true;
    std::pair<double,double> target{1, 1};
    std::pair<double,double> bounds{10, 10};
    a.to_target(target, bounds);

//    EXPECT_EQ(1, a.x);
//    EXPECT_EQ(1, a.y);
//    EXPECT_NEAR(.7854, a.heading, .001);

}

TEST(Pheromone, GivenAnEmptyPheromoneClassExpectNoPheromones)
{
    Pheromone p(5,5);

    for (int ii = 0; ii<5; ii++)
    {
        for (int jj = 0; jj<5; jj++)
        {
            const unsigned char* pixel = p.get_pixel(ii,jj);

            EXPECT_FALSE(p.contains(ii,jj));
            EXPECT_EQ(pixel[3], 0);
            EXPECT_EQ(pixel[2], 0);
            EXPECT_EQ(pixel[1], 0);
            EXPECT_EQ(pixel[0], 0);
        }

    }

}

TEST(Pheromone, GivenAPheromoneClassWhenPlacing_ExpectPheromonesAtLocation)
{
    Pheromone p(10,10);
    p.add(5,5);
    const unsigned char* pixel = p.get_pixel(5,5);

    EXPECT_TRUE(p.contains(5,5));
    EXPECT_EQ(pixel[3], 255);
    EXPECT_EQ(pixel[2], 255);
    EXPECT_EQ(pixel[1], 0);
    EXPECT_EQ(pixel[0], 0);


}

TEST(Pheromone, GivenAPheromoneClassWhenPlacingMultiple_ExpectPheromonesAtLocation)
{
    Pheromone p(10,10);
    p.add(1,1);
    p.add(3,7);
    const unsigned char* pixel = p.get_pixel(1,1);

    EXPECT_TRUE(p.contains(1,1));
    EXPECT_EQ(pixel[3], 255);
    EXPECT_EQ(pixel[2], 255);
    EXPECT_EQ(pixel[1], 0);
    EXPECT_EQ(pixel[0], 0);

    pixel = p.get_pixel(3,7);

    EXPECT_TRUE(p.contains(3,7));
    EXPECT_EQ(pixel[3], 255);
    EXPECT_EQ(pixel[2], 255);
    EXPECT_EQ(pixel[1], 0);
    EXPECT_EQ(pixel[0], 0);


}

TEST(Pheromone, GivenAPheromoneClassWhenUpdating_ExpectPheromonesToDecay)
{
    Pheromone p(10,10);
    p.add(5,5);
    const unsigned char* pixel = p.get_pixel(5,5);
    p.update();
    unsigned char decayRate = p.get_decay_rate();

    EXPECT_TRUE(p.contains(5,5));
    EXPECT_EQ(pixel[3], 255-decayRate);
    EXPECT_EQ(pixel[2], 255);
    EXPECT_EQ(pixel[1], 0);
    EXPECT_EQ(pixel[0], 0);
}

TEST(Pheromone, GivenAPheromoneClassWhenUpdatingMultiple_ExpectPheromonesToDecay)
{
    Pheromone p(10,10);
    p.add(5,5);
    const unsigned char* pixel = p.get_pixel(5,5);
    p.update();
    p.update();
    unsigned char decayRate = p.get_decay_rate();

    EXPECT_TRUE(p.contains(5,5));
    EXPECT_EQ(pixel[3], 255-2*decayRate);
    EXPECT_EQ(pixel[2], 255);
    EXPECT_EQ(pixel[1], 0);
    EXPECT_EQ(pixel[0], 0);

}

TEST(Pheromone, GivenAPheromoneWhenCompletelyDecayed_ExpectPheromonesToBeRemoved)
{
    Pheromone p(10,10);
    p.add(5,5);
    const unsigned char* pixel = p.get_pixel(5,5);
    unsigned char decayRate = p.get_decay_rate();
    for(int i = 0; i < (255 / decayRate + 1); i++)
        p.update();


    EXPECT_FALSE(p.contains(5,5));
    EXPECT_EQ(pixel[3], 0);
    EXPECT_EQ(pixel[2], 255);
    EXPECT_EQ(pixel[1], 0);
    EXPECT_EQ(pixel[0], 0);


}
