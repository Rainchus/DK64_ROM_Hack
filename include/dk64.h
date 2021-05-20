//functions
extern void dma_copy(int romStart, int romEnd, int* ramStart); //0x80000450
extern void setFlag (int flagIndex, int value, char unk); //0x8073129C
extern int checkFlag (int flagIndex, char unk); //0x8073110C returns true/false of specified flag
extern void printText (int* hud, int xPos, int yPos, float scale, char* string); //806ABB98
extern int* malloc (int size); //0x80610FE8 returns ptr to free space (returns NULL if heap is full)
extern void setHUDPointer (int* hud); //0x806A921C
extern void dk_strncpy (char* destination, char* source, int size); //0x80003000 (start of C file [this function is the entire C file...lol])
extern void printKroolTimer (char* destination, char* source, ...); //0x800031E0
extern int spawnActor (int actorID, int actorBehavior); //0x80677FA8
extern int dk_strlen (char* string); //0x80002F18
extern void SpawnTextOverlay (int z, int x, int y, char* string); //0x8069D0F8 a0 = z?, a1 = x (s16), a2 = y (s16), a3 = textpointer
extern void setCurrentActorOpacity (char opacity); //custom function
extern void Watch_ColourWatch (int color); //custom function
//extern void printTextCutscene (int style, char* string); //0x806FBD5C


//data
extern short g_AmmoCount; //0x807FCC40
extern short p1PressedButtons; //0x807ECD48
extern short p1HeldButtons; //0x807ECD58
extern int* tempPtr; //0x807FFFF8
extern char initFlag; //0x807FFFFF