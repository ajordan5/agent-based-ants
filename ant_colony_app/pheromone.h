#ifndef PHEROMONE_H
#define PHEROMONE_H

#include <vector>
#include "object.h"
#include "colorhelper.h"

class Pheromone : public Object
{
public:
    Pheromone(size_t width, size_t height);
    const unsigned char* get_strengths() const;
    const unsigned char* get_pixel(int x, int y) const;
    void add(double x, double y) override;
    void set_color(int r, int g, int b);

protected:
    size_t width{0};
    size_t height{0};
    int red{255};
    int green{0};
    int blue{0};
    std::vector<int> strengths;
};

#endif // PHEROMONE_H
