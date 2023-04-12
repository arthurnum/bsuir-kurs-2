#include "matrix.h"

typedef struct Camera {
    f4matrix view;

    float angle_x;
    float angle_y;
    float angle_z;
    float pos_x;
    float pos_y;
    float pos_z;
    float scale_x;
    float scale_y;
    float scale_z;
} Camera;

Camera* newCamera();
void updateCameraView(Camera* camera);
void resetCameraView(Camera* camera);
