# Minecraft PSP Port - Fully Optimized from Scratch

Un port completo de Minecraft para PSP, optimizado desde cero con renderizado de alta performance, generación procedural de mundos, sistema de bloques destructibles, mobs, inventario y crafteo.

## 🎮 Características

- ✅ Motor gráfico optimizado para PSP (GU API)
- ✅ Generación procedural de mundos infinitos
- ✅ Sistema de chunks con LOD (Level of Detail)
- ✅ Bloques destructibles y construibles
- ✅ Inventario y sistema de crafteo
- ✅ Mobs básicos con IA
- ✅ Física simplificada (gravedad, colisiones)
- ✅ Día/Noche ciclo
- ✅ Texturas generadas proceduralmente
- ✅ Controles PSP optimizados

## 📋 Requisitos

- PSP con Custom Firmware (CFW)
- PPSSPP Emulator (para desarrollo)
- Python 3.8+
- GCC for PSP (psp-gcc)

## 🚀 Compilación Rápida

```bash
python scripts/generate_textures.py
make -C build
./run_emulator.sh build/minecraft.elf
```

## 📊 Especificaciones

| Componente | Spec |
|-----------|------|
| Plataforma | PSP (333 MHz, 32MB RAM) |
| Renderizado | GU API + Vertex Caching |
| Texturas | CLUT 8-bit comprimido |
| FPS Target | 60 FPS constante |
| Draw Calls | <2000 por frame |
| Chunks | Sistema de LOD 4-nivel |

## 📝 Licencia

Proyecto educativo. Minecraft © Mojang/Microsoft.
