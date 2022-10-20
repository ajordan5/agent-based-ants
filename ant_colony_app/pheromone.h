#ifndef PHEROMONE_H
#define PHEROMONE_H

#include <unordered_map>
#include <unordered_set>

class Pheromone
{
public:
    Pheromone();

protected:
    std::unordered_map<int, std::unordered_set<int>> locations;
    double** strengths;
};

#endif // PHEROMONE_H
