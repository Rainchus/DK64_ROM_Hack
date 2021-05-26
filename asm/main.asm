.n64 // Let armips know we're coding for the N64 architecture
.open "rom/base-u.z64", "rom/DK64-U-Mod.z64", 0 // Open the ROM file
.include "asm/symbols.asm" // Include dk64.asm to tell armips' linker where to find the game's function(s)
.include "asm/boot.asm" //include modified boot code
.headersize ( 0x805DAE00 - ( (END - START) + bootStart) )
.org 0x805DAE00
.importobj "main.o" // Import and link the compiled C object
.importobj "warp.o" // Import and link the compiled C object
.importobj "ramview.o"
//.endarea
.close // Close the ROM file