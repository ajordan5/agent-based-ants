#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "ant.h"

class World
{
public:
    World();
    World(double home_x, double home_y);

    struct Colony
    {
        double x{0};
        double y{0};
    };
    Colony get_home() const;

private:
    Colony home_base;
    std::vector<Ant*> ants;
    void add_ant(double x, double y);
    void add_many_ants(int num_of_ants);

};

#endif // WORLD_H
