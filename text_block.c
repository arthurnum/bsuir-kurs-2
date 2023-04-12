#include "stdlib.h"
#include "string.h"
#include "text_block.h"

TextBlock* newTextBlock(float xl, float xr, float yb, float yt) {
    TextBlock* block = malloc(sizeof(TextBlock));

    float vertices[] = {
        xl, yb, -15.0,
        xl, yt, -15.0,
        xr, yb, -15.0,
        xr, yt, -15.0,
    };

    float uva[] = {
        0.0, 1.0,
        0.0, 0.0,
        1.0, 1.0,
        1.0, 0.0,
    };

    unsigned int indices[] = {
        0, 1, 2,
        3, 2, 1
    };

    block->v_size = sizeof(float) * 12;
    block->vertices = malloc(block->v_size);
    memcpy(block->vertices, vertices, block->v_size);

    block->uva_size = sizeof(float) * 8;
    block->uva = malloc(block->uva_size);
    memcpy(block->uva, uva, block->uva_size);

    block->i_count = 6;
    block->i_size = sizeof(unsigned int) * 6;
    block->indices = malloc(block->i_size);
    memcpy(block->indices, indices, block->i_size);

    return block;
}
