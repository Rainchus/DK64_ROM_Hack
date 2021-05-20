#include "../include/common.h"

char testString[] = "Test";
char testString2[] = "%s 10";
char tempSpace[0x20];

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

//void printText (int* hud, int xPos, int yPos, float scale, char* string)
void mainCFunc() {
    if (p1PressedButtons & 0x0800) { //on dpad up press
        SpawnTextOverlay(10, 25, 25, testString);
        setCurrentActorOpacity(0xff);
    }
    setFlags();
    if (p1HeldButtons & 0x0400) {
        //setFlags();
    }
}