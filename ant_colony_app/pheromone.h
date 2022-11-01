#ifndef PHEROMONE_H
#define PHEROMONE_H

#include <vector>
#include "object.h"
#include "ant.h"
#include "colorhelper.h"

class Pheromone : public Object
{
public:
    Pheromone(size_t width, size_t height);
    const unsigned char* get_image() const;
    const unsigned char* get_pixel(int x, int y) const;
    const double get_strength(int x, int y) const;
    void add(double x, double y) override;
    void set_color(int r, int g, int b);
    double get_decay_rate() const;
    double get_init_strength() const;
    void update();
    double ray_search(Ant* a) const;

protected:
    size_t width{0};
    size_t height{0};
    int red{255};
    int green{0};
    int blue{0};
    double searchAzimuth{15.0 * PI/180};
    double searchDistance{5.0};
    std::vector<int> imageBuffer;
    std::vector<double> strengthsDouble;
    double decayRate{0.15};
    double initPheromoneStrength{100};

    void decay(int index);
    std::pair<int, int> propogate_ray(Ant* ant, double angle) const;
};

#endif // PHEROMONE_H
