#include "food.h"

Food::Food()
{

}

void Food::add_food(int x, int y)
{
    total++;
    locations[x].insert(y);
}

const std::unordered_map<int, std::unordered_set<int>>* Food::get_locations() const
{
    return &locations;
}

const int Food::get_total() const
{
    return total;
}
