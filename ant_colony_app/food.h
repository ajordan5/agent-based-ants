#ifndef FOOD_H
#define FOOD_H

#define PI 3.14159

#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <math.h>
#include "ant.h"

class Food
{
public:
    Food();
    void add_food(int x, int y);
    void remove_food(int x, int y);
    const std::unordered_map<int, std::unordered_set<int>>* get_locations() const;
    const int get_total() const;
    std::pair<int,int> search(const Ant* ant);

protected:
    std::unordered_map<int, std::unordered_set<int>> locations;
    std::pair<int,int> search_quadrant(int xAnt, int yAnt, int xLeft, int yTop, int xRight, int yBottom);
    int sideSearchDistance{20};
    int forwardSearchDistance{30};
    int total{0};

};

#endif // FOOD_H
