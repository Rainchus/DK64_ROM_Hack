#include "../include/common.h"

#define maxWarpLines 10

char returnLine[] = "RETURN";
char warps[] = "WARPS";
char cheats[] = "CHEATS";
char player[] = "PLAYER";
char file[] = "FILE";
char practice[] = "PRACTICE";
char debug[] = "DEBUG";
char settings[] = "SETTINGS";

char warp_Japes[0x18] = "JUNGLE JAPES";

char warp_Aztec[0x18] = "ANGRY AZTEC";
char warp_Factory[0x18] = "FRANTIC FACTORY";

char warp_Galleon[0x18] = "GLOOMY GALLEON";
char warp_FungiForest[0x18] = "FUNGI FOREST";
char warp_creepyCastle[0x18] = "CREEPY CASTLE";
char warp_blank[0x18] = { 0 };

char warpsSubMenu = 0;
char warpsSubMenuIndex = 0;
int warpPageIndex = 0;

char* mainMenuLines[] = { returnLine, warps, cheats, player, file, practice, debug, settings, NULL };
char* warpPage0[] = { warp_Japes, warp_Aztec, warp_Factory, warp_Galleon, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
char* warpPage1[] = { warp_Galleon, warp_FungiForest, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
char** warpMenuPages[] = { warpPage0, warpPage1};

//initializeTransition(0x07, 0x0F);
const short japesWarpID = 0x070F;
const short aztecWarpID = 0x2600;
const short factoryWarpID = 0x1A00;
//
const short galleonWarpID = 0x1E00;
const short fungiForestWarpID = 0x301B;
const short creepyCastleWarpID = 0x5700;

short warpsPage0Values[] = { japesWarpID, aztecWarpID, factoryWarpID, galleonWarpID, NULL};
short warpsPage1Values[] = { galleonWarpID, fungiForestWarpID, creepyCastleWarpID, NULL};

short* warpArrays[] = { warpsPage0Values, warpsPage1Values};



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

void destroyAllTextMenus(void) {
    for (int i = 0; i < sizeof(textObjectInstancesCurrent) / sizeof(int*); i++) {
        if (textObjectInstancesCurrent[i] != NULL && textObjectInstancesCurrent[i] != (TextOverlay*)-1) {
            deleteActor(textObjectInstancesCurrent[i]);
            textObjectInstancesCurrent[i] = NULL;
        }
    }
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

void initWarpMenu(void) {
    TextOverlay* textOverlay;
    int x = 10;
    int y = 40;
    int style = 10;

    //set warp page index to 0 to simplify things
    //get array size
    for (int i = 0; i < maxWarpLines; i++) {
        if (( *((warpMenuPages[warpPageIndex])+ i)) != 0) {
            SpawnTextOverlay(style, x, y, ( *((warpMenuPages[warpPageIndex])+ i)), 0, 0, 2, 0);
        } else {
            SpawnTextOverlay(style, x, y, warp_blank, 0, 0, 2, 0);
            //does equal 0, create blank
        }
        textOverlay = latestObject;
        textObjectInstancesCurrent[i] = textOverlay;
        setActorOpacity(0xff, textOverlay);
        y += 15;
    }
}

void colorCurrentSelection(int lineCount, int colorIndex) {
    for (int i = 0; i < lineCount - 1; i++) { //-1 because last one is NULL
        if (textObjectInstancesCurrent[i] != NULL) {
            if (i == colorIndex) {
                setOverlayColor( (TextOverlay*) textObjectInstancesCurrent[i], 0, 0xFF, 00); //green
            } else {
                setOverlayColor( (TextOverlay*) textObjectInstancesCurrent[i], 0xFF, 0xFF, 0xFF); //white
            }
        }
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

int scrollMenu(int cursorValue, int sizeOfMenu) {
    if ( (p1PressedButtons & L_Button) == 0 && (p1HeldButtons & L_Button) == 0) {
        if (p1PressedButtons & dpadUp) {
            if (cursorValue != 0) {
                cursorValue--;
            } else {
                cursorValue = sizeOfMenu;
            }
        }
        if (p1PressedButtons & dpadDown) {
            if (cursorValue < sizeOfMenu){
                cursorValue++;
            } else {
                cursorValue = 0;
            }
        }
    }
    return cursorValue;
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

void checkWarpMenuInput(void) {
    if (p1HeldButtons & L_Button && p1PressedButtons & dpadLeft) {
        warpsSubMenu = 0;
        mainMenuBoolean = 1;
        destroyAllTextMenus();
        initMainMenu();
    }
}

void checkScrollPage (void) {
    if (p1PressedButtons & dpadRight && ((p1HeldButtons & L_Button) == 0)){
        if (warpPageIndex < sizeof(warpArrays) / sizeof(short*) -1) {
            warpPageIndex++;
        } else {
            warpPageIndex = 0;
        }
    }
    if (p1PressedButtons & dpadLeft && ((p1HeldButtons & L_Button) == 0)){
        if (warpPageIndex != 0) {
            warpPageIndex--;
        } else {
            warpPageIndex = (sizeof(warpMenuPages) / sizeof(char**)) -1;
        }
    }
}

void updateWarpMenuStrings(void) {
    for (int i = 0; i < maxWarpLines; i++) {
        if (textObjectInstancesCurrent[i] != 0) {
            if (textObjectInstancesCurrent[i]->string != 0) {
                if ( (*((warpMenuPages[warpPageIndex])+ i)) != NULL) {
                    textObjectInstancesCurrent[i]->string = (*((warpMenuPages[warpPageIndex])+ i));
                } else {
                    textObjectInstancesCurrent[i]->string = warp_blank;
                }
            }
        }
    }
}

void updateWarpMenu(void) {
    //initializeTransition(0x07, 0x0F);
    checkScrollPage();
    //updateWarpMenuStrings();
    colorCurrentSelection( (sizeof(warpPage0) / sizeof(char*)), warpsSubMenuIndex);
    checkWarpMenuInput();
    updateWarpMenuStrings();
    int i;
    //get array size
    if (mainMenuBoolean == 1) {
        goto updateWarpMenuExit;
    } else {
        for (i = 0; i < maxWarpLines; i++) {
            if (*(textObjectInstancesCurrent[i]->string) == 0) {
                //points to null string
                i--;
                break;
            }
        }
    }
        //(warpMenuPages[warpsPage])
    warpsSubMenuIndex = scrollMenu(warpsSubMenuIndex, i);
    if (p1PressedButtons & L_Button) { //double tap L to warp
        if (inputTimer == 0) { //start timer
            inputTimer = 7;
        } else {
            //warp
            inputTimer = 0;
            short* arg0 = warpArrays[warpPageIndex];
            short arg0_1 = (*(arg0 + warpsSubMenuIndex)) >> 8; //shift upper byte of s16 to lower byte
            short arg1_1 = (*(arg0 + warpsSubMenuIndex)) & 0xFF;
            initializeTransition(arg0_1, arg1_1); //warp
            warpsSubMenu = 0;
            destroyAllTextMenus();
        }
    }
    updateWarpMenuExit:
    i = 0;
}

void handleOption(int optionSelected) {
    switch (currentMenu) {
        case 0: //nothing
            break;
        case 1: //
            updateWarpMenu();
            break;
    }
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