#include "renderer.h"
#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_WIDTH 512
#define BUFFER_HEIGHT 272
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

static unsigned int __attribute__((aligned(16))) display_list[262144];
static uint32_t *frame_buffer;
static uint32_t *depth_buffer;
static renderer_t g_renderer;

int renderer_init(void) {
    sceGuInit();
    sceGuStart(GU_DIRECT, display_list);
    
    frame_buffer = (uint32_t *)0x44000000;
    depth_buffer = (uint32_t *)0x44044000;
    
    sceGuDrawBuffer(GU_PSM_8888, frame_buffer, BUFFER_WIDTH);
    sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, (void *)0x44044000, BUFFER_WIDTH);
    
    sceGuDepthBuffer(depth_buffer, BUFFER_WIDTH);
    sceGuOffset(2048 - (SCREEN_WIDTH / 2), 2048 - (SCREEN_HEIGHT / 2));
    sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    sceGuDepthRange(65535, 0);
    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuFrontFace(GU_CW);
    sceGuEnable(GU_CULL_FACE);
    sceGuEnable(GU_DEPTH_TEST);
    
    sceGuFinish();
    sceGuSync(0, 0);
    
    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_ON);
    
    g_renderer.width = SCREEN_WIDTH;
    g_renderer.height = SCREEN_HEIGHT;
    g_renderer.fov = 75.0f;
    g_renderer.initialized = 1;
    
    return 0;
}

void renderer_shutdown(void) {
    sceGuTerm();
    g_renderer.initialized = 0;
}

void renderer_begin_frame(void) {
    sceGuStart(GU_DIRECT, display_list);
    sceGuClearColor(0xFF5A5A5A);
    sceGuClearDepth(0);
    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
}

void renderer_end_frame(void) {
    sceGuFinish();
    sceGuSync(0, 0);
    sceDisplayWaitVblankStart();
    
    static int flip = 0;
    if (flip) {
        sceGuDrawBuffer(GU_PSM_8888, frame_buffer, BUFFER_WIDTH);
        sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, (void *)0x44044000, BUFFER_WIDTH);
    } else {
        sceGuDrawBuffer(GU_PSM_8888, (void *)0x44044000, BUFFER_WIDTH);
        sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, frame_buffer, BUFFER_WIDTH);
    }
    flip ^= 1;
}

void renderer_clear_screen(uint32_t color) {
    sceGuClearColor(color);
    sceGuClear(GU_COLOR_BUFFER_BIT | GU_DEPTH_BUFFER_BIT);
}

typedef struct {
    float x, y, z;
    uint32_t color;
} vertex_t;

void renderer_draw_cube(float x, float y, float z, uint32_t color) {
    // Simplified cube rendering
    // This would be expanded with proper vertex buffers and matrices
}
