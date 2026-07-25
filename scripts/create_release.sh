#!/bin/bash

# Minecraft PSP Port - Create Release Package
# Prepares files for GitHub Release

echo "=== Minecraft PSP Port - Release Builder ==="
echo ""

VERSION="1.0.0"
RELEASE_DIR="minecraft-psp-v${VERSION}"
ZIP_NAME="minecraft-psp-v${VERSION}.zip"

echo "[1/4] Creating release directory..."
mkdir -p "$RELEASE_DIR"
mkdir -p "$RELEASE_DIR/assets/textures"

echo "[2/4] Copying files..."

# Copy main files
cp build/EBOOT.PBP "$RELEASE_DIR/" 2>/dev/null || echo "Warning: EBOOT.PBP not found"
cp assets/textures/atlas.png "$RELEASE_DIR/assets/textures/" 2>/dev/null || echo "Warning: atlas.png not found"
cp README.md "$RELEASE_DIR/"
cp README_SETUP.md "$RELEASE_DIR/"
cp RELEASE_NOTES.md "$RELEASE_DIR/"
cp CHANGELOG.md "$RELEASE_DIR/"

echo "[3/4] Creating ZIP..."
zip -r "$ZIP_NAME" "$RELEASE_DIR"

echo "[4/4] Cleaning up..."
rm -rf "$RELEASE_DIR"

echo ""
echo "✓ Release package created: $ZIP_NAME"
echo "Size: $(du -h $ZIP_NAME | cut -f1)"
echo ""
echo "Next steps:"
echo "1. Go to: https://github.com/CrasFunk/minecraft-psp-port/releases/new"
echo "2. Tag version: v${VERSION}"
echo "3. Title: Minecraft PSP Port v${VERSION}"
echo "4. Upload: $ZIP_NAME"
echo "5. Publish Release"
echo ""
