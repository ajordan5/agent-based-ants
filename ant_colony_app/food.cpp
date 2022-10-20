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

std::pair<int,int> Food::search(const Ant* ant)
{
    int piHalves = std::round(2*ant->heading / PI);
    int quadrant = piHalves%4;

    int yTop{0};
    int xLeft{0};
    int xRight{0};
    int yBottom{0};

    while (quadrant < 0)
    {
        quadrant = quadrant + 4;
    }

    switch(quadrant)
    {
        case 0:{
            yBottom = ant->y-sideSearchDistance;
            yTop = ant->y+sideSearchDistance;
            xLeft = ant->x;
            xRight = ant->x+forwardSearchDistance;
            break;
        }
        case 1:{
            xLeft = ant->x-sideSearchDistance;
            xRight = ant->x+sideSearchDistance;
            yBottom = ant->y;
            yTop = ant->y+forwardSearchDistance;
            break;
        }
        case 3:{
            xLeft = ant->x-sideSearchDistance;
            xRight = ant->x+sideSearchDistance;
            yTop = ant->y;
            yBottom = ant->y-forwardSearchDistance;
            break;
        }
        case 2:{
            yBottom = ant->y-sideSearchDistance;
            yTop = ant->y+sideSearchDistance;
            xRight = ant->x;
            xLeft = ant->x-forwardSearchDistance;
            break;
        }

    }

    return search_quadrant(ant->x, ant->y, xLeft, yTop, xRight, yBottom);

}

std::pair<int,int> Food::search_quadrant(int xAnt, int yAnt, int xLeft, int yTop, int xRight, int yBottom)
{
    double min_dist = INT_MAX;
    std::pair<int,int> nearest_food{-1,-1};
    for(int x = xLeft; x<=xRight; x++)
    {
        if(locations.count(x))
        {
            for(int y = yBottom; y<=yTop; y++)
            {
                if(locations[x].count(y))
                {
                    double dist = sqrt((xAnt-x)*(xAnt-x) + (yAnt-y)*(yAnt-y));
                    if (dist < min_dist)
                    {
                        min_dist = dist;
                        nearest_food = {x,y};
                    }
                }
            }
        }
    }

    return nearest_food;
}
