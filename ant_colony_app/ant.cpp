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
    headingRate = walk * turnScale;
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

    if (travelDistance >= distanceToTarget)
    {
        x = target.first;
        y = target.second;
        heading = heading - PI;
        hasFood = !hasFood;
        return true;
    }
    else
    {
        double angleSign{direction >= 0 ? 1.0 : -1.0};
        abs(direction - heading) > maxTurn ? heading =  angleSign*maxTurn
                                            : heading = direction;
        propogate_dynamics(bounds);
        return false;

    }
}

void Ant::heading_to_target(std::pair<double,double> target, std::pair<double,double> bounds)
{
    double xDiff = target.first - x;
    double yDiff = target.second - y;
    double direction = atan2(yDiff , xDiff);

    heading = std::min(direction, maxTurn);
    propogate_dynamics(bounds);


}

void Ant::propogate_dynamics(std::pair<double,double> bounds)
{
    x = x + cos(heading)*speed*timeStep;
    y = y + sin(heading)*speed*timeStep;

    if (x > bounds.first || x < 0)
    {
        heading = PI - heading;
        headingRate = 0;
        x > 0 ? x = bounds.first : x = 0;
    }

    if (y > bounds.first || y < 0)
    {
        heading = 2*PI - heading;
        headingRate = 0;
        y > 0 ? y = bounds.first : y = 0;
    }

}

