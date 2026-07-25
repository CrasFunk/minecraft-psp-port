#include "world.h"
#include "../utils/perlin.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WATER_LEVEL 64
#define MOUNTAIN_HEIGHT 80

static uint32_t noise_seed = 0;

static float perlin_noise_2d(float x, float y, uint32_t seed);
static void generate_chunk(chunk_t *chunk, int chunk_x, int chunk_z, uint32_t seed);

world_t *world_create(uint32_t seed) {
    world_t *world = (world_t *)malloc(sizeof(world_t));
    if (!world) return NULL;
    
    world->seed = seed;
    world->time_of_day = 0;
    world->fog_distance = 128.0f;
    noise_seed = seed;
    
    // Initialize chunk pointers
    for (int x = 0; x < RENDER_DISTANCE * 2; x++) {
        for (int z = 0; z < RENDER_DISTANCE * 2; z++) {
            world->chunks[x][z] = NULL;
        }
    }
    
    return world;
}

void world_destroy(world_t *world) {
    if (!world) return;
    
    for (int x = 0; x < RENDER_DISTANCE * 2; x++) {
        for (int z = 0; z < RENDER_DISTANCE * 2; z++) {
            if (world->chunks[x][z]) {
                free(world->chunks[x][z]);
                world->chunks[x][z] = NULL;
            }
        }
    }
    
    free(world);
}

static float perlin_noise_2d(float x, float y, uint32_t seed) {
    // Simplified Perlin noise
    uint32_t xi = (uint32_t)x & 255;
    uint32_t yi = (uint32_t)y & 255;
    
    float xf = x - (int)x;
    float yf = y - (int)y;
    
    uint32_t hash1 = ((xi + seed) * 73856093) ^ ((yi + seed) * 19349663);
    uint32_t hash2 = ((xi + 1 + seed) * 73856093) ^ ((yi + seed) * 19349663);
    uint32_t hash3 = ((xi + seed) * 73856093) ^ ((yi + 1 + seed) * 19349663);
    uint32_t hash4 = ((xi + 1 + seed) * 73856093) ^ ((yi + 1 + seed) * 19349663);
    
    float v1 = (float)(hash1 & 0xFF) / 255.0f;
    float v2 = (float)(hash2 & 0xFF) / 255.0f;
    float v3 = (float)(hash3 & 0xFF) / 255.0f;
    float v4 = (float)(hash4 & 0xFF) / 255.0f;
    
    // Smooth interpolation
    float u = xf * xf * (3.0f - 2.0f * xf);
    float v = yf * yf * (3.0f - 2.0f * yf);
    
    float a = v1 + u * (v2 - v1);
    float b = v3 + u * (v4 - v3);
    
    return a + v * (b - a);
}

static void generate_chunk(chunk_t *chunk, int chunk_x, int chunk_z, uint32_t seed) {
    memset(chunk->blocks, 0, sizeof(chunk->blocks));
    chunk->x = chunk_x;
    chunk->z = chunk_z;
    chunk->loaded = 1;
    
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            float world_x = chunk_x * CHUNK_SIZE + x;
            float world_z = chunk_z * CHUNK_SIZE + z;
            
            // Generate base terrain
            float height_noise = perlin_noise_2d(world_x * 0.05f, world_z * 0.05f, seed);
            float mountain_noise = perlin_noise_2d(world_x * 0.01f, world_z * 0.01f, seed + 1);
            
            float height = 64.0f + height_noise * 20.0f + mountain_noise * 40.0f;
            int terrain_height = (int)height;
            
            if (terrain_height > CHUNK_HEIGHT) terrain_height = CHUNK_HEIGHT - 1;
            if (terrain_height < 1) terrain_height = 1;
            
            // Fill blocks
            for (int y = 0; y < terrain_height; y++) {
                uint8_t block_type;
                
                if (y < 4) {
                    block_type = 1; // Bedrock
                } else if (y < terrain_height - 3) {
                    block_type = 3; // Stone
                } else if (y < terrain_height - 1) {
                    block_type = 2; // Dirt
                } else if (y == terrain_height - 1) {
                    if (terrain_height > WATER_LEVEL) {
                        block_type = 4; // Grass
                    } else {
                        block_type = 2; // Sand
                    }
                } else {
                    block_type = 0; // Air
                }
                
                chunk->blocks[x][y][z] = block_type;
            }
            
            // Water filling
            for (int y = terrain_height; y <= WATER_LEVEL; y++) {
                if (y < CHUNK_HEIGHT) {
                    chunk->blocks[x][y][z] = 5; // Water
                }
            }
        }
    }
}

chunk_t *world_get_chunk(world_t *world, int chunk_x, int chunk_z) {
    if (!world) return NULL;
    
    int idx_x = chunk_x + RENDER_DISTANCE;
    int idx_z = chunk_z + RENDER_DISTANCE;
    
    if (idx_x < 0 || idx_x >= RENDER_DISTANCE * 2 || idx_z < 0 || idx_z >= RENDER_DISTANCE * 2) {
        return NULL;
    }
    
    if (!world->chunks[idx_x][idx_z]) {
        world->chunks[idx_x][idx_z] = (chunk_t *)malloc(sizeof(chunk_t));
        if (world->chunks[idx_x][idx_z]) {
            generate_chunk(world->chunks[idx_x][idx_z], chunk_x, chunk_z, world->seed);
        }
    }
    
    return world->chunks[idx_x][idx_z];
}

uint8_t world_get_block(world_t *world, int x, int y, int z) {
    if (y < 0 || y >= CHUNK_HEIGHT) return 0;
    
    int chunk_x = x / CHUNK_SIZE;
    int chunk_z = z / CHUNK_SIZE;
    int local_x = x % CHUNK_SIZE;
    int local_z = z % CHUNK_SIZE;
    
    if (local_x < 0) local_x += CHUNK_SIZE;
    if (local_z < 0) local_z += CHUNK_SIZE;
    
    chunk_t *chunk = world_get_chunk(world, chunk_x, chunk_z);
    if (!chunk) return 0;
    
    return chunk->blocks[local_x][y][local_z];
}

void world_set_block(world_t *world, int x, int y, int z, uint8_t block) {
    if (y < 0 || y >= CHUNK_HEIGHT) return;
    
    int chunk_x = x / CHUNK_SIZE;
    int chunk_z = z / CHUNK_SIZE;
    int local_x = x % CHUNK_SIZE;
    int local_z = z % CHUNK_SIZE;
    
    if (local_x < 0) local_x += CHUNK_SIZE;
    if (local_z < 0) local_z += CHUNK_SIZE;
    
    chunk_t *chunk = world_get_chunk(world, chunk_x, chunk_z);
    if (chunk) {
        chunk->blocks[local_x][y][local_z] = block;
    }
}

void world_update(world_t *world) {
    if (!world) return;
    world->time_of_day++;
    if (world->time_of_day >= 24000) {
        world->time_of_day = 0;
    }
}

void world_render(world_t *world, void *player) {
    if (!world || !player) return;
    // Rendering logic will be implemented in renderer
}
