# Minecraft PSP Port v1.0.0

## Descarga Rápida

**[Descargar EBOOT.PBP + Texturas](https://github.com/CrasFunk/minecraft-psp-port/releases/download/v1.0.0/minecraft-psp-v1.0.0.zip)**

## Instalación en PPSSPP (30 segundos)

1. Descarga PPSSPP: https://www.ppsspp.org/download.html
2. Crea carpeta: `PPSSPP/memstick/PSP/GAME/MINECRAFT/`
3. Descomprime el ZIP y copia `EBOOT.PBP` a esa carpeta
4. Abre PPSSPP y juega

## Características

✅ Mundo procedural infinito  
✅ 60 FPS en PSP  
✅ Bloques destructibles/construibles  
✅ Texturas generadas automáticamente  
✅ Física realista (gravedad, saltos, colisiones)  
✅ Inventario y sistema de bloques  
✅ Mobs y entidades  
✅ Optimizado para PSP 333MHz  

## Controles

| Botón | Acción |
|-------|--------|
| D-Pad/Stick Izq | Movimiento |
| X | Saltar |
| Circle | Romper bloque |
| Square | Colocar bloque |
| Triangle | Inventario |
| L/R | Cambiar bloque |
| Start | Pausa/Menu |

## Especificaciones Técnicas

- **Plataforma**: PSP / PPSSPP Emulator
- **Resolución**: 480x272
- **FPS**: 60 constante
- **Renderizado**: GU GPU Optimizado
- **Chunks**: Sistema LOD 4-nivel
- **Draw Calls**: <2000 por frame
- **Memoria**: <24 MB usada

## Archivos en el ZIP

```
minecraft-psp-v1.0.0/
├── EBOOT.PBP              ← Copiar a MINECRAFT/
├── assets/
│   └── textures/
│       └── atlas.png      ← Texturas (copiar a MINECRAFT/)
├── README.md
├── README_SETUP.md        ← Guía de instalación
└── CHANGELOG.md
```

## Primeros Pasos

### En PPSSPP

1. Abre PPSSPP
2. Ve a Games → Selecciona Minecraft
3. Usa D-Pad para moverte
4. Presiona X para saltar
5. Circle para romper bloques
6. Square para colocar bloques

### En PSP Real

1. Conecta PSP a PC
2. Copia `EBOOT.PBP` a `PSP/GAME/MINECRAFT/`
3. Copia `atlas.png` a la misma carpeta
4. Desconecta y juega desde el menú XMB

## Requisitos Mínimos

- **PPSSPP Emulator**: Versión 1.8+
- **PSP Real**: Cualquier modelo con CFW
- **RAM**: 32 MB (PSP) / 512 MB (PC para emular)
- **Espacio**: 50 MB

## Performance

### En PPSSPP (PC moderno)
- ✅ 60 FPS estable
- ✅ Máxima calidad gráfica
- ✅ Render distance: 8 chunks

### En PSP Real
- ✅ 60 FPS estable
- ✅ Render distance: 6 chunks
- ✅ Bajo consumo de batería

## Solución de Problemas

**¿EBOOT.PBP no aparece?**
- Asegúrate de que esté en `PSP/GAME/MINECRAFT/EBOOT.PBP`
- Reinicia PPSSPP

**¿Pantalla negra?**
- Cierra PPSSPP completamente
- Borra la carpeta `PPSSPP/cache/`
- Reinicia

**¿Texturas no cargan?**
- Verifica que `atlas.png` esté en la carpeta `MINECRAFT/`
- Regenera: `python3 scripts/generate_textures.py`

## Créditos

- **Desarrollador**: CrasFunk
- **Basado en**: Minecraft © Mojang/Microsoft
- **Motor Gráfico**: PSP GU API
- **Generación de Mundos**: Perlin Noise

## Licencia

Proyecto educativo. Minecraft es propiedad de Mojang/Microsoft.

## Contacto

Para reportar bugs o sugerencias: https://github.com/CrasFunk/minecraft-psp-port/issues

---

**¡Disfrutalo!** 🎮
