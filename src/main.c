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

char testString[] = "TEST";
char testString2[] = "%s 10";
char testString3[] = "TEST AGAIN";
char formatter08[] = "%02X: %08X %08X %08X %08X";
char formatter04[] = "%04X %04X %04X %04X %04X %04X %04X %04X ";
char formatter02[] = "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ";
char formatterHeader[] = "ADDR: %08X";

char header[40];
char line1[40];
char line2[40];
char line3[40];
char line4[40];
char line5[40];
char line6[40];
char line7[40];
char line8[40];
char line9[40];

char* lines[] = {header, line1, line2, line3, line4, line5, line6, line7, line8, line9};

char tempHeaderSpace[0x20];
char tempSpace[40];

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

TextOverlay* SpawnTextOverlayWrapper(int z, int y, int x, char* string) {
    SpawnTextOverlay(z, y, x, string);
    return latestObject;
}

/*
void dk_sprintfWrapper (char* destination, int byteFormat, int* address) {
    if (byteFormat == ByteFormat4) {
        dk_sprintf(destination, formatter08, *(address), *(address + 1), *(address + 2), *(address + 3));
    } else if (byteFormat == ByteFormat2) {
        dk_sprintf(destination, formatter04, *(address), *(address + 1), *(address + 2), *(address + 3), *(address + 4), *(address + 5), *(address + 6), *(address + 7));
    } else if (byteFormat == ByteFormat1) {
        dk_sprintf(destination, formatter02, *(address), *(address + 1), *(address + 2), *(address + 3), *(address + 4), *(address + 5), *(address + 6), *(address + 7), *(address + 8), *(address + 9), *(address + 10), *(address + 11), *(address + 12), *(address + 13), *(address + 14), *(address + 15));
    } else {//unknown byte format, default to %08X
        dk_sprintf(destination, formatter08, *(address), *(address + 1), *(address + 2), *(address + 3));
    }
}
*/

void initHeader (int* address) {
    TextOverlay* textOverlay;

    dk_sprintf(header, formatterHeader, address);
    textOverlay = SpawnTextOverlayWrapper(10, 25, 20, header);
    //textOverlay->string now holds a pointer to TempHeaderSpace
    textOverlay->string = lines[0];
    textObjectInstancesCurrent[0] = (int*)textOverlay;
    setActorOpacity(0xff, textOverlay);
}

void updateHeader (int* address) {
    dk_sprintf(header, formatterHeader, address);
}

void initTable (int* address) {
    TextOverlay* textOverlay;
    int x = 40;
    int y = 15;
    int z = 10;

    for (int i = 0; i < 8; i++) {
        dk_sprintf((lines[i+1]), formatter08, ( (int)(address + i * 4) & 0x000000FF), *(address + i * 4), *(address + (i * 4 + 1)), *(address + (i * 4 + 2)), *(address + (i * 4 + 3)));
        textOverlay = SpawnTextOverlayWrapper(z, y, x, (lines[i+1]));
        textOverlay->string = lines[i+1];
        textObjectInstancesCurrent[i+1] = (int*)textOverlay;
        setActorOpacity(0xff, textOverlay);
        x += 15;
    }
}

void updateTable (int* address) {
    for (int i = 0; i < 8; i++) { //max of 8 lines
        dk_sprintf((lines[i+1]), formatter08, ( (int)(address + i * 4) & 0x000000FF), *(address + i * 4), *(address + (i * 4 + 1)), *(address + (i * 4 + 2)), *(address + (i * 4 + 3))); 
        //we do i+1 on lines because *lines[0] is header text
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

void mainCFunc() {
    if (p1PressedButtons & dpadUp) {
        if ( (unsigned int)(printStartAddr - 4) < (unsigned int) validRamReadStart) {
            //dont change address, out of normal RDRAM range
        } else {
            printStartAddr -= 0x4;
        }
    }

    if (p1PressedButtons & dpadDown) {
        if ( (unsigned int) (printStartAddr + 4) >= (unsigned int) validRamReadEnd) { //we display 0x10 bytes * 8 therefore we stop advancing at 807FFF90 to -
            //prevent reading from invalid memory
            //dont change address, out of normal RDRAM range
        } else {
            printStartAddr += 0x4;
        }
    }

    if (p1PressedButtons & 0x0800 && p1HeldButtons & 0x0020) { //hold L and press dpad up
        menuFlag = !menuFlag;
        if (menuFlag == 1) { //spawn menu
            initHeader(printStartAddr);
            initTable(printStartAddr);
        } else { //destroy menu
            destroyTextObjects();
        }
    }
    updateHeader(printStartAddr);
    updateTable(printStartAddr);
    setFlags();
}