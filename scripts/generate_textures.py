#!/usr/bin/env python3
"""
Generate optimized textures for Minecraft PSP Port
Creates 8-bit CLUT textures for PSP GPU
"""

import os
import struct
from PIL import Image, ImageDraw

TEXTURE_SIZE = 16
PALETTE_SIZE = 256

# Block types and their colors (RGB)
BLOCK_COLORS = {
    0: (0, 0, 0),          # Air (transparent)
    1: (64, 64, 64),       # Bedrock
    2: (139, 108, 71),     # Dirt
    3: (128, 128, 128),    # Stone
    4: (34, 139, 34),      # Grass top
    5: (33, 102, 204),     # Water
    6: (210, 180, 140),    # Sand
    7: (139, 90, 43),      # Wood
    8: (34, 139, 34),      # Leaves
    9: (205, 92, 92),      # Dirt grass side
}

def create_texture_block(block_type, shade=1.0):
    """
    Create a 16x16 texture block with variations
    shade: 0.0-2.0 for light/dark variations
    """
    if block_type not in BLOCK_COLORS:
        block_type = 0
    
    r, g, b = BLOCK_COLORS[block_type]
    
    # Apply shade
    r = max(0, min(255, int(r * shade)))
    g = max(0, min(255, int(g * shade)))
    b = max(0, min(255, int(b * shade)))
    
    # Create image
    img = Image.new('RGB', (TEXTURE_SIZE, TEXTURE_SIZE), (r, g, b))
    draw = ImageDraw.Draw(img)
    
    # Add noise pattern for detail
    import random
    for i in range(TEXTURE_SIZE * TEXTURE_SIZE // 4):
        x = random.randint(0, TEXTURE_SIZE - 1)
        y = random.randint(0, TEXTURE_SIZE - 1)
        intensity = random.randint(-20, 20)
        
        pixel_r = max(0, min(255, r + intensity))
        pixel_g = max(0, min(255, g + intensity))
        pixel_b = max(0, min(255, b + intensity))
        
        img.putpixel((x, y), (pixel_r, pixel_g, pixel_b))
    
    # Add borders for block definition
    if block_type != 0:
        draw.rectangle([(0, 0), (TEXTURE_SIZE - 1, TEXTURE_SIZE - 1)], outline=(0, 0, 0))
    
    return img

def create_texture_atlas():
    """
    Create a texture atlas with all block types
    Organized as a spritesheet: 16 blocks per row
    """
    blocks_per_row = 16
    num_blocks = len(BLOCK_COLORS)
    rows = (num_blocks + blocks_per_row - 1) // blocks_per_row
    
    atlas_width = blocks_per_row * TEXTURE_SIZE
    atlas_height = rows * TEXTURE_SIZE
    
    atlas = Image.new('RGB', (atlas_width, atlas_height), (0, 0, 0))
    
    for block_id, (r, g, b) in BLOCK_COLORS.items():
        x = (block_id % blocks_per_row) * TEXTURE_SIZE
        y = (block_id // blocks_per_row) * TEXTURE_SIZE
        
        texture = create_texture_block(block_id)
        atlas.paste(texture, (x, y))
    
    return atlas

def create_palette():
    """
    Create an 8-bit color palette (256 colors)
    Optimized for PSP CLUT format
    """
    palette = []
    
    # Create a gradient palette
    for i in range(PALETTE_SIZE):
        # Simple grayscale with some color variance
        base = i
        r = base
        g = base
        b = base
        palette.append((r, g, b, 255))  # RGBA
    
    return palette

def quantize_to_8bit(img):
    """
    Quantize image to 8-bit indexed color
    """
    return img.convert('P', palette=Image.ADAPTIVE, colors=256)

def save_texture_atlas(atlas, output_path):
    """
    Save texture atlas as PNG
    """
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    atlas.save(output_path, 'PNG')
    print(f"Texture atlas saved: {output_path}")

def generate_all_textures():
    """
    Generate all textures for the game
    """
    print("Generating Minecraft PSP textures...")
    
    # Create atlas
    atlas = create_texture_atlas()
    
    # Quantize to 8-bit
    atlas_8bit = quantize_to_8bit(atlas)
    
    # Save
    output_dir = 'assets/textures'
    save_texture_atlas(atlas, f'{output_dir}/atlas.png')
    save_texture_atlas(atlas_8bit, f'{output_dir}/atlas_8bit.png')
    
    print(f"Created {len(BLOCK_COLORS)} block textures")
    print(f"Atlas size: {atlas.size}")
    print("Texture generation complete!")

if __name__ == '__main__':
    generate_all_textures()
