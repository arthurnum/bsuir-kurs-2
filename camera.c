#include "stdlib.h"
#include "camera.h"

Camera* newCamera() {
    Camera* camera = malloc(sizeof(Camera));
    resetCameraView(camera);
    return camera;
}

void updateCameraView(Camera* camera) {
    f4matrix old_view = camera->view;

    camera->view =
        f4matrix_scale(
            f4matrix_rotateZ(
                f4matrix_rotateY(
                    f4matrix_rotateX(
                        f4matrix_translate(
                            f4matrix_camera(),
                            camera->pos_x, camera->pos_y, camera->pos_z
                        ),
                        camera->angle_x
                    ),
                    camera->angle_y
                ),
                camera->angle_z
            ),
            camera->scale_x, camera->scale_y, camera->scale_z
        );

    free(old_view);
}

void resetCameraView(Camera* camera) {
    camera->view = f4matrix_camera();
    camera->pos_x = 0.0;
    camera->pos_y = 0.0;
    camera->pos_z = 0.0;
    camera->angle_x = 0.0;
    camera->angle_y = 0.0;
    camera->angle_z = 0.0;
    camera->scale_x = 1.0;
    camera->scale_y = 1.0;
    camera->scale_z = 1.0;
}
