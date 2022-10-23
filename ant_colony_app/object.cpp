#include "object.h"

Object::Object()
{

}

void Object::add(double x, double y)
{
    x = int(x);
    y = int(y);
    if(locations.count(x) && locations[x].count(y)) return;
    total++;
    locations[x].insert(y);
}

void Object::remove(int x, int y)
{
    if(locations.count(x) && locations[x].count(y))
    {
        total--;
        locations[x].erase(y);
        if (locations[x].empty()) locations.erase(x);
    }


}

std::unordered_map<int, std::unordered_set<int>> Object::get_locations() const
{
    return locations;
}

int Object::get_total() const
{
    return total;
}

bool Object::contains(int x, int y)
{
    if (locations.count(x)) return locations[x].count(y);
    else return false;
}

std::pair<int,int> Object::search(double x, double y, double heading)
{
    int piHalves = std::round(2*heading / PI);
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
            yBottom = y-sideSearchDistance;
            yTop = y+sideSearchDistance;
            xLeft = x;
            xRight = x+forwardSearchDistance;
            break;
        }
        case 1:{
            xLeft = x-sideSearchDistance;
            xRight = x+sideSearchDistance;
            yBottom = y;
            yTop = y+forwardSearchDistance;
            break;
        }
        case 3:{
            xLeft = x-sideSearchDistance;
            xRight = x+sideSearchDistance;
            yTop = y;
            yBottom = y-forwardSearchDistance;
            break;
        }
        case 2:{
            yBottom = y-sideSearchDistance;
            yTop = y+sideSearchDistance;
            xRight = x;
            xLeft = x-forwardSearchDistance;
            break;
        }

    }

    return search_quadrant(x, y, xLeft, yTop, xRight, yBottom);

}

std::pair<int,int> Object::search_quadrant(double xAnt, double yAnt, int xLeft, int yTop, int xRight, int yBottom)
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
