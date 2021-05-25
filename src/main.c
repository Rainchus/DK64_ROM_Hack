#include "../include/common.h"

#define ByteFormat4 0
#define ByteFormat2 1
#define ByteFormat1 2

#define dpadUp 0x0800
#define dpadDown 0x0400
#define dpadLeft 0x0200
#define dpadRight 0x0100

#define validRamReadStart 0x80000000
#define validRamReadEnd 0x807FFF90

#define menuStateChangeStartAddr 00000000
#define menuStateSelectAddr 00000001 //for selecting a ram address to modify in the table
#define menuStatePokeAddr 00000002 //for changing a ram value

char formatter08[] = "%02X:%08X %08X %08X %08X";
char formatter04[] = "%02X:%04X %04X %04X %04X %04X %04X %04X %04X";
char formatter02[] = "%02X:%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X";
char formatterHeader[] = "ADDR: %08X";

char header[20];
char line1[0];
char line2[0];
char line3[0];
char line4[0];
char line5[0];
char line6[0];
char line7[0];
char line8[0];
char line9[0];
char* greenText;

char* lines[] = {header, line1, line2, line3, line4, line5, line6, line7, line8};

void setFlags() {
    setFlag(0x17A, 1, 0);
    setFlag(0x64, 1, 2);
    setFlag(0x309, 1, 0); //Cranky's Lab 1st time text
    setFlag(0x181, 0x01, 0); //open gate to main hub
    setFlag(0x186, 0x01, 0); //bird first time main hub go away pls
    
    setFlag(0x1B1, 0x01, 0); //set warp 1 in main hub under tag barrel
    setFlag(0x1B2, 0x01, 0); //set warp 1 in main hub by k lumsy (i think that's his name?)
    setFlag(0x1B3, 0x01, 0); //set warp 2 in main hub under tag barrel
    setFlag(0x1B4, 0x01, 0); //set warp 2 in main hub by aztec entrance
    setFlag(0x1B5, 0x01, 0); //set warp 3 in main hub under tag barrel
    setFlag(0x1B6, 0x01, 0); //set warp 3 in main hub fungi forest entrance
    setFlag(0x1B7, 0x01, 0); //set warp 4 in main hub under tag barrel
    setFlag(0x1B8, 0x01, 0); //set warp 4 in main hub frantic factory
    setFlag(0x1B9, 0x01, 0); //set warp 5 in main hub in fairy island
    setFlag(0x1BA, 0x01, 0); //set warp 5 in main hub under tag barrel
    setFlag(0x163, 0x01, 0);
}

TextOverlay* SpawnTextOverlayWrapper(int style, int x, int y, char* string, int timer1, int timer2, unsigned char effect, unsigned char speed) {
    SpawnTextOverlay(style, x, y, string, timer1, timer2, effect, speed);
    return latestObject;
}


void dk_sprintfWrapper (char* destination, int byteFormat, int* address) {
    if (byteFormat == ByteFormat4) {
        dk_sprintf(destination, formatter08, ((unsigned int)address & 0x000000FF), *(address), *(address + 1), *(address + 2), *(address + 3));
    } else if (byteFormat == ByteFormat2) {
        dk_sprintf(destination, formatter04, ((unsigned int)address & 0x000000FF), *((unsigned short*)address), *((unsigned short*)address + 1), *((unsigned short*)address + 2), *((unsigned short*)address + 3), *((unsigned short*)address + 4), *((unsigned short*)address + 5), *((unsigned short*)address + 6), *((unsigned short*)address + 7));
    } else if (byteFormat == ByteFormat1) {
        dk_sprintf(destination, formatter02, ((unsigned int)address & 0x000000FF), *((unsigned char*)address), *((unsigned char*)address + 1), *((unsigned char*)address + 2), *((unsigned char*)address + 3), *((unsigned char*)address + 4), *((unsigned char*)address + 5), *((unsigned char*)address + 6), *((unsigned char*)address + 7), *((unsigned char*)address + 8), *((unsigned char*)address + 9), *((unsigned char*)address + 10), *((unsigned char*)address + 11), *((unsigned char*)address + 12), *((unsigned char*)address + 13), *((unsigned char*)address + 14), *((unsigned char*)address + 15));
    } else {//unknown byte format, default to %08X
        dk_sprintf(destination, formatter08, ((unsigned int)address & 0x000000FF), *(address), *(address + 1), *(address + 2), *(address + 3));
    }
}


void initHeader (int* address) {
    TextOverlay* textOverlay;

    dk_sprintf(header, formatterHeader, address);
    textOverlay = SpawnTextOverlayWrapper(headerStyle, 25, 20, header, 0, 0, 2, 0);
    textOverlay->string = lines[0];
    textObjectInstancesCurrent[0] = (int*)textOverlay;
    setActorOpacity(0xff, textOverlay);
}

void updateHeader (int* address) {
    dk_sprintf(header, formatterHeader, address);
}

void initTable (int* address) {
    TextOverlay* textOverlay;
    int x = 10;
    int y = 40;

    for (int i = 0; i < 8; i++) {
        dk_sprintfWrapper((lines[i+1]), currentFormat, (address + (i * 4)));
        textOverlay = SpawnTextOverlayWrapper(tableStyle, x, y, (lines[i+1]), 0, 0, 2, 0);
        textOverlay->string = lines[i+1];
        textObjectInstancesCurrent[i+1] = (int*)textOverlay;
        setActorOpacity(0xff, textOverlay);
        y += 15;
    }
}

void updateTable (int* address) {
    for (int i = 0; i < 8; i++) { //max of 8 lines
        if (lines[i+1] != 0) {
            dk_sprintfWrapper((lines[i+1]), currentFormat, (address + (i * 4)));
            //we do i+1 on lines because *lines[0] is header text
        }
    }
}

void destroyTextObjects(void) {
    for (int i = 0; i < sizeof(textObjectInstancesCurrent) / sizeof(int*); i++) {
        if (textObjectInstancesCurrent[i] != 0 && textObjectInstancesCurrent[i] != (int*)-1) {
            deleteActor(textObjectInstancesCurrent[i]);
            textObjectInstancesCurrent[i] = 0;
        }
    }
}

void setInitialPrintingAddr() {
    printStartAddr = (int*)0x80000000;
}

void getLinePointers() {
    for (int i = 0; i < (sizeof(lines) / sizeof(char*)) - 1; i++) {//(sizeof(lines) / sizeof(char*)) - 1 because lines[0] is header
        lines[i+1] = malloc(0x44); //i+1 because lines[0] is header
    }
}

void freeLinePointers() {
    for (int i = 0; i < (sizeof(lines) / sizeof(char*)) - 1; i++) {//(sizeof(lines) / sizeof(char*)) - 1 because lines[0] is header
        if (lines[i+1] != 0 && lines[i+1] != (char*)-1) {
            free(lines[i+1]); //i+1 because lines[0] is header
            lines[i+1] = 0;
        }
    }
}

void scrollRAMViewer(void) {
    if (p1PressedButtons & dpadUp) {
        if ( (unsigned int)(printStartAddr - 4) < (unsigned int) validRamReadStart) {
            //prevents reading from invalid memory
        } else {
            printStartAddr -= 0x4;
        }
    }

    if (p1PressedButtons & dpadDown) {
        if ( (unsigned int) (printStartAddr + 4) >= (unsigned int) validRamReadEnd) { //we display 0x10 bytes * 8 therefore we stop advancing at 807FFF90
            //prevents reading from invalid memory
        } else {
            printStartAddr += 0x4;
        }
    }
}

void checkForFormatChange() {
    if (p1PressedButtons & dpadRight && p1HeldButtons & 0x0020) {
        if ( (currentFormat + 1) < 3) {
            currentFormat++;
        }
    }
    if (p1PressedButtons & dpadLeft && p1HeldButtons & 0x0020) {
        if ( currentFormat != 0) {
            currentFormat--;
        }
    }
}

void openOrCloseMenuCheck() {
    if (p1PressedButtons & 0x0800 && p1HeldButtons & 0x0020) { //hold L and press dpad up
        menuFlag = !menuFlag;
        if (menuFlag == 1) { //spawn menu
            headerStyle = 10;
            tableStyle = 5;
            getLinePointers();
            initHeader(printStartAddr);
            initTable(printStartAddr);
        } else { //destroy menu
            destroyTextObjects();
            freeLinePointers();
        }
    }
}

void pickRAMAddr() {
    if (p1PressedButtons & dpadUp) {
        if ( (unsigned int)(printStartAddr - 4) < (unsigned int) validRamReadStart) {
            //prevents reading from invalid memory
        } else {
            printStartAddr -= 0x4;
        }
    }

    if (p1PressedButtons & dpadDown) {
        if ( (unsigned int) (printStartAddr + 4) >= (unsigned int) validRamReadEnd) { //we display 0x10 bytes * 8 therefore we stop advancing at 807FFF90
            //prevents reading from invalid memory
        } else {
            printStartAddr += 0x4;
        }
    }    

}

void mainCFunc() {
    openOrCloseMenuCheck();
    if (menuFlag == 1) {
        checkForFormatChange();
        scrollRAMViewer();
        //pickRAMAddr();
        updateHeader(printStartAddr);
        updateTable(printStartAddr);
    }
    setFlags();
}