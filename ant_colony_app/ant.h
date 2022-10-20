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
    bool hasFood{false};

    void propogate_dynamics(double heading);
    void random_walk(std::pair<double,double> bounds);
    bool to_target(std::pair<double,double> target, std::pair<double,double> bounds);

private:
    double speed{50};
    double headingRate{0};
    double turnScale{0.15};
    double timeStep{0.1};
    double maxTurn{1};

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

};

#endif // ANT_H
