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

bool Ant::to_target(int targetX, int targetY)
{
    double xDiff = targetX - x;
    double yDiff = targetY - y;
    double distance = sqrt((xDiff)*(xDiff) + (yDiff)*(yDiff));
    double direction = atan2(yDiff , xDiff);

    double travelDistance = speed*timeStep;

    if (travelDistance > distance)
    {
        x = targetX;
        y = targetY;
        heading = direction;
        hasFood = !hasFood;
        return true;
    }
    else
    {
        heading = std::min(direction, maxTurn);
        x = x + cos(heading)*speed*timeStep;
        y = y + sin(heading)*speed*timeStep;
        return false;

    }
}

