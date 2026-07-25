#include "perlin.h"
#include <math.h>

static uint32_t hash_func(uint32_t x, uint32_t y, uint32_t z, uint32_t seed) {
    uint32_t h = seed;
    h ^= (x * 73856093);
    h ^= (y * 19349663);
    h ^= (z * 83492791);
    h = (h ^ (h >> 13)) * 1274126177U;
    return h ^ (h >> 16);
}

float perlin_noise(float x, float y, float z, uint32_t seed) {
    int xi = (int)x & 255;
    int yi = (int)y & 255;
    int zi = (int)z & 255;
    
    float xf = x - (int)x;
    float yf = y - (int)y;
    float zf = z - (int)z;
    
    // Smooth interpolation curves
    float u = xf * xf * (3.0f - 2.0f * xf);
    float v = yf * yf * (3.0f - 2.0f * yf);
    float w = zf * zf * (3.0f - 2.0f * zf);
    
    // Hash corners
    uint32_t h000 = hash_func(xi, yi, zi, seed);
    uint32_t h100 = hash_func(xi + 1, yi, zi, seed);
    uint32_t h010 = hash_func(xi, yi + 1, zi, seed);
    uint32_t h110 = hash_func(xi + 1, yi + 1, zi, seed);
    uint32_t h001 = hash_func(xi, yi, zi + 1, seed);
    uint32_t h101 = hash_func(xi + 1, yi, zi + 1, seed);
    uint32_t h011 = hash_func(xi, yi + 1, zi + 1, seed);
    uint32_t h111 = hash_func(xi + 1, yi + 1, zi + 1, seed);
    
    // Normalize to 0-1
    float v000 = (float)(h000 & 0xFF) / 255.0f;
    float v100 = (float)(h100 & 0xFF) / 255.0f;
    float v010 = (float)(h010 & 0xFF) / 255.0f;
    float v110 = (float)(h110 & 0xFF) / 255.0f;
    float v001 = (float)(h001 & 0xFF) / 255.0f;
    float v101 = (float)(h101 & 0xFF) / 255.0f;
    float v011 = (float)(h011 & 0xFF) / 255.0f;
    float v111 = (float)(h111 & 0xFF) / 255.0f;
    
    // Interpolation
    float v00 = v000 + u * (v100 - v000);
    float v10 = v010 + u * (v110 - v010);
    float v01 = v001 + u * (v101 - v001);
    float v11 = v011 + u * (v111 - v011);
    
    float v0 = v00 + v * (v10 - v00);
    float v1 = v01 + v * (v11 - v01);
    
    return v0 + w * (v1 - v0);
}

float perlin_noise_2d(float x, float y, uint32_t seed) {
    return perlin_noise(x, y, 0.0f, seed);
}
