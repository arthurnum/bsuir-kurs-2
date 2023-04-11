typedef struct MeshPlane {
    float* vertices;
    int v_size;

    unsigned int* indices;
    int i_size;
    int i_count;
} MeshPlane;

MeshPlane* newMeshPlane();
