#include "world.h"

World::World() : ant_population{0}
{

}

World::World(double home_x, double home_y) : ant_population{0}
{
    home_base.x = home_x;
    home_base.y = home_y;
}

const World::Colony* World::get_home() const
{
    return &home_base;
}

void World::add_many_ants(int num_of_ants)
{
    ant_population += num_of_ants;
    for (int ii = 0; ii<num_of_ants; ii++)
    {
        ants.push_back(new Ant{home_base.x, home_base.y, 0.0});
    }
}
