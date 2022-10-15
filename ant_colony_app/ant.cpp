#include "ant.h"

Ant::Ant() : x{0}, y{0}, heading{0}, gen(rd()), dis(0, 1)
{
    std::srand(time(0));

}

Ant::Ant(double x0, double y0, double heading0) : x{x0}, y{y0}, heading{heading0}, gen(rd()), dis(0, 1)
{
    std::srand(time(0));
}

void Ant::random_walk()
{
    double walk = 2*(dis(gen) - 0.5);
    headingRate = headingRate + walk * turnScale;
    heading = heading + headingRate*timeStep;

    x = x + cos(heading)*speed*timeStep;
    y = y + sin(heading)*speed*timeStep;

}

void Ant::to_food(int food_x, int food_y)
{
    double yDiff = food_y - y;
    double xDiff = food_x - x;
    double distance = sqrt((xDiff)*(xDiff) + (yDiff)*(yDiff));
    double direction = atan2(yDiff, xDiff);

    double travelDistance = speed*timeStep;

    if (travelDistance > distance)
    {
        x = food_x;
        y = food_y;
        heading = direction;
    }
    else
    {
        heading = std::min(direction, maxTurn);
        x = x + cos(heading)*speed*timeStep;
        y = y + sin(heading)*speed*timeStep;

    }
}

void Ant::propogate_dynamics()
{
    random_walk();
}
