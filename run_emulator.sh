#!/bin/bash

# Minecraft PSP Port - Run in PPSSPP Emulator

if [ -z "$1" ]; then
    echo "Usage: $0 <EBOOT.PBP path>"
    echo "Example: $0 build/EBOOT.PBP"
    exit 1
fi

EBOOT_PATH="$1"

if [ ! -f "$EBOOT_PATH" ]; then
    echo "Error: File not found: $EBOOT_PATH"
    exit 1
fi

echo "Looking for PPSSPP..."

# Try to find PPSSPP
if command -v ppsspp &> /dev/null; then
    echo "Found PPSSPP, launching..."
    ppsspp "$EBOOT_PATH"
elif command -v PPSSPPWindows &> /dev/null; then
    PPSSPPWindows "$EBOOT_PATH"
elif [ -d "$HOME/PPSSPP" ]; then
    echo "Launching PPSSPP from home directory..."
    $HOME/PPSSPP/PPSSPP "$EBOOT_PATH"
else
    echo "PPSSPP not found. Download from: https://www.ppsspp.org/"
    echo ""
    echo "Setup instructions:"
    echo "1. Create game folder: PPSSPP/memstick/PSP/GAME/MINECRAFT/"
    echo "2. Copy EBOOT.PBP to that folder"
    echo "3. Launch PPSSPP and select Minecraft from games list"
    exit 1
fi
