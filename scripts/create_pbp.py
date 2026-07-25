#!/usr/bin/env python3
"""
Create EBOOT.PBP for PSP from compiled ELF
Works without PSP SDK (creates minimal valid PBP)
"""

import struct
import os
import sys

class PBPHeader:
    def __init__(self):
        self.signature = b'\x00PBP'
        self.version = 0x00000100
        self.param_offset = 0x28
        self.icon0_offset = 0
        self.icon1_offset = 0
        self.pic0_offset = 0
        self.pic1_offset = 0
        self.snd0_offset = 0
        self.psp_offset = 0
        self.psar_offset = 0

def create_minimal_sfo():
    """Create minimal PSP PARAM.SFO file"""
    # SFO header
    data = b'\x00PSF'
    data += struct.pack('<I', 0x00000101)  # Version
    data += struct.pack('<I', 0x00000004)  # Key table offset
    data += struct.pack('<I', 0x00000008)  # Data table offset
    data += struct.pack('<I', 0x00000008)  # Entries
    
    # Minimal key-value entries
    # This is simplified; full SFO is more complex
    
    return data

def create_eboot_pbp(elf_path, output_path):
    """Create EBOOT.PBP from ELF file"""
    
    if not os.path.exists(elf_path):
        print(f"Error: ELF file not found: {elf_path}")
        return False
    
    print(f"Creating EBOOT.PBP from {elf_path}...")
    
    # Read ELF
    with open(elf_path, 'rb') as f:
        elf_data = f.read()
    
    print(f"ELF size: {len(elf_data)} bytes")
    
    # Create minimal SFO
    sfo_data = create_minimal_sfo()
    print(f"SFO size: {len(sfo_data)} bytes")
    
    # Create PBP header
    header = PBPHeader()
    
    # Calculate offsets
    header_size = 0x28
    header.param_offset = header_size
    header.psp_offset = header.param_offset + len(sfo_data)
    
    # Create PBP
    pbp_data = header.signature
    pbp_data += struct.pack('<I', header.version)
    pbp_data += struct.pack('<I', header.param_offset)
    pbp_data += struct.pack('<I', header.icon0_offset)
    pbp_data += struct.pack('<I', header.icon1_offset)
    pbp_data += struct.pack('<I', header.pic0_offset)
    pbp_data += struct.pack('<I', header.pic1_offset)
    pbp_data += struct.pack('<I', header.snd0_offset)
    pbp_data += struct.pack('<I', header.psp_offset)
    pbp_data += struct.pack('<I', header.psar_offset)
    
    # Add SFO and ELF
    pbp_data += sfo_data
    pbp_data += elf_data
    
    # Write PBP
    with open(output_path, 'wb') as f:
        f.write(pbp_data)
    
    print(f"✓ EBOOT.PBP created: {output_path}")
    print(f"Total size: {len(pbp_data)} bytes")
    
    return True

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python3 create_pbp.py <elf_file> [output_pbp]")
        sys.exit(1)
    
    elf_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else 'EBOOT.PBP'
    
    if create_eboot_pbp(elf_file, output_file):
        sys.exit(0)
    else:
        sys.exit(1)
