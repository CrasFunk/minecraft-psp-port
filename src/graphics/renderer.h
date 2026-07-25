#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include <pspgu.h>

typedef struct {
    uint32_t width;
    uint32_t height;
    float fov;
    int initialized;
} renderer_t;

int renderer_init(void);
void renderer_shutdown(void);
void renderer_begin_frame(void);
void renderer_end_frame(void);
void renderer_clear_screen(uint32_t color);
void renderer_draw_cube(float x, float y, float z, uint32_t color);

#endif
