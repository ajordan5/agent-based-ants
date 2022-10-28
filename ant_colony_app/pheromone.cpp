#include "pheromone.h"

Pheromone::Pheromone(size_t w, size_t h) : width{w}, height{h}
{
    strengths.resize((w+1)*(h+1));
    sideSearchDistance = 4;
    forwardSearchDistance = 4;
}

const unsigned char* Pheromone::get_strengths() const
{
    return reinterpret_cast<const unsigned char*>(strengths.data());
}

const unsigned char* Pheromone::get_pixel(int x, int y) const
{
    int arrayIndex = grid_to_array_index(width, height, x, y);
    return reinterpret_cast<const unsigned char*>(&strengths[arrayIndex]);
}

unsigned char Pheromone::get_decay_rate() const
{
    return decayRate;
}

void Pheromone::add(double x, double y)
{
    x = int(x);
    y = int(y);
    if(locations.count(x) && locations[x].count(y)) return;
    total++;
    locations[x].insert(y);

    int arrayIndex = grid_to_array_index(width, height, x, y);
    set_rgba(&strengths[arrayIndex], red, green, blue, 255);
}

void Pheromone::set_color(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
}

void Pheromone::update()
{
    std::unordered_map<int, std::unordered_set<int>> locations_copy(locations);
    for (auto i = locations_copy.begin();  i != locations_copy.end(); i++)
    {

        int x = i->first;
        std::unordered_set<int> ys = i->second;
        for (auto y = ys.begin(); y != ys.end(); y++)
        {
            int arrayIndex = grid_to_array_index(width, height, x, *y);
            bool removed = decay_alpha(&strengths[arrayIndex], decayRate);
            if (removed)
                remove(x, *y);
        }
    }

}
