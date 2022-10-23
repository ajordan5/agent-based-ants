#include "pheromone.h"

Pheromone::Pheromone(size_t w, size_t h) : width{w}, height{h}
{
    strengths.resize(w*h);
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

void Pheromone::add(int x, int y)
{
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
