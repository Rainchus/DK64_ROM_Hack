// Tell armips' linker where the assets we declared in dk64.h are located

//functions
.definelabel dmaCopy, 0x80000450
.definelabel setFlag, 0x8073129C
.definelabel checkFlag, 0x8073110C
.definelabel printText, 0x806ABB98
.definelabel malloc, 0x80610FE8
.definelabel setHUDPointer, 0x806A921C
.definelabel dk_strncpy, 0x80003000
.definelabel printKroolTimer, 0x800031E0
.definelabel spawnActor, 0x80677FA8
.definelabel dk_strlen, 0x80002F18
.definelabel SpawnTextOverlay, 0x8069D0F8 // a0 = z?, a1 = x (s16), a2 = y (s16), a3 = textpointer
//.definelabel printTextCutscene, 0x806FBD5C


//data
.definelabel g_AmmoCount, 0x807FCC40
.definelabel p1PressedButtons, 0x807ECD48
.definelabel p1HeldButtons, 0x807ECD58
.definelabel tempPtr, 0x807FFFF8
.definelabel initFlag, 0x807FFFFF