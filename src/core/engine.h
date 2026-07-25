#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint32_t frame_count;
    float delta_time;
    float fps;
    uint32_t memory_used;
    int initialized;
} engine_t;

engine_t *engine_init(void);
void engine_shutdown(engine_t *engine);
void engine_update(engine_t *engine);
float engine_get_delta_time(engine_t *engine);
uint32_t engine_get_frame_count(engine_t *engine);

#endif
