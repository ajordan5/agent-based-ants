#ifndef COLORHELPER_H
#define COLORHELPER_H

void set_rgba(int* coordinate, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha);
int grid_to_array_index(int width, int height, int xIdx, int yIdx);

#endif // COLORHELPER_H
