.headersize 0x7FFFF400
.org 0x80000764
LUI a0, 0x01FE //start of ROM copy
ORI a1, a0, 0xD060
ORI a0, 0xD020
LUI a2, 0x807F
JAL dmaCopy
ORI a2, a2, 0xF310 //RAM location to copy to
J displacedBootCode
NOP

.headersize 0x7E8122F0
.org 0x807FF310
displacedBootCode:
LUI v0, 0x8001
ADDIU v0, v0, 0xDCC4
//set story skip to always be on
ORI t3, r0, 0x0001
LUI t4, 0x8074
SB t3, 0x452C (t4) //set story skip to 1
LUI t3, 0x0000
LUI t4, 0x0001
LUI t5, 0x0001
LUI t9, 0x000D
LUI t8, 0x000D
J 0x80000784
LUI t6, 0x000D