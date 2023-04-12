#include "control.h"
#include "stdlib.h"
#include "stdio.h"

const char* rotateString(char mode) {
    switch (mode % 3) {
        case ROTATE_MODE_X:
            return "Rotate1";
        case ROTATE_MODE_Y:
            return "Rotate2";
        case ROTATE_MODE_Z:
            return "Rotate3";
        default:
            return "Rotate";
    }
}

const char* translateString(char mode) {
    switch (mode % 2) {
        case TRANSLATE_MODE_Y:
            return "Translate1";
        case TRANSLATE_MODE_Z:
            return "Translate2";
        default:
            return "Translate";
    }
}

const char* objectString(ControlState state) {
    if (state.objectMode % 2 == 0) {
        return "Cube";
    } else {
        return "Camera";
    }
}

const char* modeString(ControlState state) {
    switch (state.mode) {
        case MODE_ROTATE:
            return rotateString(state.rotateMode);
        case MODE_SCALE:
            return "Scale";
        case MODE_TRANSLATE:
            return translateString(state.translateMode);
        default:
            return "Off";
    }
}

char* modeToString(ControlState state) {
    char* text = malloc(64);
    sprintf(
        text,
        "Mode: %6s %10s",
        objectString(state), modeString(state)
    );
    return text;
}
