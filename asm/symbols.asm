// Tell armips' linker where the assets we declared in dk64.h are located

//functions
.definelabel dmaCopy, 0x80000450
.definelabel setFlag, 0x8073129C
.definelabel checkFlag, 0x8073110C
.definelabel printText, 0x806ABB98
.definelabel malloc, 0x80610FE8
.definelabel setHUDPointer, 0x806A921C
.definelabel dk_strncpy, 0x80003000


//data
.definelabel g_AmmoCount, 0x807FCC40