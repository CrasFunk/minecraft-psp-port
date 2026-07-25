#include "engine.h"
#include <stdlib.h>
#include <pspkernel.h>
#include <psptypes.h>

static uint64_t last_tick = 0;
static engine_t *g_engine = NULL;

engine_t *engine_init(void) {
    engine_t *engine = (engine_t *)malloc(sizeof(engine_t));
    if (!engine) return NULL;
    
    engine->frame_count = 0;
    engine->delta_time = 0.0f;
    engine->fps = 0.0f;
    engine->memory_used = 0;
    engine->initialized = 1;
    
    last_tick = sceKernelGetSystemTimeWide();
    g_engine = engine;
    
    return engine;
}

void engine_shutdown(engine_t *engine) {
    if (engine) {
        free(engine);
    }
}

void engine_update(engine_t *engine) {
    if (!engine) return;
    
    uint64_t current_tick = sceKernelGetSystemTimeWide();
    engine->delta_time = (float)(current_tick - last_tick) / 1000000.0f;
    
    if (engine->delta_time > 0.0f) {
        engine->fps = 1.0f / engine->delta_time;
    }
    
    last_tick = current_tick;
    engine->frame_count++;
}

float engine_get_delta_time(engine_t *engine) {
    return engine ? engine->delta_time : 0.0f;
}

uint32_t engine_get_frame_count(engine_t *engine) {
    return engine ? engine->frame_count : 0;
}
