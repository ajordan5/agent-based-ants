#ifndef FOOD_H
#define FOOD_H

#include <unordered_map>
#include <unordered_set>

class Food
{
public:
    Food();
    void add_food(int x, int y);
    const std::unordered_map<int, std::unordered_set<int>>* get_locations() const;
     const int get_total() const;

private:
    std::unordered_map<int, std::unordered_set<int>> locations;
    int total{0};

};

#endif // FOOD_H
