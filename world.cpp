#include "world.h"

World::World()
    : food{new Food}, foodPheromones{new Pheromone(worldBounds.first, worldBounds.second)},
      homePheromones{new Pheromone(worldBounds.first, worldBounds.second)}
{
    homeBase.x = worldBounds.first/2;
    homeBase.y = worldBounds.second/2;
    homePheromones->set_color(0, 100, 0);
}

World::World(double home_x, double home_y)
    : food{new Food}, foodPheromones{new Pheromone(worldBounds.first, worldBounds.second)},
      homePheromones{new Pheromone(worldBounds.first, worldBounds.second)}
{
    homeBase.x = home_x;
    homeBase.y = home_y;
    homePheromones->set_color(255, 175, 180);
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

const Pheromone* World::get_home_pheromones() const
{
    return homePheromones;
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

void World::to_pheromones(Ant* ant)
{
    Pheromone* targetPheromone;
    ant->hasFood ? targetPheromone = homePheromones :
            targetPheromone = foodPheromones;
    double targetHeading = targetPheromone->ray_search(ant);

    if (targetHeading == -PI)
    {
        ant->random_walk(worldBounds);
    }
    else
    {
        ant->heading = ant->heading + targetHeading;
        ant->propogate_dynamics(worldBounds);
    }
}

std::pair<double,double> World::to_home(Ant* ant)
{
    double xDiff = homeBase.x - ant->x;
    double yDiff = homeBase.y- ant->y;
    double distanceToHome = sqrt((xDiff)*(xDiff) + (yDiff)*(yDiff));

    std::pair<double,double> target{-1,-1};
    if (distanceToHome < homeSearchRadius)
    {
        target = {homeBase.x, homeBase.y};
    }
    return target;
}

void World::update()
{
    foodPheromones->update();
    homePheromones->update();
    for (auto a : ants)
    {
        std::pair<double,double> target;
        if(a->hasFood)
        {
            foodPheromones->add(a->x, a->y);
            target = to_home(a);
        }
        else
        {
            homePheromones->add(a->x, a->y);
            target = food->search(a->x, a->y, a->heading);
        }

        if (target.first == -1)
        {
            to_pheromones(a);
        }
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

