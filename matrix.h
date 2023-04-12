typedef float* f4matrix;

f4matrix f4matrix_perspectiveProjection(float width, float height, float fov_grad, float near, float far);
f4matrix f4matrix_camera();
f4matrix f4matrix_identity();
f4matrix f4matrix_multiply(f4matrix mat, f4matrix mat2);
f4matrix f4matrix_rotateX(f4matrix mat, float grad);
f4matrix f4matrix_rotateY(f4matrix mat, float grad);
f4matrix f4matrix_rotateZ(f4matrix mat, float grad);
f4matrix f4matrix_scale(f4matrix mat, float x, float y, float z);
f4matrix f4matrix_translate(f4matrix mat, float x, float y, float z);
char* f4matrix_toString(f4matrix mat);
