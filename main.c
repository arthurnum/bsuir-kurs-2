#include "SDL.h"
#include "SDL_ttf.h"
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "stdlib.h"

#include "cube.h"
#include "matrix.h"
#include "mesh_plane.h"
#include "shaders.h"
#include "text_block.h"

int main (int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    if ( TTF_Init() < 0 ) {
		return -1;
	}

    TTF_Font* font;
    font = TTF_OpenFont("inconsolata.otf", 24);
    SDL_Surface* text;
    int textSize;
    char* matrixPresent;
    GLubyte *pixies;
    SDL_Color color = { 55, 55, 55 };

    // Open Window
    SDL_Window* window = SDL_CreateWindow("Eremeev: Matrix - 3D scene", 0, 0, 1024, 768, SDL_WINDOW_OPENGL);
    if (!window) {
        return -1;
    }

    f4matrix projection = f4matrix_perspectiveProjection(1024.0, 768.0, 55.0, 0.1, 100.0);
    f4matrix camera = f4matrix_camera();
    Cube* cube = newCube();
    MeshPlane* plane = newMeshPlane();
    TextBlock* textBlock = newTextBlock();

    // OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    // Create OpenGL context
    SDL_GLContext Context = SDL_GL_CreateContext(window);

    Shader vertexShader = loadVertexShader("GLSL/cube.vert");
    Shader fragmentShader = loadFragmentShader("GLSL/cube.frag");

    Shader planeVertexShader = loadVertexShader("GLSL/plane.vert");
    Shader planeFragmentShader = loadFragmentShader("GLSL/plane.frag");

    Shader textBlockVertexShader = loadVertexShader("GLSL/text.vert");
    Shader textBlockFragmentShader = loadFragmentShader("GLSL/text.frag");

    ShaderProgram shaderProgram = buildShaderProgram(vertexShader, fragmentShader);
    ShaderProgram planeShaderProgram = buildShaderProgram(planeVertexShader, planeFragmentShader);
    ShaderProgram textBlockShaderProgram = buildShaderProgram(textBlockVertexShader, textBlockFragmentShader);

    // Cube draw init
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, cube->v_size, cube->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    unsigned int VBO_normal;
    glGenBuffers(1, &VBO_normal);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normal);
    glBufferData(GL_ARRAY_BUFFER, cube->n_size, cube->normals, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube->i_size, cube->indices, GL_STATIC_DRAW);

    // Mesh plane draw init
    unsigned int planeVAO;
    glGenVertexArrays(1, &planeVAO);
    glBindVertexArray(planeVAO);

    unsigned int planeVBO;
    glGenBuffers(1, &planeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, plane->v_size, plane->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    unsigned int planeEBO;
    glGenBuffers(1, &planeEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, plane->i_size, plane->indices, GL_STATIC_DRAW);

    // Text block21 draw init
    unsigned int tbVAO;
    glGenVertexArrays(1, &tbVAO);
    glBindVertexArray(tbVAO);

    unsigned int tbVBO;
    glGenBuffers(1, &tbVBO);
    glBindBuffer(GL_ARRAY_BUFFER, tbVBO);
    glBufferData(GL_ARRAY_BUFFER, textBlock->v_size, textBlock->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    unsigned int tbVBO_uva;
    glGenBuffers(1, &tbVBO_uva);
    glBindBuffer(GL_ARRAY_BUFFER, tbVBO_uva);
    glBufferData(GL_ARRAY_BUFFER, textBlock->uva_size, textBlock->uva, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int tbEBO;
    glGenBuffers(1, &tbEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tbEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, textBlock->i_size, textBlock->indices, GL_STATIC_DRAW);

    unsigned int textTexture;
    glGenTextures(1, &textTexture);
    glBindTexture(GL_TEXTURE_2D, textTexture);

    matrixPresent = f4matrix_toString(cube->model);
    text = TTF_RenderText_Blended_Wrapped( font, matrixPresent, color, 380 );
    textSize = text->h * text->pitch * text->format->BytesPerPixel;
    pixies = (GLubyte *)(text->pixels);
    unsigned int textPBO;
    glGenBuffers(1, &textPBO);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, textPBO);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, textSize, pixies, GL_STATIC_DRAW);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, text->pitch / text->format->BytesPerPixel);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text->w, text->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    free(matrixPresent);
    SDL_FreeSurface(text);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glViewport(0, 0, 1024, 768);
    glClearColor(0.98, 0.95, 0.85, 0.0);

    int time = 0;
    char running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    running = 0;
                    break;
                // Other input here
                default:
                    break;
                }
            }
            else if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        time++;
        updateCubeModel(cube);
        // camera = f4matrix_translate(camera, 0.0, -0.0001, 0.0);
        cube->angle_x += 0.005;
        cube->angle_y += 0.005;
        cube->angle_z += 0.005;

        if (time % 100 == 0) {
            matrixPresent = f4matrix_toString(cube->model);
            text = TTF_RenderText_Blended_Wrapped( font, matrixPresent, color, 380 );
            textSize = text->h * text->pitch * text->format->BytesPerPixel;
            pixies = (GLubyte *)(text->pixels);
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, textPBO);
            glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, textSize, pixies);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text->w, text->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
            free(matrixPresent);
            SDL_FreeSurface(text);
            // cube->pos_x += 0.001;
            // cube->pos_y += 0.0005;
            // cube->scale_x += 0.0004;
            // cube->scale_y += 0.0001;
            // cube->scale_z += 0.0001;
        } else {
            // cube->pos_x -= 0.001;
            // cube->pos_y -= 0.0005;
            // cube->scale_x -= 0.0004;
            // cube->scale_y -= 0.0001;
            // cube->scale_z -= 0.0001;
        }


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // OpenGL rendering goes here
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        uniformMatrix(shaderProgram, "projection", projection);
        uniformMatrix(shaderProgram, "view", camera);
        uniformMatrix(shaderProgram, "model", cube->model);
        glDrawElements(GL_TRIANGLES, cube->i_count, GL_UNSIGNED_INT, 0);

        glUseProgram(planeShaderProgram);
        glBindVertexArray(planeVAO);
        uniformMatrix(planeShaderProgram, "projection", projection);
        uniformMatrix(planeShaderProgram, "view", camera);
        glDrawElements(GL_LINES, plane->i_count, GL_UNSIGNED_INT, 0);

        glUseProgram(textBlockShaderProgram);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textTexture);
        glBindVertexArray(tbVAO);
        uniformMatrix(textBlockShaderProgram, "projection", projection);
        uniformMatrix(textBlockShaderProgram, "view", camera);
        uniformSampler2D(textBlockShaderProgram, "texture1", 0);
        glDrawElements(GL_TRIANGLES, textBlock->i_count, GL_UNSIGNED_INT, 0);


        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();
    return 0;
}
