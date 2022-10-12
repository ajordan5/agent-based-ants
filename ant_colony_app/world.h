#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "ant.h"

class World
{
public:
    World();

private:
    std::vector<Ant*> Ants;

};

#endif // WORLD_H
