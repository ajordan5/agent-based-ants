#ifndef PHEROMONE_H
#define PHEROMONE_H

#include <vector>
#include "object.h"
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
    unsigned char get_decay_rate() const;
    double get_init_strength() const;
    void update();

protected:
    size_t width{0};
    size_t height{0};
    int red{255};
    int green{0};
    int blue{0};
    std::vector<int> imageBuffer;
    std::vector<double> strengthsDouble;
    unsigned char decayRate{1};
    double initPheromoneStrength{100};

    void decay(int x, int y);
};

#endif // PHEROMONE_H
