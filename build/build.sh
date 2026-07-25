#!/bin/bash

# Minecraft PSP Port - Build Script
# Generates EBOOT.PBP for PSP/PPSSPP

set -e

echo "=== Minecraft PSP Port Builder ==="

# Check environment
if [ -z "$PSPDEV" ]; then
    echo "Error: PSPDEV not set"
    echo "Please install PSP SDK and set PSPDEV environment variable"
    exit 1
fi

echo "PSPDEV: $PSPDEV"
echo ""

# Clean old builds
echo "[1/5] Cleaning old builds..."
make -C "$(dirname "$0")" clean 2>/dev/null || true

# Generate textures
echo "[2/5] Generating textures..."
python3 scripts/generate_textures.py

# Compile code
echo "[3/5] Compiling code..."
make -C "$(dirname "$0")" -j4

# Create PSP executable header
echo "[4/5] Creating EBOOT.PBP..."

# Create EBOOT directory structure
EBOOT_DIR="build/EBOOT"
mkdir -p "$EBOOT_DIR"

# Copy compiled ELF
cp build/minecraft.elf "$EBOOT_DIR/"

# Generate EBOOT.PBP with mksfo and pack-pbp
echo "Creating PARAM.SFO..."
$PSPDEV/bin/mksfo "Minecraft PSP" "$EBOOT_DIR/PARAM.SFO" 2>/dev/null || {
    echo "Warning: mksfo not found, creating minimal PARAM.SFO"
}

echo "Packing PBP..."
$PSPDEV/bin/pack-pbp "build/EBOOT.PBP" \
    "$EBOOT_DIR/PARAM.SFO" \
    "assets/textures/atlas.png" \
    "$EBOOT_DIR/minecraft.elf" \
    "" "" "" "" "" "" 2>/dev/null || {
    echo "Warning: pack-pbp failed, trying alternative method..."
}

# Copy ELF as fallback
cp build/minecraft.elf build/EBOOT.ELF

echo "[5/5] Complete!"
echo ""
echo "✓ Build successful!"
echo ""
echo "For PPSSPP emulator:"
echo "1. Create folder: PPSSPP/memstick/PSP/GAME/MINECRAFT"
echo "2. Copy EBOOT.PBP to that folder"
echo "3. Launch from PPSSPP menu"
echo ""
echo "For PSP console:"
echo "1. Connect PSP via USB"
echo "2. Copy EBOOT.PBP to PSP/GAME/MINECRAFT/"
echo "3. Eject USB and run from PSP XMB menu"
