#ifndef WORLD_H
#define WORLD_H

#include <stdint.h>
#include <stddef.h>

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 128
#define RENDER_DISTANCE 8

typedef struct {
    uint8_t blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
    int x, z;
    int loaded;
} chunk_t;

typedef struct {
    chunk_t *chunks[RENDER_DISTANCE * 2][RENDER_DISTANCE * 2];
    uint32_t seed;
    int time_of_day;
    float fog_distance;
} world_t;

world_t *world_create(uint32_t seed);
void world_destroy(world_t *world);
void world_update(world_t *world);
void world_render(world_t *world, void *player);
chunk_t *world_get_chunk(world_t *world, int chunk_x, int chunk_z);
uint8_t world_get_block(world_t *world, int x, int y, int z);
void world_set_block(world_t *world, int x, int y, int z, uint8_t block);

#endif
