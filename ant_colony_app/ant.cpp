#include "ant.h"

Ant::Ant() : x{0}, y{0}, heading{0}, gen(rd()), dis(0, 1)
{
    std::srand(time(0));

}

Ant::Ant(double x0, double y0, double heading0) : x{x0}, y{y0}, heading{heading0}, gen(rd()), dis(0, 1)
{
    std::srand(time(0));
}

void Ant::propogate_dynamics()
{
    double walk = 2*(dis(gen) - 0.5);
    heading_rate = heading_rate + walk * turn_scale;
    heading = heading + heading_rate*time_step;

    x = x + cos(heading)*speed;
    y = y + sin(heading)*speed;

}
