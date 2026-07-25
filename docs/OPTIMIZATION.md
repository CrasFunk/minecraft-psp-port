# Optimization Guide - Minecraft PSP Port

## Rendering Pipeline

### Current Bottlenecks

1. **Draw Calls**: Batching is critical
2. **Texture Transfers**: Use CLUT format
3. **Vertex Processing**: Keep vertex count low
4. **Memory Bandwidth**: Optimize memory access patterns

### Optimization Techniques

#### 1. Vertex Batching

```c
// GOOD: Batch multiple chunks
for (int i = 0; i < chunk_count; i++) {
    add_chunk_vertices(chunks[i]);
}
sceGuDrawArray(GU_TRIANGLES, GU_INDEX_16BIT, vertex_count, indices, vertices);

// BAD: Multiple draw calls
for (int i = 0; i < chunk_count; i++) {
    sceGuDrawArray(...);
}
```

#### 2. Culling Strategy

```c
// Frustum culling
for (int i = 0; i < chunk_count; i++) {
    if (frustum_contains_aabb(chunks[i].bbox)) {
        render_chunk(chunks[i]);
    }
}

// Occlusion culling
for (int i = 0; i < chunk_count; i++) {
    if (!is_occluded(chunks[i])) {
        render_chunk(chunks[i]);
    }
}
```

#### 3. Level of Detail (LOD)

```c
typedef struct {
    float distance;
    int detail_level;  // 0-3
} chunk_lod_t;

void update_chunk_lod(chunk_t *chunk, float player_distance) {
    if (player_distance < 32.0f) {
        chunk->detail = 0;  // Full detail
    } else if (player_distance < 64.0f) {
        chunk->detail = 1;  // 50% reduction
    } else if (player_distance < 128.0f) {
        chunk->detail = 2;  // 75% reduction
    } else {
        chunk->detail = 3;  // 90% reduction
    }
}
```

## Memory Optimization

### Chunk Storage

```c
// Efficient chunk compression
typedef struct {
    uint8_t blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
    // 16 * 128 * 16 = 32,768 bytes per chunk (uncompressed)
    // With RLE: ~8,192 bytes average
} chunk_t;
```

### Texture Compression

- **Format**: CLUT 8-bit indexed
- **Size**: 256x256 = 64 KB (vs 256 KB for 32-bit)
- **Palette**: 256 colors, 1 KB

## Physics Optimization

### Broad-phase Culling

```c
typedef struct {
    int grid[WORLD_WIDTH/32][WORLD_HEIGHT/32][WORLD_DEPTH/32];
} spatial_grid_t;

void broad_phase(spatial_grid_t *grid, entity_t *entity) {
    int grid_x = entity->x / 32;
    int grid_z = entity->z / 32;
    // Only check entities in nearby grid cells
}
```

### Narrow-phase Optimization

```c
int aabb_intersect(aabb_t a, aabb_t b) {
    return !(a.max_x < b.min_x || a.min_x > b.max_x ||
             a.max_y < b.min_y || a.min_y > b.max_y ||
             a.max_z < b.min_z || a.min_z > b.max_z);
}
```

## CPU Optimization

### SIMD Operations

```c
// PSP uses MIPS SIMD (paired single operations)
// For vector math:
__asm__(
    "add.s $f0, $f4, $f8\n"
    "add.s $f2, $f6, $f10\n"
);
```

### Function Inlining

```c
// Mark frequently called functions as inline
static inline int is_block_solid(uint8_t block) {
    return block != 0 && block != 5;  // Not air or water
}
```

## Asset Pipeline

### Texture Generation

- Pre-generate all textures
- Use 8-bit CLUT format
- Store as atlas (reduces state changes)
- Compress with lz4 if needed

### Model Simplification

- Use cube primitives (no loaded models)
- Pre-calculate vertex data
- Store as index buffers

## Profiling Tools

### Frame Rate Monitoring

```c
static uint64_t frame_times[60];
static int frame_index = 0;

void update_fps() {
    uint64_t current = sceKernelGetSystemTimeWide();
    frame_times[frame_index] = current;
    frame_index = (frame_index + 1) % 60;
    
    uint64_t avg_time = frame_times[59] - frame_times[0];
    float fps = 60.0f * 1000000.0f / (float)avg_time;
}
```

### Memory Tracking

```c
#define TRACK_ALLOC(ptr, size) \
    printf("Alloc: %p (%d bytes)\n", ptr, size)

#define TRACK_FREE(ptr) \
    printf("Free: %p\n", ptr)
```

## Performance Targets

| Metric | Target | Current |
|--------|--------|----------|
| FPS | 60 | - |
| Draw Calls | <2000 | - |
| Vertices/Frame | <100k | - |
| Memory Usage | <24 MB | - |
| Chunk Load Time | <16ms | - |

## Further Optimization Ideas

1. **GPU Accelerated Terrain**: Use vertex shaders for LOD
2. **Occlusion Queries**: Skip rendering hidden geometry
3. **Texture Atlasing**: Further reduce state changes
4. **Prefab Systems**: Pre-baked structures
5. **Procedural Compression**: Store only chunk seed
