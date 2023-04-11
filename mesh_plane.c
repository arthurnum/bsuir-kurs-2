#include "stdlib.h"
#include "string.h"
#include "mesh_plane.h"

MeshPlane* newMeshPlane() {
    MeshPlane* plane = malloc(sizeof(MeshPlane));

    float x = -50.0;
    float y = 0.0;
    float z = -50.0;
    float w = 5.0;

    plane->v_size = sizeof(float) * 240;
    plane->vertices = malloc(plane->v_size);
    int a = 0;
    for (int i = 0; i < 20; i++) {
        plane->vertices[a++] = x + w * i;
        plane->vertices[a++] = y;
        plane->vertices[a++] = z;

        plane->vertices[a++] = x + w * i;
        plane->vertices[a++] = y;
        plane->vertices[a++] = z + 100;

        plane->vertices[a++] = x;
        plane->vertices[a++] = y;
        plane->vertices[a++] = z + w * i;

        plane->vertices[a++] = x + 100;
        plane->vertices[a++] = y;
        plane->vertices[a++] = z + w * i;
    }

    plane->i_count = 80;
    plane->i_size = sizeof(unsigned int) * 80;
    plane->indices = malloc(plane->i_size);
    for (int i = 0; i < 80; i++) {
        plane->indices[i] = i;
    }

    return plane;
}

