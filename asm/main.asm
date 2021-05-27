.n64 // Let armips know we're coding for the N64 architecture
.open "rom/base-u.z64", "rom/DK64-U-Mod.z64", 0 // Open the ROM file
.include "asm/shrinkFB.asm"
.include "asm/symbols.asm" // Include dk64.asm to tell armips' linker where to find the game's function(s)
.include "asm/bootPatch.asm" //patch boot routine to DMA our code from ROM
.headersize 0x7E5EDDE0
.org 0x805DAE00
.include "asm/boot.asm" //include modified boot code
.importobj "obj/global.o"
.importobj "obj/main.o" // Import and link the compiled C object
.importobj "obj/warp.o" // Import and link the compiled C object
.importobj "obj/ramview.o"
.importobj "obj/practice.o"
//.endarea
.close // Close the ROM file