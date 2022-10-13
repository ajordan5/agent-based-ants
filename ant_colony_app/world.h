#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "ant.h"

class World
{
public:
    World();

private:
    std::vector<Ant*> ants;
    void add_ant(double x, double y);
    void add_many_ants(int num_of_ants);

};

#endif // WORLD_H
