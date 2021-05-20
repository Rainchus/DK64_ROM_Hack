.headersize 0x7FFFF400
.org 0x80000764
LUI a0, 0x01FE //start of ROM copy
ORI a1, a0, 0xDD10
ORI a0, 0xD020
LUI a2, 0x807F
JAL dmaCopy
ORI a2, a2, 0xF310 //RAM location to copy to
J displacedBootCode
NOP
////////
.headersize 0x7E8122F0
.org 0x807FF310
displacedBootCode: //ballam hook
LUI v0, 0x8001
ADDIU v0, v0, 0xDCC4
//set story skip to always be on
ORI t3, r0, 0x0001
LUI t4, 0x8074
SB t3, 0x452C (t4) //set story skip to 1
//write per frame hook
LUI t3, hi(mainASMFunctionJump)
ADDIU t3, t3, lo(mainASMFunctionJump)
LW t3, 0x0000 (t3)
LUI t4, 0x8060
SW t3, 0xC164 (t4) //store per frame hook
LUI t3, 0x0000
LUI t4, 0x0001
LUI t5, 0x0001
LUI t9, 0x000D
LUI t8, 0x000D
J 0x80000784
LUI t6, 0x000D
/////////////


mainASMFunction:
JAL	0x805FC2B0
NOP
JAL mainCFunc
NOP
J 0x805FC16C
NOP

setCurrentActorOpacity: //a0 = opacity
LUI v0, 0x8080
LW v0, 0xBB44 (v0) //load current actor
BEQZ v0, nullPtr
NOP
SB a0, 0x15F (v0)
nullPtr:
JR RA
NOP

Watch_ColourWatch:
	// a0 = Colour (u24)
    LUI a1, 0x8080
    LW a1, 0xBB44 (a1) //load current actor
    BEQZ a1, nullPtr2
    NOP
	// RGB = 0x16A > 0x16C
	ANDI 	a2, a0, 0xFF
	SB 		a2, 0x16C (a1)
	SRA 	a0, a0, 8
	ANDI 	a2, a0, 0xFF
	SB 		a2, 0x16B (a1)
	SRA 	a0, a0, 8
	ANDI 	a2, a0, 0xFF
	SB 		a2, 0x16A (a1)
    nullPtr2:
    JR RA
    NOP



mainASMFunctionJump:
J mainASMFunction


/* my hook
.headersize 0x7E8122F0
.org 0x807FF310
displacedBootCode:
LUI v0, 0x8001
ADDIU v0, v0, 0xDCC4
//set story skip to always be on
ORI t3, r0, 0x0001
LUI t4, 0x8074
SB t3, 0x452C (t4) //set story skip to 1
//write per frame hook
LUI t3, hi(mainASMFunctionJump)
ADDIU t3, t3, lo(mainASMFunctionJump)
LW t3, 0x0000 (t3)
LUI t4, 0x8060
SW t3, 0xE36C (t4) //store per frame hook in game loop
LUI t3, 0x0000
LUI t4, 0x0001
LUI t5, 0x0001
LUI t9, 0x000D
LUI t8, 0x000D
J 0x80000784
LUI t6, 0x000D



mainASMFunction:
JAL 0x80722280
NOP
JAL mainCFunc
NOP
J 0x805FE374
NOP



mainASMFunctionJump:
J mainASMFunction
*/