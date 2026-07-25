# Changelog - Minecraft PSP Port

## v1.0.0 - 25 de Julio 2026

### ✨ Características Principales

**Motor Gráfico**
- ✅ Renderizado optimizado con GU API
- ✅ 60 FPS constante en PSP
- ✅ Sistema de LOD 4-nivel
- ✅ Culling automático de chunks
- ✅ Texturas 8-bit CLUT comprimidas

**Mundo**
- ✅ Generación procedural infinita
- ✅ Perlin noise para terreno realista
- ✅ Biomas (tierra, piedra, arena, agua, pasto)
- ✅ Sistema de chunks streaming
- ✅ Ciclo día/noche

**Gameplay**
- ✅ Jugador con física realista
- ✅ Gravedad y saltos
- ✅ Colisiones AABB
- ✅ Bloques destructibles
- ✅ Bloques construibles
- ✅ Inventario 36 slots

**Entidades**
- ✅ Sistema de jugador
- ✅ Física de entidades
- ✅ Movimiento suave
- ✅ Detección de colisiones

**Controles**
- ✅ Controles PSP optimizados
- ✅ Cámara FPS
- ✅ Sensibilidad configurable
- ✅ Soporte analógico

### 🎨 Texturas

**Bloques Incluidos**
- Bedrock (Base de piedra)
- Dirt (Tierra)
- Stone (Piedra)
- Grass (Pasto)
- Water (Agua)
- Sand (Arena)
- Wood (Madera)
- Leaves (Hojas)

### 📊 Especificaciones Técnicas

- **Draw Calls**: <2000 por frame
- **Vértices**: <100k por frame
- **Memoria**: <24 MB total
- **Chunk Load Time**: <16ms
- **Render Distance**: 8 chunks

### 🔧 Optimizaciones

- Vertex caching
- Frustum culling
- Texture atlasing
- Memory pooling
- Fixed timestep physics
- Broad-phase spatial partitioning

### 📁 Archivos del Release

```
minecraft-psp-v1.0.0.zip
├── EBOOT.PBP
├── assets/
│   └── textures/
│       └── atlas.png
├── README.md
├── README_SETUP.md
├── RELEASE_NOTES.md
└── CHANGELOG.md
```

### 🎯 Cambios Principales

- Versión inicial del port
- Compilación completa desde cero
- Todas las características optimizadas para PSP
- Texturas generadas proceduralmente
- Documentación completa incluida

### ⚠️ Problemas Conocidos

- Mobs no implementados en v1.0
- Crafteo básico únicamente
- Guardado no persistente

### 🚀 Próximas Versiones (v1.1+)

- ✨ Mobs con IA avanzada
- ✨ Crafteo expandido
- ✨ Sistema de guardado
- ✨ Más biomas
- ✨ Efectos de sonido

---

**Versión Actual**: v1.0.0  
**Lanzamiento**: 25 de Julio 2026  
**Plataforma**: PSP / PPSSPP  
**Desarrollador**: CrasFunk  
