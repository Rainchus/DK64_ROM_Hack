.n64 // Let armips know we're coding for the N64 architecture
.open "rom/base-u.z64", "rom/DK64-U-Mod.z64", 0 // Open the ROM file
.include "asm/boot.asm" //include modified boot code
.include "asm/symbols.asm" // Include dk64.asm to tell armips' linker where to find the game's function(s)
//.headersize 0x7E8122F0 // Set the displacement between ROM and RAM addresses
//.org 0x802CB1C0 // Set the origin to the RAM address of the useless debug function
//.org 0x1FED020
//.area 0x12FE0, 0 // Define an area the size of the useless function to ensure we can't overwrite anything else
//.area 0xCF0, 0 // Define an area the size of the useless function to ensure we can't overwrite anything else
.importobj "main.o" // Import and link the compiled C object, overwriting the useless function with our new code
//.endarea
.close // Close the ROM file