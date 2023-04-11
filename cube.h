#include "matrix.h"

typedef struct Cube {
    float* vertices;
    int v_size;

    float* normals;
    int n_size;

    unsigned int* indices;
    int i_size;
    int i_count;

    f4matrix model;
    f4matrix identity;

    float angle_x;
    float angle_y;
    float angle_z;
    float pos_x;
    float pos_y;
    float pos_z;
    float scale_x;
    float scale_y;
    float scale_z;
} Cube;

Cube* newCube();
void updateCubeModel(Cube* cube);
