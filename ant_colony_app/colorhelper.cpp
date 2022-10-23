#include "colorhelper.h"

void set_rgba(int* coordinate, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
{
    unsigned char* rgba = reinterpret_cast<unsigned char*>(coordinate);
    rgba[3] = alpha;
    rgba[2] = b;
    rgba[1] = g;
    rgba[0] = r;
}

int grid_to_array_index(int width, int height, int xIdx, int yIdx)
{
    return yIdx*width + xIdx;
}
