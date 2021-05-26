#include "../include/common.h"

#define maxWarpLines 10

char warp_Japes[0x18] = "JUNGLE JAPES";

char warp_Aztec[0x18] = "ANGRY AZTEC";
char warp_Factory[0x18] = "FRANTIC FACTORY";

char warp_Galleon[0x18] = "GLOOMY GALLEON";
char warp_FungiForest[0x18] = "FUNGI FOREST";
char warp_creepyCastle[0x18] = "CREEPY CASTLE";
char warp_blank[0x18] = { 0 };

char warpsSubMenuIndex = 0;
int warpPageIndex = 0;


char* warpPage0[] = { warp_Japes, warp_Aztec, warp_Factory, warp_Galleon, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
char* warpPage1[] = { warp_Galleon, warp_FungiForest, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
char* warpPage2[] = { warp_Japes, warp_Factory, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
char** warpMenuPages[] = { warpPage0, warpPage1, warpPage2};

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
short warpsPage2Values[] = { japesWarpID, factoryWarpID, NULL, NULL};

short* warpArrays[] = { warpsPage0Values, warpsPage1Values, warpsPage2Values};



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

void checkScrollPage (void) {
    if (p1PressedButtons & dpadRight && ((p1HeldButtons & L_Button) == 0)){
        if (warpPageIndex < sizeof(warpMenuPages) / sizeof(char**) -1) {
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

void checkWarpMenuInput(void) {
    if (p1HeldButtons & L_Button && p1PressedButtons & dpadLeft) {
        warpsSubMenu = 0;
        mainMenuBoolean = 1;
        destroyAllTextMenus();
        initMainMenu();
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
    checkScrollPage();
    updateWarpMenuStrings();
    colorCurrentSelection( (sizeof(warpPage0) / sizeof(char*)), warpsSubMenuIndex);
    checkWarpMenuInput();
    int i;
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

    warpsSubMenuIndex = scrollMenu(warpsSubMenuIndex, i);

    if (p1PressedButtons & L_Button) { //double tap L to warp
        if (inputTimer == 0) { //start timer
            inputTimer = 7;
        } else {
            //warp
            inputTimer = 0;
            short* arg0 = warpArrays[warpPageIndex];
            short room = (*(arg0 + warpsSubMenuIndex)) >> 8; //shift upper byte of s16 to lower byte
            short entrance = (*(arg0 + warpsSubMenuIndex)) & 0xFF;
            initializeTransition(room, entrance); //warp
            warpsSubMenu = 0;
            destroyAllTextMenus();
        }
    }
    updateWarpMenuExit:
    i = 0;
}

int warpMain(void) {
    int variable;

    variable = 5;
    return variable;
}