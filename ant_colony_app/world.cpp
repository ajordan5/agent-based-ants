#include "world.h"

World::World() : ant_population{0}, food{new Food}
{
    homeBase.x = world_bounds.first/2;
    homeBase.y = world_bounds.second/2;
}

World::World(double home_x, double home_y) : ant_population{0}, food{new Food}
{
    homeBase.x = home_x;
    homeBase.y = home_y;
}

const World::Colony* World::get_home() const
{
    return &homeBase;
}

const std::vector<Ant*> World::get_ants() const
{
    return ants;
}

std::pair<double,double> World::get_bounds() const
{
    return world_bounds;
}

void World::add_ant(double x, double y)
{
    ants.push_back(new Ant{x, y, 0.0});
    ant_population++;
}

void World::add_ant(Ant& ant)
{
    ants.push_back(&ant);
    ant_population++;
}

void World::add_many_ants(int num_of_ants)
{
    ant_population += num_of_ants;
    for (int ii = 0; ii<num_of_ants; ii++)
    {
        ants.push_back(new Ant{homeBase.x, homeBase.y, 0.0});
    }
}

void World::store_food()
{
    homeBase.food_count++;
}

void World::update()
{
    for (auto a : ants)
    {
        std::pair<double,double> target;
        if(a->hasFood)
        {
            target = {homeBase.x, homeBase.y};
        }
        else
        {
            target = food->search(a);
        }

        if (target.first == -1) a->random_walk(world_bounds);
        else
        {
            bool targetClaimed = a->to_target(target, world_bounds);
            if (targetClaimed)
            {
                a->hasFood ? food->remove_food(target.first, target.second)
                           : store_food();

            }


        }
    }
}

