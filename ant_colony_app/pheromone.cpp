#include "pheromone.h"

Pheromone::Pheromone(size_t w, size_t h) : width{w}, height{h}
{
    imageBuffer.resize((w+1)*(h+1));
    strengthsDouble.resize((w+1)*(h+1));
    sideSearchDistance = 4;
    forwardSearchDistance = 4;
}

const unsigned char* Pheromone::get_image() const
{
    return reinterpret_cast<const unsigned char*>(imageBuffer.data());
}

const unsigned char* Pheromone::get_pixel(int x, int y) const
{
    int arrayIndex = grid_to_array_index(width, height, x, y);
    return reinterpret_cast<const unsigned char*>(&imageBuffer[arrayIndex]);
}

const double Pheromone::get_strength(int x, int y) const
{
    int arrayIndex = grid_to_array_index(width, height, x, y);
    if (arrayIndex < 0) return 0;
    return strengthsDouble[arrayIndex];
}

double Pheromone::get_decay_rate() const
{
    return decayRate;
}

double Pheromone::get_init_strength() const
{
    return initPheromoneStrength;
}

void Pheromone::add(double x, double y)
{
    x = int(x);
    y = int(y);
//    if(locations.count(x) && locations[x].count(y)) return;
    total++;
    locations[x].insert(y);

    int arrayIndex = grid_to_array_index(width, height, x, y);
    if (arrayIndex < 0) return;
    set_rgba(&imageBuffer[arrayIndex], red, green, blue, 255);
    strengthsDouble[arrayIndex] += initPheromoneStrength;
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
            decay(x, *y);
        }
    }

}

void Pheromone::decay(int x, int y)
{
    int index = grid_to_array_index(width, height, x, y);
    if (index < 0) return;
    strengthsDouble[index] = strengthsDouble[index] - decayRate;
    if (strengthsDouble[index] <= 0)
    {
        strengthsDouble[index] = 0;
        remove(x, y);
    }

    map_strength_to_alpha(&imageBuffer[index], strengthsDouble[index], initPheromoneStrength);
}

double Pheromone::ray_search(Ant* ant) const
{
    double strongestPheromone{0};
    double strongestHeading{-PI};

    std::vector<double> headings{-searchAzimuth, 0, searchAzimuth};
    for (int i = 0; i < headings.size(); i++)
    {
        std::pair<int,int> grid = propogate_ray(ant, headings[i]);
        double strength = get_strength(grid.first, grid.second);

        if (strength > strongestPheromone)
        {
            strongestPheromone = strength;
            strongestHeading = headings[i];
        }

    }

    return strongestHeading;
}

std::pair<int, int> Pheromone::propogate_ray(Ant* ant, double angle) const
{
    double x = ant->x + std::cos(ant->heading + angle)*searchDistance;
    double y = ant->y + std::sin(ant->heading + angle)*searchDistance;
    int xGrid = int(round(x));
    int yGrid = int(round(y));
    return {xGrid, yGrid};
}


