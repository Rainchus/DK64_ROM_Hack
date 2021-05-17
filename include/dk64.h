/*
Here we create declarations for a few functions and variables in DK64 so they can be referenced from our C code.
Later we will tell armips their addresses by defining labels for them in dk64.asm.
*/

//functions
extern void dma_copy(int romStart, int romEnd, int* ramStart); //0x80000450
extern void setFlag (int flagIndex, int value, char unk); //0x8073129C
extern int checkFlag (int flagIndex, char unk); //0x8073110C returns true/false of specified flag
extern void printText (int* hud, int xPos, int yPos, float scale, char* string); //806ABB98
extern int* malloc (int size); //0x80610FE8 returns ptr to free space (returns NULL if heap is full)
extern void setHUDPointer (int* hud); //0x806A921C
extern void dk_strncpy (char* destination, char* source, int size); //0x80003000 (start of C file [this function is the entire C file...lol])

//data
extern short g_AmmoCount; //0x807FCC40

//copied from sm64.h
/*
extern void PrintStr(int x, int y, const char* text); // 0x802D6554
extern short g_MarioCoins; // 0x8033B218
extern short g_MarioHealth; // 0x8033B21E
*/