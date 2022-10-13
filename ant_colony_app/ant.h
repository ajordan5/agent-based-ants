#ifndef ANT_H
#define ANT_H

#include <time.h>
#include <random>
#include <math.h>
#include <iostream>

class Ant
{
public:
    Ant();
    Ant(double, double, double);
    double x;
    double y;
    double heading;

    void propogate_dynamics();

private:
    double speed{5};
    double heading_rate{0};
    double turn_scale{0.25};
    double time_step{0.1};

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

};

#endif // ANT_H
