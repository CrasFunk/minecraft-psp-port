#ifndef PERLIN_H
#define PERLIN_H

#include <stdint.h>

float perlin_noise(float x, float y, float z, uint32_t seed);
float perlin_noise_2d(float x, float y, uint32_t seed);

#endif
