#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "ant.h"
#include "food.h"

class World
{
public:
    World();
    World(double home_x, double home_y);
    void add_ant(double x, double y);
    void add_many_ants(int num_of_ants);
    int ant_population;
    Food* food{nullptr};

    struct Colony
    {
        double x{0};
        double y{0};
        int food_count{0};
    };

    const Colony* get_home() const;
    const std::pair<double,double> get_bounds() const;
    const std::vector<Ant*> get_ants() const;
    void store_food();
    void update();

private:
    Colony homeBase;
    std::vector<Ant*> ants;
    std::pair<double,double> world_bounds{100, 100};

};

#endif // WORLD_H
