#define MODE_ROTATE 1
#define MODE_TRANSLATE 2
#define MODE_SCALE 3

#define ROTATE_MODE_X 0
#define ROTATE_MODE_Y 1
#define ROTATE_MODE_Z 2

#define TRANSLATE_MODE_Z 0
#define TRANSLATE_MODE_Y 1

typedef struct ControlState {
    char mode;
    char rotateMode;
    char translateMode;
    char objectMode;
} ControlState;

char* modeToString(ControlState state);
