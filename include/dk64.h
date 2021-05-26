//functions
extern void dma_copy(int romStart, int romEnd, int* ramStart); //0x80000450
extern void setFlag (int flagIndex, int value, char unk); //0x8073129C
extern int checkFlag (int flagIndex, char unk); //0x8073110C returns true/false of specified flag
extern void printText (int* hud, int xPos, int yPos, float scale, char* string); //806ABB98
extern void* malloc (int size); //0x80610FE8 returns ptr to free space (returns NULL if heap is full)
extern void free (void* mallocPtr);
extern void setHUDPointer (int* hud); //0x806A921C
extern void dk_strncpy (char* destination, char* source, int size); //0x80003000 (start of C file [this function is the entire C file...lol])
extern void printKroolTimer (char* destination, char* source, ...); //0x800031E0
extern int spawnActor (int actorID, int actorBehavior); //0x80677FA8
extern int dk_strlen (char* string); //0x80002F18
extern void SpawnTextOverlay (int style, int x, int y, char* string, int timer1, int timer2, unsigned char effect, unsigned char speed); //0x8069D0F8 a0 = style, a1 = x (s16), a2 = y (s16), a3 = textpointer
extern TextOverlay* setActorOpacity (char opacity, TextOverlay* actor); //custom function, returns last object created pointer
extern TextOverlay* SpawnTextOverlayWrapper(int style, int x, int y, char* string, int timer1, int timer2, unsigned char effect, unsigned char speed); //custom function, returns created text object
extern void deleteActor (TextOverlay* actor); //0x806785D4
extern void initializeTransition(int area, int entrance); //args are a guess
extern void dk_sprintf(char* destination, char* source, ...);
extern void setInitialPrintingAddr(); //custom
extern void getLinePointers(); //custom
extern void setOverlayColor(TextOverlay* textOverlay, char red, char green, char blue);
//extern void printTextCutscene (int style, char* string); //0x806FBD5C

extern int warpMain(void);
extern void ramViewMain(void);


//data
extern TextOverlay* latestObject; //0x807FBB44
extern short g_AmmoCount; //0x807FCC40
extern short p1PressedButtons; //0x807ECD48
extern short p1HeldButtons; //0x807ECD58
extern int* textObjectInstancesPrevious[24]; //0x807FFF00
extern TextOverlay* textObjectInstancesCurrent[24]; //0x807FFF80
extern int* graphicalOverlaySpace[32][3]; //0x807FFD80
extern char warpsSubMenu; //0x807FFD6E
extern char currentMenu; //0x807FFD6F
extern char inputTimer; //0x807FFD70
extern char mainMenuBoolean; //0x807FFD71
extern char mainCursorIndex; //0x807FFD72
extern char menuFlag; //0x807FFD73
extern int* printStartAddr; //custom
extern unsigned char headerStyle; //custom
extern unsigned char tableStyle; //custom
extern unsigned char currentFormat; //custom