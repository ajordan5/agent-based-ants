#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "ant.h"
#include "food.h"
#include "pheromone.h"

class World
{
public:
    World();
    World(double home_x, double home_y);
    void add_ant(double x, double y);
    void add_ant(Ant& ant);
    void add_many_ants(int num_of_ants);

    struct Colony
    {
        double x{0};
        double y{0};
        int food_count{0};
    };

    const Colony* get_home() const;
    Food* get_food() const;
    const Pheromone* get_food_pheromones() const;
    std::pair<double,double> get_bounds() const;
    const std::vector<Ant*> get_ants() const;
    double get_ant_population() const;
    void store_food();
    void update();

protected:
    Colony homeBase;
    std::vector<Ant*> ants;
    std::pair<double,double> worldBounds{1000, 1000};
    int antPopulation;
    Food* food{nullptr};
    Pheromone* foodPheromones{nullptr};

};

#endif // WORLD_H
