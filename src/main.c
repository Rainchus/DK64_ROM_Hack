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

char testString[] = "TEST";
char testString2[] = "%s 10";
char testString3[] = "TEST AGAIN";
char formatter08[] = "%08X %08X %08X %08X";
char formatter04[] = "%04X %04X %04X %04X %04X %04X %04X %04X ";
char formatter02[] = "%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ";
char formatterHeader[] = "ADDR: %08X";

char line0[0x10];
char line1[0x10];
char line2[0x10];
char line3[0x10];
char line4[0x10];
char line5[0x10];
char line6[0x10];
char line7[0x10];
char line8[0x10];
char line9[0x10];

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

void clearCurrentTextActors(void) {
    for (int i = 0; i < sizeof(textObjectInstancesCurrent) / sizeof(int*); i++) {
        textObjectInstancesCurrent[i] = 0;
    }
}

void clearPreviousTextActors(void) {
    for (int i = 0; i < sizeof(textObjectInstancesPrevious) / sizeof(int*); i++) {
        textObjectInstancesPrevious[i] = 0;
    }
}

void copyCurrentTextActorsToPrevious(void) {
    for (int i = 0; i < sizeof(textObjectInstancesPrevious) / sizeof(int*); i++) {
        textObjectInstancesPrevious[i] = textObjectInstancesCurrent[i];
    }
}

void destroyPreviousActors(void) {
    for (int i = 0; i < sizeof(textObjectInstancesPrevious) / sizeof(int*); i++) {
        if (textObjectInstancesPrevious[i] == 0 || textObjectInstancesPrevious[i] == (int*)0xFFFFFFFF) {
            continue;
        } else {
            deleteActor(textObjectInstancesPrevious[i]);
            textObjectInstancesPrevious[i] = 0;
        }
    }
}

int* SpawnTextOverlayWrapper(int z, int y, int x, char* string) {
    SpawnTextOverlay(z, y, x, string);
    return latestObject;
}

void createCurrentActors(int* address) { //a0 = address to print from
    int x = 40;
    int y = 25;
    int z = 10;
    int* objectInstance;
    char tempSpace[40];

    for (int i = 0; i < 8; i++) { //starts to cause lag pretty quickly...maybe only do 8
        dk_sprintf(tempSpace, formatter08, *(address + i * 4), *(address + (i * 4 + 1)), *(address + (i * 4 + 2)), *(address + (i * 4 + 3)));
        objectInstance = SpawnTextOverlayWrapper(z, y, x, tempSpace);
        textObjectInstancesCurrent[i + 1] = objectInstance; //i + 1 because heading is in first slot by default
        setActorOpacity(0xff, objectInstance);
        x += 15;
    }
}

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

void printHeader (int* address) { //a0 = address to print from
    int* objectInstance;
    char tempHeaderSpace[0x20];

    dk_sprintf(tempHeaderSpace, formatterHeader, address);
    objectInstance = SpawnTextOverlayWrapper(10, 25, 20, tempHeaderSpace);
    textObjectInstancesCurrent[0] = objectInstance;
    setActorOpacity(0xff, objectInstance);
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
    }

    copyCurrentTextActorsToPrevious();
    destroyPreviousActors();
    clearCurrentTextActors();

    if (menuFlag == 1) {
        printHeader(printStartAddr);
        createCurrentActors(printStartAddr);
    }
    setFlags();
}