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
JAL patchGraphicOverlaySpace
NOP
LUI t0, hi(printStartAddr)
LUI t1, 0x8000
SW t1, lo(printStartAddr) (t0) //set starting printing address to 0x80000000
LUI t0, hi(menuFlag)
SW r0, lo(menuFlag) (t0)
//JAL clearGraphicOverlayPointers
//NOP
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

setActorOpacity: //a0 = opacity, a1 = actor
BEQZ a1, nullPtr3
NOP
SB a0, 0x15F (a1) //set opacity
ADDIU a0, r0, 0xFFFF
SB a0, 0x155 (a1) //set timer state to stopped
ORI a0, r0, 0x0001
SB a0, 0x154 (a1) //set text to display
nullPtr3:
JR RA
NOP

patchGraphicOverlaySpace:
LUI t0, hi(graphicOverlayInstructionsPatch1)
ADDIU t0, t0, lo(graphicOverlayInstructionsPatch1)
LW t1, 0x0000 (t0)
LW t2, 0x0004 (t0)
LUI t3, 0x8069
SW t1, 0xC374 (t3)
SW t2, 0xC378 (t3)
//
LUI t0, hi(graphicOverlayInstructionsPatch2)
ADDIU t0, t0, lo(graphicOverlayInstructionsPatch2)
LW t1, 0x0000 (t0)
LW t2, 0x0004 (t0)
SW t1, 0xC310 (t3)
SW t2, 0xC314 (t3)
//
LUI t0, hi(graphicOverlayInstructionsPatch3)
ADDIU t0, t0, lo(graphicOverlayInstructionsPatch3)
LW t1, 0x0000 (t0)
LW t2, 0x0004 (t0)
SW t1, 0xC240 (t3)
SW t2, 0xC244 (t3)

LUI t0, hi(graphicOverlayInstructionsPatch4)
ADDIU t0, t0, lo(graphicOverlayInstructionsPatch4)
LW t1, 0x0000 (t0)
JR RA
SW t1, 0xC364 (t3)


graphicOverlayInstructionsPatch1:
LUI t8, hi(graphicalOverlaySpace)
ADDIU t8, t8, lo(graphicalOverlaySpace)

graphicOverlayInstructionsPatch2:
LUI a2, hi(graphicalOverlaySpace)
ADDIU a2, a2, lo(graphicalOverlaySpace)

graphicOverlayInstructionsPatch3:
LUI s2, hi(graphicalOverlaySpace)
ADDIU s2, s2, lo(graphicalOverlaySpace)

graphicOverlayInstructionsPatch4:
SLTI at, v0, 32

clearGraphicOverlayPointers:
LUI t0, hi(graphicalOverlaySpace)
ADDIU t0, t0, lo(graphicalOverlaySpace)
ORI v0, r0, 0x0000 //for loop count
graphicOverlayLoop:
SLTI v1, v0, 32
BEQZ v1, exitGraphicLoop
NOP
SW r0, 0x0000 (t0)
SW r0, 0x0004 (t0)
SW r0, 0x0008 (t0)
ADDIU t0, t0, 0x000C
ADDIU v0, v0, 0x0001
BEQ r0, r0, graphicOverlayLoop
NOP
exitGraphicLoop:
JR RA
NOP

mainASMFunctionJump:
J mainASMFunction


//mainCFunc at 807FF648 currently


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