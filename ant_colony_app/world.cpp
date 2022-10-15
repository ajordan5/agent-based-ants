#include "world.h"

World::World() : ant_population{0}, food{new Food}
{

}

World::World(double home_x, double home_y) : ant_population{0}, food{new Food}
{
    home_base.x = home_x;
    home_base.y = home_y;
}

const World::Colony* World::get_home() const
{
    return &home_base;
}

const std::vector<Ant*> World::get_ants() const
{
    return ants;
}

void World::add_many_ants(int num_of_ants)
{
    ant_population += num_of_ants;
    for (int ii = 0; ii<num_of_ants; ii++)
    {
        ants.push_back(new Ant{home_base.x, home_base.y, 0.0});
    }
}

void World::update()
{
    for (auto a : ants)
    {
        std::pair nearestFood = food->search(a);
        if (nearestFood.first == -1) a->random_walk();
        else
        {
            bool foodClaimed = a->to_food(nearestFood.first, nearestFood.second);
            if (foodClaimed)food->remove_food(nearestFood.first, nearestFood.second);
        }
    }
}

