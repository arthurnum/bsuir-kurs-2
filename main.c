#include "SDL.h"
#include "SDL_ttf.h"
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "stdlib.h"

#include "camera.h"
#include "cube.h"
#include "control.h"
#include "matrix.h"
#include "mesh_plane.h"
#include "shaders.h"
#include "text_block.h"

void processStateAgainstCube(ControlState state, SDL_Keycode key, Cube* cube) {
    switch (key) {
        case SDLK_RIGHT:
            switch (state.mode) {
                case MODE_ROTATE:
                    switch (state.rotateMode % 3) {
                        case ROTATE_MODE_X:
                            cube->angle_z -= 0.5;
                            break;
                        case ROTATE_MODE_Y:
                            cube->angle_z -= 0.5;
                            break;
                        case ROTATE_MODE_Z:
                            cube->angle_y += 0.5;
                            break;
                        default:
                            break;
                    }
                    break;
                case MODE_TRANSLATE:
                    cube->pos_x += 0.01;
                    break;
                default:
                    break;
            }
            break;

        case SDLK_LEFT:
            switch (state.mode) {
                case MODE_ROTATE:
                    switch (state.rotateMode % 3) {
                        case ROTATE_MODE_X:
                            cube->angle_z += 0.5;
                            break;
                        case ROTATE_MODE_Y:
                            cube->angle_z += 0.5;
                            break;
                        case ROTATE_MODE_Z:
                            cube->angle_y -= 0.5;
                            break;
                        default:
                            break;
                    }
                    break;
                case MODE_TRANSLATE:
                    cube->pos_x -= 0.01;
                    break;
                default:
                    break;
            }
            break;

        case SDLK_UP:
            switch (state.mode) {
                case MODE_ROTATE:
                    switch (state.rotateMode % 3) {
                        case ROTATE_MODE_X:
                            cube->angle_y += 0.5;
                            break;
                        case ROTATE_MODE_Y:
                            cube->angle_x += 0.5;
                            break;
                        case ROTATE_MODE_Z:
                            cube->angle_x += 0.5;
                            break;
                        default:
                            break;
                    }
                    break;
                case MODE_SCALE:
                    cube->scale_x += 0.01;
                    cube->scale_y += 0.01;
                    cube->scale_z += 0.01;
                    break;
                case MODE_TRANSLATE:
                    switch (state.translateMode % 2) {
                        case TRANSLATE_MODE_Y:
                            cube->pos_y += 0.01;
                            break;
                        case TRANSLATE_MODE_Z:
                            cube->pos_z += 0.01;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;

        case SDLK_DOWN:
            switch (state.mode) {
                case MODE_ROTATE:
                    switch (state.rotateMode % 3) {
                        case ROTATE_MODE_X:
                            cube->angle_y -= 0.5;
                            break;
                        case ROTATE_MODE_Y:
                            cube->angle_x -= 0.5;
                            break;
                        case ROTATE_MODE_Z:
                            cube->angle_x -= 0.5;
                            break;
                        default:
                            break;
                    }
                    break;
                case MODE_SCALE:
                    cube->scale_x -= 0.01;
                    cube->scale_y -= 0.01;
                    cube->scale_z -= 0.01;
                    break;
                case MODE_TRANSLATE:
                    switch (state.translateMode % 2) {
                        case TRANSLATE_MODE_Y:
                            cube->pos_y -= 0.01;
                            break;
                        case TRANSLATE_MODE_Z:
                            cube->pos_z -= 0.01;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    updateCubeModel(cube);
}

void processStateAgainstCamera(ControlState state, SDL_Keycode key, Camera* camera) {
    switch (key) {
        case SDLK_RIGHT:
            switch (state.mode) {
                case MODE_ROTATE:
                    switch (state.rotateMode % 3) {
                        case ROTATE_MODE_X:
                            camera->angle_z += 0.5;
                            break;
                        case ROTATE_MODE_Y:
                            camera->angle_z += 0.5;
                            break;
                        case ROTATE_MODE_Z:
                            camera->angle_y += 0.5;
                            break;
                        default:
                            break;
                    }
                    break;
                case MODE_TRANSLATE:
                    camera->pos_x -= 0.1;
                    break;
                default:
                    break;
            }
            break;

        case SDLK_LEFT:
            switch (state.mode) {
                case MODE_ROTATE:
                    switch (state.rotateMode % 3) {
                        case ROTATE_MODE_X:
                            camera->angle_z -= 0.5;
                            break;
                        case ROTATE_MODE_Y:
                            camera->angle_z -= 0.5;
                            break;
                        case ROTATE_MODE_Z:
                            camera->angle_y -= 0.5;
                            break;
                        default:
                            break;
                    }
                    break;
                case MODE_TRANSLATE:
                    camera->pos_x += 0.1;
                    break;
                default:
                    break;
            }
            break;

        case SDLK_UP:
            switch (state.mode) {
                case MODE_ROTATE:
                    camera->angle_x += 0.5;
                    break;
                case MODE_SCALE:
                    camera->scale_x += 0.01;
                    camera->scale_y += 0.01;
                    camera->scale_z += 0.01;
                    break;
                case MODE_TRANSLATE:
                    switch (state.translateMode % 2) {
                        case TRANSLATE_MODE_Y:
                            camera->pos_y -= 0.1;
                            break;
                        case TRANSLATE_MODE_Z:
                            camera->pos_z -= 0.1;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;

        case SDLK_DOWN:
            switch (state.mode) {
                case MODE_ROTATE:
                    camera->angle_x -= 0.5;
                    break;
                case MODE_SCALE:
                    camera->scale_x -= 0.01;
                    camera->scale_y -= 0.01;
                    camera->scale_z -= 0.01;
                    break;
                case MODE_TRANSLATE:
                    switch (state.translateMode % 2) {
                        case TRANSLATE_MODE_Y:
                            camera->pos_y += 0.1;
                            break;
                        case TRANSLATE_MODE_Z:
                            camera->pos_z += 0.1;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    updateCameraView(camera);
}

void updateMatrixSamplerBuffer(unsigned int buffer, unsigned int texture, SDL_Surface* text, char update) {
    int textSize = text->h * text->pitch * text->format->BytesPerPixel;
    GLubyte* pixies = (GLubyte *)(text->pixels);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buffer);
    if (update) {
        glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, textSize, pixies);
    } else {
        glBufferData(GL_PIXEL_UNPACK_BUFFER, textSize, pixies, GL_STATIC_DRAW);
    }
    glPixelStorei(GL_UNPACK_ROW_LENGTH, text->pitch / text->format->BytesPerPixel);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text->w, text->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
}

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
    char* textFormatPresent;
    SDL_Color color = { 55, 55, 55 };

    // Open Window
    SDL_Window* window = SDL_CreateWindow("Eremeev: Matrix - 3D scene", 0, 0, 1024, 768, SDL_WINDOW_OPENGL);
    if (!window) {
        return -1;
    }

    ControlState state = { 0, 0, 0, 0 };
    f4matrix projection = f4matrix_perspectiveProjection(1024.0, 768.0, 55.0, 0.1, 100.0);
    Camera* camera = newCamera();
    Cube* cube = newCube();
    MeshPlane* plane = newMeshPlane();
    TextBlock* textBlock = newTextBlock(5.0, 12.0, 4.0, 8.0);
    TextBlock* cameraTextBlock = newTextBlock(-10.0, -3.0, 4.0, 8.0);
    TextBlock* modeTextBlock = newTextBlock(-2.0, 3.0, 7.0, 8.0);

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

    // Cube text block draw init
    unsigned int cube_tbVAO;
    glGenVertexArrays(1, &cube_tbVAO);
    glBindVertexArray(cube_tbVAO);

    unsigned int cube_tbVBO;
    glGenBuffers(1, &cube_tbVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cube_tbVBO);
    glBufferData(GL_ARRAY_BUFFER, textBlock->v_size, textBlock->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    unsigned int cube_tbVBO_uva;
    glGenBuffers(1, &cube_tbVBO_uva);
    glBindBuffer(GL_ARRAY_BUFFER, cube_tbVBO_uva);
    glBufferData(GL_ARRAY_BUFFER, textBlock->uva_size, textBlock->uva, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int cube_tbEBO;
    glGenBuffers(1, &cube_tbEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_tbEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, textBlock->i_size, textBlock->indices, GL_STATIC_DRAW);

    unsigned int textTexture;
    glGenTextures(1, &textTexture);

    textFormatPresent = f4matrix_toString(cube->model);
    text = TTF_RenderText_Blended_Wrapped( font, textFormatPresent, color, 380 );
    unsigned int cube_textPBO;
    glGenBuffers(1, &cube_textPBO);
    updateMatrixSamplerBuffer(cube_textPBO, textTexture, text, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    free(textFormatPresent);
    SDL_FreeSurface(text);

    // Camera text block draw init
    unsigned int camera_tbVAO;
    glGenVertexArrays(1, &camera_tbVAO);
    glBindVertexArray(camera_tbVAO);

    unsigned int camera_tbVBO;
    glGenBuffers(1, &camera_tbVBO);
    glBindBuffer(GL_ARRAY_BUFFER, camera_tbVBO);
    glBufferData(GL_ARRAY_BUFFER, cameraTextBlock->v_size, cameraTextBlock->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    unsigned int camera_tbVBO_uva;
    glGenBuffers(1, &camera_tbVBO_uva);
    glBindBuffer(GL_ARRAY_BUFFER, camera_tbVBO_uva);
    glBufferData(GL_ARRAY_BUFFER, cameraTextBlock->uva_size, cameraTextBlock->uva, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int camera_tbEBO;
    glGenBuffers(1, &camera_tbEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, camera_tbEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cameraTextBlock->i_size, cameraTextBlock->indices, GL_STATIC_DRAW);

    unsigned int camera_textTexture;
    glGenTextures(1, &camera_textTexture);

    textFormatPresent = f4matrix_toString(camera->view);
    text = TTF_RenderText_Blended_Wrapped( font, textFormatPresent, color, 380 );
    unsigned int camera_textPBO;
    glGenBuffers(1, &camera_textPBO);
    updateMatrixSamplerBuffer(camera_textPBO, camera_textTexture, text, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    free(textFormatPresent);
    SDL_FreeSurface(text);

    // Mode text block draw init
    unsigned int mode_tbVAO;
    glGenVertexArrays(1, &mode_tbVAO);
    glBindVertexArray(mode_tbVAO);

    unsigned int mode_tbVBO;
    glGenBuffers(1, &mode_tbVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mode_tbVBO);
    glBufferData(GL_ARRAY_BUFFER, modeTextBlock->v_size, modeTextBlock->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    unsigned int mode_tbVBO_uva;
    glGenBuffers(1, &mode_tbVBO_uva);
    glBindBuffer(GL_ARRAY_BUFFER, mode_tbVBO_uva);
    glBufferData(GL_ARRAY_BUFFER, modeTextBlock->uva_size, modeTextBlock->uva, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    unsigned int mode_tbEBO;
    glGenBuffers(1, &mode_tbEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mode_tbEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, modeTextBlock->i_size, modeTextBlock->indices, GL_STATIC_DRAW);

    unsigned int mode_textTexture;
    glGenTextures(1, &mode_textTexture);

    textFormatPresent = modeToString(state);
    text = TTF_RenderText_Blended_Wrapped( font, textFormatPresent, color, 380 );
    unsigned int mode_textPBO;
    glGenBuffers(1, &mode_textPBO);
    updateMatrixSamplerBuffer(mode_textPBO, mode_textTexture, text, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    free(textFormatPresent);
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
                    case SDLK_r:
                        state.mode = MODE_ROTATE;
                        state.rotateMode++;
                        break;
                    case SDLK_s:
                        state.mode = MODE_SCALE;
                        break;
                    case SDLK_t:
                        state.mode = MODE_TRANSLATE;
                        state.translateMode++;
                        break;
                    case SDLK_RIGHT:
                    case SDLK_LEFT:
                    case SDLK_UP:
                    case SDLK_DOWN:
                        if (state.objectMode % 2 == 0) {
                            processStateAgainstCube(state, event.key.keysym.sym, cube);
                        } else {
                            processStateAgainstCamera(state, event.key.keysym.sym, camera);
                        }
                        break;
                    case SDLK_o:
                        state.objectMode++;
                        break;
                    case SDLK_i:
                        resetCubeModel(cube);
                        resetCameraView(camera);
                        break;
                    // Other input here
                    default:
                        break;
                }
            } else if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        time++;
        if (time % 501 == 0) {
            textFormatPresent = f4matrix_toString(cube->model);
            text = TTF_RenderText_Blended_Wrapped( font, textFormatPresent, color, 380 );
            updateMatrixSamplerBuffer(cube_textPBO, textTexture, text, 1);
            free(textFormatPresent);
            SDL_FreeSurface(text);

            textFormatPresent = f4matrix_toString(camera->view);
            text = TTF_RenderText_Blended_Wrapped( font, textFormatPresent, color, 380 );
            updateMatrixSamplerBuffer(camera_textPBO, camera_textTexture, text, 1);
            free(textFormatPresent);
            SDL_FreeSurface(text);

            textFormatPresent = modeToString(state);
            text = TTF_RenderText_Blended_Wrapped( font, textFormatPresent, color, 380 );
            updateMatrixSamplerBuffer(mode_textPBO, mode_textTexture, text, 1);
            free(textFormatPresent);
            SDL_FreeSurface(text);

            time = 1;
        }


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // OpenGL rendering goes here
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        uniformMatrix(shaderProgram, "projection", projection);
        uniformMatrix(shaderProgram, "view", camera->view);
        uniformMatrix(shaderProgram, "model", cube->model);
        glDrawElements(GL_TRIANGLES, cube->i_count, GL_UNSIGNED_INT, 0);

        glUseProgram(planeShaderProgram);
        glBindVertexArray(planeVAO);
        uniformMatrix(planeShaderProgram, "projection", projection);
        uniformMatrix(planeShaderProgram, "view", camera->view);
        glDrawElements(GL_LINES, plane->i_count, GL_UNSIGNED_INT, 0);

        glUseProgram(textBlockShaderProgram);
        uniformMatrix(textBlockShaderProgram, "projection", projection);
        uniformMatrix(textBlockShaderProgram, "view", camera->view);
        uniformSampler2D(textBlockShaderProgram, "texture1", 0);
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, textTexture);
        glBindVertexArray(cube_tbVAO);
        glDrawElements(GL_TRIANGLES, textBlock->i_count, GL_UNSIGNED_INT, 0);

        glBindTexture(GL_TEXTURE_2D, camera_textTexture);
        glBindVertexArray(camera_tbVAO);
        glDrawElements(GL_TRIANGLES, cameraTextBlock->i_count, GL_UNSIGNED_INT, 0);

        glBindTexture(GL_TEXTURE_2D, mode_textTexture);
        glBindVertexArray(mode_tbVAO);
        glDrawElements(GL_TRIANGLES, modeTextBlock->i_count, GL_UNSIGNED_INT, 0);


        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();
    return 0;
}
