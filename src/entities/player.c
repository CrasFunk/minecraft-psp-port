#include "player.h"
#include "../world/world.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define GRAVITY 0.08f
#define JUMP_FORCE 0.42f
#define PLAYER_SPEED 0.1f
#define PLAYER_HEIGHT 1.8f
#define PLAYER_WIDTH 0.6f

player_t *player_create(float x, float y, float z) {
    player_t *player = (player_t *)malloc(sizeof(player_t));
    if (!player) return NULL;
    
    player->x = x;
    player->y = y;
    player->z = z;
    player->vx = 0.0f;
    player->vy = 0.0f;
    player->vz = 0.0f;
    player->pitch = 0.0f;
    player->yaw = 0.0f;
    player->speed = PLAYER_SPEED;
    player->jumping = 0;
    player->selected_slot = 0;
    
    // Initialize inventory (36 slots)
    memset(player->inventory, 0, sizeof(player->inventory));
    
    return player;
}

void player_destroy(player_t *player) {
    if (player) {
        free(player);
    }
}

static int check_collision(player_t *player, world_t *world, float new_x, float new_y, float new_z) {
    // Simple AABB collision detection
    int bx_min = (int)(new_x - PLAYER_WIDTH / 2.0f);
    int bx_max = (int)(new_x + PLAYER_WIDTH / 2.0f);
    int by_min = (int)(new_y);
    int by_max = (int)(new_y + PLAYER_HEIGHT);
    int bz_min = (int)(new_z - PLAYER_WIDTH / 2.0f);
    int bz_max = (int)(new_z + PLAYER_WIDTH / 2.0f);
    
    for (int x = bx_min; x <= bx_max; x++) {
        for (int y = by_min; y <= by_max; y++) {
            for (int z = bz_min; z <= bz_max; z++) {
                uint8_t block = world_get_block(world, x, y, z);
                if (block != 0 && block != 5) { // Not air or water
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

void player_update(player_t *player, void *world_ptr) {
    if (!player || !world_ptr) return;
    
    world_t *world = (world_t *)world_ptr;
    
    // Apply gravity
    player->vy -= GRAVITY;
    
    // Clamp falling speed
    if (player->vy < -0.5f) {
        player->vy = -0.5f;
    }
    
    // Apply velocity
    float new_x = player->x + player->vx;
    float new_y = player->y + player->vy;
    float new_z = player->z + player->vz;
    
    // Collision detection on Y axis
    if (!check_collision(player, world, player->x, new_y, player->z)) {
        player->y = new_y;
    } else {
        if (player->vy < 0.0f) {
            player->jumping = 0;
        }
        player->vy = 0.0f;
    }
    
    // Collision detection on X axis
    if (!check_collision(player, world, new_x, player->y, player->z)) {
        player->x = new_x;
    } else {
        player->vx = 0.0f;
    }
    
    // Collision detection on Z axis
    if (!check_collision(player, world, player->x, player->y, new_z)) {
        player->z = new_z;
    } else {
        player->vz = 0.0f;
    }
    
    // Friction
    player->vx *= 0.9f;
    player->vz *= 0.9f;
    
    // Clamp position within world bounds
    if (player->y < 0.0f) {
        player->y = 64.0f;
        player->vy = 0.0f;
    }
}

void player_render(player_t *player) {
    // First-person camera rendering
    // This would be integrated with the renderer
}

void player_handle_input(player_t *player, SceCtrlData *pad) {
    if (!player || !pad) return;
    
    // Movement
    if (pad->Buttons & PSP_CTRL_UP) {
        player->vz -= player->speed;
    }
    if (pad->Buttons & PSP_CTRL_DOWN) {
        player->vz += player->speed;
    }
    if (pad->Buttons & PSP_CTRL_LEFT) {
        player->vx -= player->speed;
    }
    if (pad->Buttons & PSP_CTRL_RIGHT) {
        player->vx += player->speed;
    }
    
    // Jump
    if (pad->Buttons & PSP_CTRL_CROSS && !player->jumping) {
        player->vy = JUMP_FORCE;
        player->jumping = 1;
    }
    
    // Look around (analog sticks)
    if (pad->Lx > 128) {
        player->yaw += 0.02f;
    }
    if (pad->Lx < 127) {
        player->yaw -= 0.02f;
    }
    if (pad->Ly > 128) {
        player->pitch -= 0.02f;
    }
    if (pad->Ly < 127) {
        player->pitch += 0.02f;
    }
    
    // Clamp pitch
    if (player->pitch > 1.57f) player->pitch = 1.57f;
    if (player->pitch < -1.57f) player->pitch = -1.57f;
}
