mips64-elf-gcc -Wall -O1 -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -G0 -c src/main.c
armips asm/main.asm
n64crc "rom/DK64-U-Mod.z64"