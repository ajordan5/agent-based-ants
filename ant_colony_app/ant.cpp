#include "ant.h"

Ant::Ant() : x{0}, y{0}, heading{0}, gen(rd()), dis(0, 1)
{
    std::srand(time(0));

}

Ant::Ant(double x0, double y0, double heading0) : x{x0}, y{y0}, heading{heading0}, gen(rd()), dis(0, 1)
{
    std::srand(time(0));
}

void Ant::random_walk(std::pair<double,double> bounds)
{
    double walk = 2*(dis(gen) - 0.5);
    headingRate = headingRate + walk * turnScale;
    heading = heading + headingRate*timeStep;

    propogate_dynamics(bounds);

}

bool Ant::to_target(std::pair<double,double> target, std::pair<double,double> bounds)
{
    double xDiff = target.first - x;
    double yDiff = target.second - y;
    double distanceToTarget = sqrt((xDiff)*(xDiff) + (yDiff)*(yDiff));
    double direction = atan2(yDiff , xDiff);

    double travelDistance = speed*timeStep;

    if (travelDistance > distanceToTarget)
    {
        x = target.first;
        y = target.second;
        heading = direction;
        hasFood = !hasFood;
        return true;
    }
    else
    {
        heading = std::min(direction, maxTurn);
        propogate_dynamics(bounds);
        return false;

    }
}

void Ant::propogate_dynamics(std::pair<double,double> bounds)
{
    x = x + cos(heading)*speed*timeStep;
    y = y + sin(heading)*speed*timeStep;
}

