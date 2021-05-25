.org 0x113F0
.incbin "bin/0113F0_CompressedModZLib.bin" //sets heap end to 0x805D0000, normally is 0x805F0000

.definelabel bootStart, 0x01FED020

.headersize 0x7FFFF400
.org 0x80000764
LUI a0, 0x01FE //start of ROM copy
ORI a1, a0, ( (END - START) + bootStart & 0xFFFF)
ORI a0, a0, 0xD020
LUI a2, 0x807F
JAL dmaCopy
ORI a2, a2, 0xF310 //RAM location to copy to
J displacedBootCode
NOP
////////

.headersize 0x7E8122F0
.org 0x807FF310
START:
displacedBootCode: //ballam hook
LUI v0, 0x8001
ADDIU v0, v0, 0xDCC4
//set story skip to always be on
ORI t3, r0, 0x0001
LUI t4, 0x8074
SB t3, 0x452C (t4) //set story skip to 1
//write per frame hook
//
LUI t3, hi(mainASMFunctionVanilla)
LW t3, lo(mainASMFunctionVanilla) (t3)
LUI t4, 0x8060
SW t3, 0xC164 (t4) //remove per frame hook
JAL patchGraphicOverlaySpace
NOP
LUI t0, hi(printStartAddr)
LUI t1, 0x8000
SW t1, lo(printStartAddr) (t0) //set starting printing address to 0x80000000
LUI t0, hi(menuFlag)
SW r0, lo(menuFlag) (t0)
LUI t0, hi(skipFirstCutsceneRegardlessOfStorySkip)
LW t0, lo(skipFirstCutsceneRegardlessOfStorySkip) (t0)
LUI t1, 0x8071
SW t0, 0x4520 (t1) //always skip first cutscene no matter what
LUI t0, hi(currentFormat)
SB r0, lo(currentFormat) (t0) //set to 0 so menu works (default is FF)
//JAL 0x80712EDC //set game mode to file select?
//NOP
//807124E8 LW	A0, 0x0018 (SP)
//

LUI t0, hi(skipRapAndPreview)
ADDIU t0, t0, lo(skipRapAndPreview)
LUI t1, 0x8071
ORI t1, t1, 0x24E8
LW t2, 0x0000 (t0)
SW t2, 0x0000 (t1)
LW t2, 0x0004 (t0)
SW t2, 0x0008 (t1) //skip rap and preview on boot
//
LUI t0, hi(menuCodeDMAJump)
ADDIU t0, t0, lo(menuCodeDMAJump)
LUI t1, 0x8071
ORI t1, t1, 0x2AC8
LW t2, 0x0000 (t0)
SW t2, 0x0000 (t1)
LW t2, 0x0004 (t0)
SW t2, 0x0004 (t1)

/*
LUI a0, hi(bootStart + (END - START) )
ADDIU a1, a0, lo(bootStart + (END - START) + 0x10)
ADDIU a0, a0, lo(bootStart + (END - START) )
LUI a2, 0x805D //0x805DAE00
ORI a2, a2, 0xAE00
JAL dmaCopy
NOP
*/
//
LUI t0, hi(menuFlagOffOnRoomTransition)
ADDIU t0, t0, lo(menuFlagOffOnRoomTransition)
LW t1, 0x0000 (t0)
LW t2, 0x0004 (t0)
LUI t0, 0x8060 //805FF4A0
SW t1, 0xF4A0 (t0)
SW t2, 0xF4D4 (t0)
LUI t3, 0x0000
LUI t4, 0x0001
LUI t5, 0x0001
LUI t9, 0x000D
LUI t8, 0x000D
J 0x80000784
LUI t6, 0x000D
//end of boot code
/////////////////////////////////////////////////////

menuFlagOffOnRoomTransition:
LUI gp, hi(menuFlag)
SW r0, lo(menuFlag) (gp)

skipFirstCutsceneRegardlessOfStorySkip:
ORI t6, r0, 0x0001


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
nullPtr3:
JR RA
NOP

skipRapAndPreview:
ORI a0, r0, 0x0050
ORI a2, r0, 0x0005

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

setOverlayColor: //a0 = overlay, a1 = red, a2 = green, a3 = blue
BEQZ a0, setOverlayColorExit
NOP
SB a1, 0x016A (a0)
SB a2, 0x016B (a0)
SB a3, 0x016C (a0)
setOverlayColorExit:
JR RA
NOP

mainASMFunctionJump:
J mainASMFunction //instruction copied and used as a hook
NOP

mainASMFunctionVanilla:
JAL	0x805FC2B0
NOP

menuCodeDMAJump:
J menuCodeDMA
NOP

menuCodeDMA:
//80712AC8
ORI at, r0, 0006
BEQ at, t7, dmaCustomCode
NOP
menuCodeExit:
LUI	AT, 0x8075
SB	R0, 0x5324 (AT)
J 0x80712AD0
NOP
dmaCustomCode:
LUI a0, hi(bootStart + (END - START) )
ADDIU a1, a0, lo(bootStart + (END - START) + 0x2000)
ADDIU a0, a0, lo(bootStart + (END - START) )
LUI a2, 0x805D //0x805DAE00
ORI a2, a2, 0xAE00
JAL dmaCopy
NOP
LUI t3, hi(mainASMFunctionJump)
ADDIU t3, t3, lo(mainASMFunctionJump)
LW t3, 0x0000 (t3)
LUI t4, 0x8060
SW t3, 0xC164 (t4) //store per frame hook
J menuCodeExit
NOP
.align 0x10
END: