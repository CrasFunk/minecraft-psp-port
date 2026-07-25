# Minecraft PSP Port - Architecture Documentation

## Overview

This document describes the architecture and design decisions for the Minecraft PSP Port, optimized for PSP hardware constraints.

## Hardware Constraints

- **CPU**: 333 MHz Allegrex (MIPS R4000 variant)
- **RAM**: 32 MB (shared between system and game)
- **GPU**: PSP GU (Graphics Unit) with 2 MB embedded DRAM
- **Display**: 480x272 @ 60 Hz
- **Storage**: UMD (up to 1.8 GB) or Memory Stick

## Core Systems

### 1. Rendering Engine (`src/graphics/`)

**Purpose**: High-performance 3D rendering optimized for PSP

**Key Components**:
- `renderer.c`: GU initialization, frame management
- Vertex caching and batching
- Level of Detail (LOD) system
- Culling algorithms

**Optimizations**:
- Fixed-function pipeline (no shaders on PSP)
- Vertex buffer objects (VBO) with indexed rendering
- Texture compression (CLUT 8-bit)
- Early depth testing
- Back-face culling

### 2. World Generation (`src/world/`)

**Purpose**: Procedural generation of infinite worlds

**Key Components**:
- `world.c`: Chunk management and loading
- `../utils/perlin.c`: Perlin noise implementation

**Features**:
- Chunk-based streaming (16x128x16 blocks per chunk)
- Deterministic seeding (same seed = same world)
- Multi-layer terrain (bedrock, stone, dirt, grass)
- Water generation at fixed level
- LOD 4 levels of detail

**Memory Strategy**:
- Only 16x16 chunks loaded at once (8 render distance in each direction)
- Streaming system loads/unloads chunks based on player position
- Chunks stored in cache with LRU eviction

### 3. Entity System (`src/entities/`)

**Purpose**: Player, mobs, and item management

**Key Components**:
- `player.c`: Player physics, input, camera

**Physics**:
- AABB collision detection
- Gravity and jump mechanics
- Ground detection
- Velocity-based movement

### 4. Block System (`src/blocks/`)

**Purpose**: Block types, properties, and interactions

**Block Types**:
- 0: Air
- 1: Bedrock
- 2: Dirt
- 3: Stone
- 4: Grass
- 5: Water
- 6: Sand
- 7: Wood
- 8: Leaves

## Memory Layout

```
32 MB RAM
├── System (16 MB) - Kernel, threads, system
├── Game Engine (4 MB)
│   ├── Code (2 MB)
│   └── Global data (2 MB)
├── Rendering (6 MB)
│   ├── Frame buffer (1 MB)
│   ├── Depth buffer (1 MB)
│   └── Vertex buffers (4 MB)
├── World (5 MB)
│   ├── Chunk cache (4 MB)
│   └── Terrain data (1 MB)
└── Game Logic (1 MB)
    ├── Entities
    ├── Inventory
    └── AI
```

## Performance Targets

- **Frame Rate**: 60 FPS constant
- **Draw Calls**: <2000 per frame
- **Vertex Count**: <100k per frame
- **Memory Usage**: <24 MB
- **Chunk Loading**: <16ms per frame

## Optimization Techniques

### 1. Rendering Optimization

- **Vertex Caching**: Pre-calculated vertex data for each chunk
- **Frustum Culling**: Only render chunks visible to camera
- **Occlusion Culling**: Skip chunks blocked by other chunks
- **LOD System**: Progressive detail levels
- **Texture Atlasing**: Single texture for all blocks

### 2. Physics Optimization

- **Broad-phase**: Grid-based spatial partitioning
- **Narrow-phase**: AABB intersection tests
- **Simplified Gravity**: No fluid dynamics
- **Fixed time-step**: 1/60s per frame

### 3. Memory Optimization

- **Chunk Streaming**: Load/unload dynamically
- **Texture Compression**: 8-bit CLUT format
- **Model Compression**: Simplified geometry
- **Memory Pooling**: Pre-allocated object pools

## Threading Model

- **Main Thread**: Game logic, rendering
- **IO Thread**: Chunk loading/saving
- **Callback Thread**: System events

## Build System

- **Makefile**: Primary build system
- **CMake**: Alternative (optional)
- **Python Scripts**: Asset generation

## Future Optimizations

1. SIMD vectorization for physics
2. Hardware T&L (Transform & Lighting)
3. Compressed chunk storage
4. Advanced LOD culling
5. Prefabricated structure generation
