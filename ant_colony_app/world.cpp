#include "world.h"

World::World() : food{new Food}, foodPheromones{new Pheromone(worldBounds.first, worldBounds.second)}
{
    homeBase.x = worldBounds.first/2;
    homeBase.y = worldBounds.second/2;
}

World::World(double home_x, double home_y) : food{new Food}, foodPheromones{new Pheromone(worldBounds.first, worldBounds.second)}
{
    homeBase.x = home_x;
    homeBase.y = home_y;
}

const World::Colony* World::get_home() const
{
    return &homeBase;
}

Food* World::get_food() const
{
    return food;
}

const Pheromone* World::get_food_pheromones() const
{
    return foodPheromones;
}

double World::get_ant_population() const
{
    return antPopulation;
}

const std::vector<Ant*> World::get_ants() const
{
    return ants;
}

std::pair<double,double> World::get_bounds() const
{
    return worldBounds;
}

void World::add_ant(double x, double y)
{
    ants.push_back(new Ant{x, y, 0.0});
    antPopulation++;
}

void World::add_ant(Ant& ant)
{
    ants.push_back(&ant);
    antPopulation++;
}

void World::add_many_ants(int num_of_ants)
{
    antPopulation += num_of_ants;
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
    foodPheromones->update();
    for (auto a : ants)
    {
        std::pair<double,double> target;
        if(a->hasFood)
        {
            foodPheromones->add(a->x, a->y);
            target = {homeBase.x, homeBase.y};
        }
        else
        {
            target = food->search(a->x, a->y, a->heading);
        }

        if (target.first == -1) a->random_walk(worldBounds);
        else
        {
            bool targetClaimed = a->to_target(target, worldBounds);
            if (targetClaimed)
            {
                a->hasFood ? food->remove(target.first, target.second)
                           : store_food();

            }



        }
    }
}

