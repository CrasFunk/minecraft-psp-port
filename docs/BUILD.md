# Build Instructions - Minecraft PSP Port

## Prerequisites

### Linux/macOS

1. Install PSP SDK:
```bash
# Using prebuilt (recommended)
wget https://github.com/pspdev/pspsdk/releases/download/latest/pspsdk.tar.gz
tar xzf pspsdk.tar.gz
export PSPDEV=/path/to/pspsdk
export PATH=$PSPDEV/bin:$PATH
```

2. Install dependencies:
```bash
# Ubuntu/Debian
sudo apt-get install build-essential python3 python3-pip
pip3 install Pillow

# macOS
brew install python@3
pip3 install Pillow
```

### Windows

1. Download PSP SDK for Windows from official repository
2. Install Python 3.8+
3. Install PIL: `pip install Pillow`

## Build Steps

### Step 1: Generate Assets

```bash
python3 scripts/generate_textures.py
```

This creates optimized 8-bit CLUT textures in `assets/textures/`.

### Step 2: Compile

```bash
make -C build clean
make -C build
```

This produces `build/minecraft.elf`.

### Step 3: Create EBOOT.PBP

```bash
make -C build eboot
```

This creates PSP executable format.

## Running in PPSSPP

1. Download PPSSPP emulator
2. Create game folder: `PPSSPP/memstick/PSP/GAME/MINECRAFT/`
3. Copy EBOOT.PBP to that folder
4. Launch from PPSSPP

## Running on PSP

1. Mount PSP via USB
2. Copy EBOOT.PBP to `PSP/GAME/MINECRAFT/`
3. Eject and run from PSP menu

## Debugging

### PPSSPP Debugging

1. Enable debugger in PPSSPP settings
2. Use GDB for breakpoints:
```bash
psp-gdb build/minecraft.elf
```

### Console Output

```bash
# View debug output
pspDebugScreenPrintf("Debug: %d\n", value);
```

## Performance Profiling

### Using PPSSPP Profiler

1. Enable "Show Profile" in PPSSPP
2. View frame times and GPU usage

### Memory Analysis

```bash
# Check memory usage
sceKernelQueryMemoryInfo(&meminfo);
```

## Troubleshooting

### "Cannot find PSPDEV"
```bash
export PSPDEV=/path/to/pspsdk
export PATH=$PSPDEV/bin:$PATH
```

### Compilation Errors
```bash
make -C build clean
make -C build V=1  # Verbose output
```

### Runtime Crashes
1. Check for stack overflow: increase heap size in Makefile
2. Verify chunk generation logic
3. Check memory alignment (16-byte alignment required)
