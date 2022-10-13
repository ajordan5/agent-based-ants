#include "food.h"

Food::Food()
{

}

void Food::add_food(int x, int y)
{
    if(locations.count(x) && locations[x].count(y)) return;
    total++;
    locations[x].insert(y);
}

void Food::remove_food(int x, int y)
{
    if(locations.count(x) && locations[x].count(y))
    {
        total--;
        locations[x].erase(y);
        if (locations[x].empty()) locations.erase(x);
    }


}

const std::unordered_map<int, std::unordered_set<int>>* Food::get_locations() const
{
    return &locations;
}

const int Food::get_total() const
{
    return total;
}
