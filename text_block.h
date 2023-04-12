typedef struct TextBlock {
    float* vertices;
    int v_size;

    float* uva;
    int uva_size;

    unsigned int* indices;
    int i_size;
    int i_count;
} TextBlock;

TextBlock* newTextBlock(float xl, float xr);
