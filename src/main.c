#include "../include/common.h"

char returnLine[] = "RETURN";
char warps[] = "WARPS";
char cheats[] = "CHEATS";
char player[] = "PLAYER";
char file[] = "FILE";
char practice[] = "PRACTICE";
char debug[] = "DEBUG";
char settings[] = "SETTINGS";

char* mainMenuLines[] = { returnLine, warps, cheats, player, file, practice, debug, settings, NULL };

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

void initMainMenu(void) {
    TextOverlay* textOverlay;
    int x = 10;
    int y = 40;
    int style = 10;

    for (int i = 0; i < (sizeof(mainMenuLines) / sizeof(char*)) - 1; i++) { //-1 because last one is NULL
        SpawnTextOverlay(style, x, y, (mainMenuLines[i]), 0, 0, 2, 0);
        textOverlay = latestObject;
        textObjectInstancesCurrent[i] = textOverlay;
        setActorOpacity(0xff, textOverlay);
        y += 15;
    }
}

void openOrCloseMainMenuCheck(void) {
    if (p1HeldButtons & L_Button && p1PressedButtons & dpadUp) { //hold L, double tap dpad up to open menu
        if (warpsSubMenu == 0) {
            if (inputTimer == 0) { //start timer
                inputTimer = 7;
            } else {
                mainMenuBoolean = !mainMenuBoolean;
                inputTimer = 0;
                if (mainMenuBoolean == 1) { //spawn menu
                    initMainMenu();
                } else { //destroy menu
                    destroyAllTextMenus();
                }
            }
        }
    }
    if (inputTimer != 0) {
        inputTimer--;
    }
}

int selectOptionMainMenu(void) {
    if (p1PressedButtons & dpadRight && p1HeldButtons & L_Button) { //hold L and press dpadRight
            mainMenuBoolean = 0;
            destroyAllTextMenus();
        switch (mainCursorIndex) {
            case 0: //return
                return 0;
            case 1: //warps
                initWarpMenu();
                warpsSubMenu = 1;
                return 1;
        }
    }
    return -1;
}

void menuMain(void) {
    openOrCloseMainMenuCheck();
    if (mainMenuBoolean == 1) {
        colorCurrentSelection( (sizeof(mainMenuLines) / sizeof(char*)), mainCursorIndex);
        mainCursorIndex = scrollMenu(mainCursorIndex, sizeof(mainMenuLines) / sizeof(char*) -2);
        currentMenu = selectOptionMainMenu();
    } else {
        switch (mainCursorIndex) {
            case 0:
                break;
            case 1:
                if (warpsSubMenu == 1) {
                    updateWarpMenu();
                }
                break;
        }
    }
}

void mainCFunc() {
    menuMain();
    //ramViewMain();
    setFlags();
}