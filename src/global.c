#include "../include/common.h"

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

void destroyAllTextMenus(void) {
    for (int i = 0; i < sizeof(textObjectInstancesCurrent) / sizeof(TextOverlay*); i++) {
        if (textObjectInstancesCurrent[i] != NULL && textObjectInstancesCurrent[i] != (TextOverlay*)-1) {
            deleteActor(textObjectInstancesCurrent[i]);
            textObjectInstancesCurrent[i] = NULL;
        }
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