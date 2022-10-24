#ifndef ANT_H
#define ANT_H

#define PI 3.14159

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

    void propogate_dynamics(std::pair<double,double> bounds);
    void random_walk(std::pair<double,double> bounds);
    bool to_target(std::pair<double,double> target, std::pair<double,double> bounds);

protected:
    double speed{15};
    double headingRate{0};
    double turnScale{0.01};
    double timeStep{0.1};
    double maxTurn{1};

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

};

#endif // ANT_H
