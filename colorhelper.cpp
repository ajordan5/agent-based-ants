#include "colorhelper.h"

void set_rgba(int* coordinate, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
{
    unsigned char* rgba = reinterpret_cast<unsigned char*>(coordinate);
    rgba[3] = alpha;
    rgba[2] = r;
    rgba[1] = g;
    rgba[0] = b;
}

int grid_to_array_index(int width, int height, int xIdx, int yIdx)
{
    if (xIdx > width || yIdx > height || xIdx < 0 || yIdx < 0) return -1;
    return yIdx*width + xIdx;
}

bool decay_alpha(int* coordinate, unsigned char decayRate)
{
    unsigned char* rgba = reinterpret_cast<unsigned char*>(coordinate);
    unsigned char alpha = rgba[3];
    if (decayRate >= alpha)
    {
        rgba[3] = 0;
        return true;
    }
    else
    {
        rgba[3] = rgba[3] - decayRate;
        return false;
    }
}

void map_strength_to_alpha(int* pixel, double pheromoneStrength, double initPheromoneStrength)
{
    unsigned char* rgba = reinterpret_cast<unsigned char*>(pixel);
    if (pheromoneStrength >= initPheromoneStrength)
        rgba[3] = 205;
    else
        rgba[3] = int(pheromoneStrength/initPheromoneStrength * 205);

}
