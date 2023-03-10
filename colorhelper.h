#ifndef COLORHELPER_H
#define COLORHELPER_H

void set_rgba(int* pixel, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha);
int grid_to_array_index(int width, int height, int xIdx, int yIdx);
bool decay_alpha(int* coordinate, unsigned char decayRate);
void map_strength_to_alpha(int* pixel, double pheromoneStrength, double initPheromoneStrength);

#endif // COLORHELPER_H
