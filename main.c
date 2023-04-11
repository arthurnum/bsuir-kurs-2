#include "SDL.h"
#include "SDL_ttf.h"
// #include "SDL2/SDL_opengl.h"
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
// #include <OpenGL/glext.h>
#include "stdlib.h"

#include "cube.h"
#include "matrix.h"
#include "mesh_plane.h"
#include "text_block.h"

int main (int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    if ( TTF_Init() < 0 ) {
		return -1;
	}



    f4matrix projection = f4matrix_perspectiveProjection(1024.0, 768.0, 55.0, 0.1, 100.0);
    f4matrix camera = f4matrix_camera();

    // Open Window
    SDL_Window* window = SDL_CreateWindow("Eremeev: Matrix - 3D scene", 0, 0, 1024, 768, SDL_WINDOW_OPENGL);
    if (!window) {
        return -1;
    }


    TTF_Font* font;
    font = TTF_OpenFont("inconsolata.otf", 24);
    SDL_Surface* text;
    // Set color to black
    SDL_Color color = { 55, 55, 55 };
    char* matrixPresent = malloc(512);
    sprintf(
        matrixPresent,
        "%5.2f %5.2f %5.2f %5.2f\n"
        "%5.2f %5.2f %5.2f %5.2f\n"
        "%5.2f %5.2f %5.2f %5.2f\n"
        "%5.2f %5.2f %5.2f %5.2f",
        projection[0],
        projection[1],
        projection[2],
        projection[3],
        projection[4],
        projection[5],
        projection[6],
        projection[7],
        projection[8],
        projection[9],
        projection[10],
        projection[11],
        projection[12],
        projection[13],
        projection[14],
        projection[15]
    );
    text = TTF_RenderText_Blended_Wrapped( font, matrixPresent, color, 380 );
    int textSize = text->h * text->pitch * text->format->BytesPerPixel;
    GLubyte *pixies = (GLubyte *)(text->pixels);




    // OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    // Create OpenGL context
    SDL_GLContext Context = SDL_GL_CreateContext(window);

    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aNormal;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "uniform mat4 model;\n"
        "out vec4 normal;\n"
        "void main()\n"
        "{\n"
        "   normal = model * vec4(aNormal, 1.0);\n"
        "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
        "}\n\0";
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
    };

    const char *fragmentShaderSource = "#version 330 core\n"
        "in vec4 normal;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   float cosTheta = clamp( dot( normal, normalize(vec4(-5.0, 10.0, -10.0, 1.0)) ), 0.5, 1.0);\n"
        "   vec3 result = vec3(0.8, 0.8, 0.8) * cosTheta;\n"
        "   FragColor = vec4(result, 1.0);\n"
        "}\n\0";
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infoLog);
    };

    const char *planeVertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * mat4(1.0) * vec4(aPos, 1.0);\n"
        "}\n\0";
    unsigned int planeVertexShader;
    planeVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(planeVertexShader, 1, &planeVertexShaderSource, NULL);
    glCompileShader(planeVertexShader);

    glGetShaderiv(planeVertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(planeVertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
    };

    const char *planeFragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.75, 0.75, 1.0, 1.0);\n"
        "}\n\0";
    unsigned int planeFragmentShader;
    planeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(planeFragmentShader, 1, &planeFragmentShaderSource, NULL);
    glCompileShader(planeFragmentShader);

    glGetShaderiv(planeFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(planeFragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infoLog);
    };

    // Text BLOCK -----------------
    const char *textBlockVertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 uva;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "out vec2 uvaPos;\n"
        "void main()\n"
        "{\n"
        "   uvaPos = uva;"
        "   gl_Position = projection * vec4(aPos, 1.0);\n"
        "}\n\0";
    unsigned int textBlockVertexShader;
    textBlockVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(textBlockVertexShader, 1, &textBlockVertexShaderSource, NULL);
    glCompileShader(textBlockVertexShader);

    glGetShaderiv(textBlockVertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(textBlockVertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
    };

    const char *textBlockFragmentShaderSource = "#version 330 core\n"
        "uniform sampler2D texture1;\n"
        "in vec2 uvaPos;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = texture(texture1, uvaPos);\n"
        "}\n\0";
    unsigned int textBlockFragmentShader;
    textBlockFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(textBlockFragmentShader, 1, &textBlockFragmentShaderSource, NULL);
    glCompileShader(textBlockFragmentShader);

    glGetShaderiv(textBlockFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(textBlockFragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infoLog);
    };
    // ----------------------------

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    unsigned int planeShaderProgram;
    planeShaderProgram = glCreateProgram();
    glAttachShader(planeShaderProgram, planeVertexShader);
    glAttachShader(planeShaderProgram, planeFragmentShader);
    glLinkProgram(planeShaderProgram);

    unsigned int textBlockShaderProgram;
    textBlockShaderProgram = glCreateProgram();
    glAttachShader(textBlockShaderProgram, textBlockVertexShader);
    glAttachShader(textBlockShaderProgram, textBlockFragmentShader);
    glLinkProgram(textBlockShaderProgram);

    Cube* cube = newCube();

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



    MeshPlane* plane = newMeshPlane();

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


    TextBlock* textBlock = newTextBlock();

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

    unsigned int textPBO;
    glGenBuffers(1, &textPBO);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, textPBO);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, textSize, pixies, GL_STATIC_DRAW);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, text->pitch / text->format->BytesPerPixel);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text->w, text->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



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




        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // OpenGL rendering goes here
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        int modelLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, projection);
        int modelLoc2 = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(modelLoc2, 1, GL_TRUE, camera);
        int modelLoc3 = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc3, 1, GL_TRUE, cube->model);

        glDrawElements(GL_TRIANGLES, cube->i_count, GL_UNSIGNED_INT, 0);

        glUseProgram(planeShaderProgram);
        glBindVertexArray(planeVAO);

        modelLoc = glGetUniformLocation(planeShaderProgram, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, projection);
        modelLoc2 = glGetUniformLocation(planeShaderProgram, "view");
        glUniformMatrix4fv(modelLoc2, 1, GL_TRUE, camera);

        glDrawElements(GL_LINES, plane->i_count, GL_UNSIGNED_INT, 0);



        glUseProgram(textBlockShaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textTexture);

        glBindVertexArray(tbVAO);

        modelLoc = glGetUniformLocation(textBlockShaderProgram, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_TRUE, projection);
        modelLoc2 = glGetUniformLocation(textBlockShaderProgram, "view");
        glUniformMatrix4fv(modelLoc2, 1, GL_TRUE, camera);
        int modelLoc4 = glGetUniformLocation(textBlockShaderProgram, "texture1");
        glUniform1i(modelLoc4, 0);


        glDrawElements(GL_TRIANGLES, textBlock->i_count, GL_UNSIGNED_INT, 0);

         if (time % 100 == 0) {
            sprintf(
                matrixPresent,
                "%5.2f %5.2f %5.2f %5.2f\n"
                "%5.2f %5.2f %5.2f %5.2f\n"
                "%5.2f %5.2f %5.2f %5.2f\n"
                "%5.2f %5.2f %5.2f %5.2f",
                cube->model[0],
                cube->model[1],
                cube->model[2],
                cube->model[3],
                cube->model[4],
                cube->model[5],
                cube->model[6],
                cube->model[7],
                cube->model[8],
                cube->model[9],
                cube->model[10],
                cube->model[11],
                cube->model[12],
                cube->model[13],
                cube->model[14],
                cube->model[15]
            );
            text = TTF_RenderText_Blended_Wrapped( font, matrixPresent, color, 380 );
            textSize = text->h * text->pitch * text->format->BytesPerPixel;
            pixies = (GLubyte *)(text->pixels);
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, textPBO);
            glBufferSubData(GL_PIXEL_UNPACK_BUFFER, 0, textSize, pixies);
            // glPixelStorei(GL_UNPACK_ROW_LENGTH, text->pitch / text->format->BytesPerPixel);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text->w, text->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
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

        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();
    return 0;
}
