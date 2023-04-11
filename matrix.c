#include "stdlib.h"
#include "math.h"
#include "matrix.h"

f4matrix f4matrix_perspectiveProjection(float width, float height, float fov_grad, float near, float far) {
    f4matrix f = calloc(16, sizeof(float*));

    float fov_rad = fov_grad * M_PI / 180.0;
    float fk = cos(0.5 * fov_rad) / sin(0.5 * fov_rad);
    float aspect = width / height;
    float clip_near = (far + near) / (near - far);
    float clip_far = (2.0 * far * near) / (near - far);

    // [0][0]
    f[0] = fk / aspect;

    // [1][1]
    f[5] = fk;

    // [2][2], [2][3]
    f[10] = clip_near;
    f[11] = clip_far;

    // [3][2]
    f[14] = -1.0;

    return f;
}

f4matrix f4matrix_camera() {
    f4matrix f = calloc(16, sizeof(float*));

    f[0] = 1.0;

    f[5] = 0.9284;
    f[6] = 0.3713;
    f[7] = 0.0;

    f[9] = 0.3713;
    f[10] = -0.9284;
    f[11] = -10.7703;

    f[15] = 1.0;

    return f;
}

f4matrix f4matrix_identity() {
    f4matrix f = calloc(16, sizeof(float*));

    f[0] = 1.0;
    f[5] = 1.0;
    f[10] = 1.0;
    f[15] = 1.0;

    return f;
}

f4matrix f4matrix_multiply(f4matrix mat, f4matrix mat2) {
    f4matrix f = calloc(16, sizeof(float*));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            f[i * 4 + j] =  mat[i * 4] * mat2[j] +
                            mat[i * 4 + 1] * mat2[4 + j] +
                            mat[i * 4 + 2] * mat2[8 + j] +
                            mat[i * 4 + 3] * mat2[12 + j];
        }
    }

    free(mat);
    free(mat2);
    return f;
}

f4matrix f4matrix_rotateX(f4matrix mat, float grad) {
    f4matrix f = calloc(16, sizeof(float*));
    float angleRad = grad * M_PI / 180.0;

    f[0] = 1.0;
    f[5] = cos(angleRad);
    f[6] = -sin(angleRad);
    f[9] = sin(angleRad);
    f[10] = cos(angleRad);
    f[15] = 1.0;

    return f4matrix_multiply(mat, f);
}

f4matrix f4matrix_rotateY(f4matrix mat, float grad) {
    f4matrix f = calloc(16, sizeof(float*));
    float angleRad = grad * M_PI / 180.0;

    f[0] = cos(angleRad);
    f[2] = sin(angleRad);
    f[5] = 1.0;
    f[8] = -sin(angleRad);
    f[10] = cos(angleRad);
    f[15] = 1.0;

    return f4matrix_multiply(mat, f);
}

f4matrix f4matrix_rotateZ(f4matrix mat, float grad) {
    f4matrix f = calloc(16, sizeof(float*));
    float angleRad = grad * M_PI / 180.0;

    f[0] = cos(angleRad);
    f[1] = -sin(angleRad);
    f[4] = sin(angleRad);
    f[5] = cos(angleRad);
    f[10] = 1.0;
    f[15] = 1.0;

    return f4matrix_multiply(mat, f);
}

f4matrix f4matrix_scale(f4matrix mat, float x, float y, float z) {
    f4matrix f = calloc(16, sizeof(float*));

    f[0] = x;
    f[5] = y;
    f[10] = z;
    f[15] = 1.0;

    return f4matrix_multiply(mat, f);
}

f4matrix f4matrix_translate(f4matrix mat, float x, float y, float z) {
    f4matrix f = calloc(16, sizeof(float*));

    f[0] = 1.0;
    f[3] = x;
    f[5] = 1.0;
    f[7] = y;
    f[10] = 1.0;
    f[11] = z;
    f[15] = 1.0;

    return f4matrix_multiply(mat, f);
}

