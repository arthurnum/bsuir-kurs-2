#include "stdlib.h"
#include "string.h"
#include "cube.h"

Cube* newCube() {
    Cube* cube = malloc(sizeof(Cube));

    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    float w = 1.0;

    float vertices[] = {
        // front
        x - w, y - w, z - w,
        x - w, y + w, z - w,
        x + w, y - w, z - w,
        x + w, y + w, z - w,
        // left
        x - w, y - w, z - w,
        x - w, y + w, z - w,
        x - w, y - w, z + w,
        x - w, y + w, z + w,
        // top
        x - w, y + w, z - w,
        x - w, y + w, z + w,
        x + w, y + w, z - w,
        x + w, y + w, z + w,
        // right
        x + w, y - w, z - w,
        x + w, y + w, z - w,
        x + w, y - w, z + w,
        x + w, y + w, z + w,
        // bottom
        x - w, y - w, z - w,
        x - w, y - w, z + w,
        x + w, y - w, z - w,
        x + w, y - w, z + w,
        // back
        x - w, y - w, z + w,
        x - w, y + w, z + w,
        x + w, y - w, z + w,
        x + w, y + w, z + w,
    };

    float normals[] = {
        // front normals
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        0.0, 0.0, -1.0,
        // left normals
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        -1.0, 0.0, 0.0,
        // top normals
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        // right normals
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        // bottom normals
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        0.0, -1.0, 0.0,
        // back normals
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
    };

    unsigned int indices[] = {
        // front
        0, 1, 2,
        3, 2, 1,
        // left
        4, 5, 6,
        7, 6, 5,
        // top
        8, 9, 10,
        11, 10, 9,
        // right
        12, 13, 14,
        15, 14, 13,
        // bottom
        16, 17, 18,
        19, 18, 17,
        // back
        20, 21, 22,
        23, 22, 21,
    };

    cube->v_size = sizeof(float) * 72;
    cube->vertices = malloc(cube->v_size);
    memcpy(cube->vertices, vertices, cube->v_size);

    cube->n_size = sizeof(float) * 72;
    cube->normals = malloc(cube->n_size);
    memcpy(cube->normals, normals, cube->n_size);

    cube->i_size = sizeof(unsigned int) * 36;
    cube->i_count = 36;
    cube->indices = malloc(cube->i_size);
    memcpy(cube->indices, indices, cube->i_size);

    resetCubeModel(cube);

    return cube;
}

void updateCubeModel(Cube* cube) {
    f4matrix old_model = cube->model;

    cube->model =
        f4matrix_scale(
            f4matrix_rotateZ(
                f4matrix_rotateY(
                    f4matrix_rotateX(
                        f4matrix_translate(
                            f4matrix_identity(),
                            cube->pos_x, cube->pos_y, cube->pos_z
                        ),
                        cube->angle_x
                    ),
                    cube->angle_y
                ),
                cube->angle_z
            ),
            cube->scale_x, cube->scale_y, cube->scale_z
        );

    free(old_model);
}

void resetCubeModel(Cube* cube) {
    cube->model = f4matrix_identity();
    cube->pos_x = 0.0;
    cube->pos_y = 0.0;
    cube->pos_z = 0.0;
    cube->angle_x = 0.0;
    cube->angle_y = 0.0;
    cube->angle_z = 0.0;
    cube->scale_x = 1.0;
    cube->scale_y = 1.0;
    cube->scale_z = 1.0;
}
