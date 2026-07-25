# Minecraft PSP Port - Quick Setup Guide

## Para PPSSPP Emulator (Recomendado)

### Opción 1: Directa (Más fácil)

1. **Descargar PPSSPP**: https://www.ppsspp.org/download.html

2. **Crear carpeta del juego**:
   ```
   PPSSPP/memstick/PSP/GAME/MINECRAFT/
   ```

3. **Copiar EBOOT.PBP**:
   - Copiar `build/EBOOT.PBP` a la carpeta `MINECRAFT/`
   - Debe quedar así: `PPSSPP/memstick/PSP/GAME/MINECRAFT/EBOOT.PBP`

4. **Ejecutar PPSSPP**:
   - Abre PPSSPP
   - El juego aparecerá en la lista
   - Haz clic para jugar

### Opción 2: Línea de Comandos

```bash
# En Linux/macOS
./run_emulator.sh build/EBOOT.PBP

# O ejecutar directamente PPSSPP
ppsspp build/EBOOT.PBP
```

## Para PSP Real

1. **Conecta PSP a PC via USB** (con CFW instalado)

2. **Crea la carpeta** `PSP/GAME/MINECRAFT/`

3. **Copia los archivos**:
   - `EBOOT.PBP` → `PSP/GAME/MINECRAFT/EBOOT.PBP`
   - `assets/textures/atlas.png` → `PSP/GAME/MINECRAFT/`

4. **Desconecta y ejecuta** desde el menú XMB

## Controles

### PSP
- **D-Pad/Left Stick**: Movimiento
- **Cross (X)**: Saltar
- **Circle (O)**: Romper bloque
- **Square (□)**: Colocar bloque
- **Triangle (△)**: Abre inventario
- **L/R**: Cambiar bloque
- **Start**: Pausa
- **Select**: Menú

## Archivos Necesarios

- ✅ `EBOOT.PBP` - Ejecutable principal
- ✅ `atlas.png` - Texturas (generadas automáticamente)

## Solución de Problemas

### "EBOOT.PBP no funciona"
- Verifica que el archivo esté en la carpeta correcta
- Intenta regenerar: `python3 scripts/create_pbp.py build/minecraft.elf build/EBOOT.PBP`

### "Pantalla negra"
- Cierra PPSSPP completamente
- Borra caché de PPSSPP
- Intenta de nuevo

### "Texturas no cargan"
- Asegúrate de generar texturas: `python3 scripts/generate_textures.py`
- Verifica que `assets/textures/atlas.png` existe

## Compilación Completa (Opcional)

Si quieres compilar desde cero:

```bash
# 1. Instalar PSP SDK
# 2. Establecer PSPDEV
export PSPDEV=/path/to/pspsdk

# 3. Generar texturas
python3 scripts/generate_textures.py

# 4. Compilar
make -C build

# 5. Crear EBOOT.PBP
python3 scripts/create_pbp.py build/minecraft.elf build/EBOOT.PBP

# 6. Copiar a PPSSPP
cp build/EBOOT.PBP ~/PPSSPP/memstick/PSP/GAME/MINECRAFT/
```

## Sistema de Archivos PSP

```
PPSSPP/
├── memstick/
│   └── PSP/
│       └── GAME/
│           └── MINECRAFT/
│               ├── EBOOT.PBP        ← Copiar aquí
│               ├── assets/
│               │   └── textures/
│               │       └── atlas.png
│               └── save/             ← Datos guardados
```

## Performance Tips

- **PPSSPP Settings**:
  - Resolution: 1x (480x272) para mejor rendimiento
  - GPU Backend: OpenGL (más estable)
  - Enable: "Accurate Emulation"

- **PSP Real**:
  - Desactiva sonido si hay lag
  - Reduce render distance en opciones
  - Limpia memoria del PSP

## Descarga Rápida

**PPSSPP**: https://www.ppsspp.org/download.html

**EBOOT.PBP**: Generado automáticamente en `build/EBOOT.PBP`
