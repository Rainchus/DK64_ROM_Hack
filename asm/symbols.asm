// Tell armips' linker where the assets we declared in dk64.h are located

//functions
.definelabel dmaCopy, 0x80000450
.definelabel setFlag, 0x8073129C
.definelabel checkFlag, 0x8073110C
.definelabel printText, 0x806ABB98
.definelabel malloc, 0x80610FE8
.definelabel free, 0x80611408
.definelabel setHUDPointer, 0x806A921C
.definelabel dk_strncpy, 0x80003000
.definelabel printKroolTimer, 0x800031E0
.definelabel spawnActor, 0x80677FA8
.definelabel dk_strlen, 0x80002F18
.definelabel dk_sprintf, 0x800031E0
.definelabel SpawnTextOverlay, 0x8069D0F8 // a0 = style?, a1 = x (s16), a2 = y (s16), a3 = textpointer
.definelabel deleteActor, 0x806785D4
//.definelabel printTextCutscene, 0x806FBD5C
//8002FE50 increment current menu selection on main menu, 8049210F is ram addr of current menu
//step loop file menu? 80030340


//data
.definelabel g_AmmoCount, 0x807FCC40
.definelabel latestObject, 0x807FBB44
.definelabel p1PressedButtons, 0x807ECD48
.definelabel p1HeldButtons, 0x807ECD58
.definelabel menuFlag, 0x807FFD70
.definelabel printStartAddr, 0x807FFD74
.definelabel headerStyle, 0x807FFD78
.definelabel tableStyle, 0x807FFD79
.definelabel currentFormat, 0x807FFD7A
.definelabel graphicalOverlaySpace, 0x807FFD80
.definelabel textObjectInstancesPrevious, 0x807FFF00
.definelabel textObjectInstancesCurrent, 0x807FFF80
