#ifndef PLAYER_H
#define PLAYER_H

#include <pspctrl.h>

typedef struct {
    float x, y, z;
    float vx, vy, vz;
    float pitch, yaw;
    float speed;
    int jumping;
    int inventory[36];
    int selected_slot;
    void *world;
} player_t;

player_t *player_create(float x, float y, float z);
void player_destroy(player_t *player);
void player_update(player_t *player, void *world);
void player_render(player_t *player);
void player_handle_input(player_t *player, SceCtrlData *pad);

#endif
