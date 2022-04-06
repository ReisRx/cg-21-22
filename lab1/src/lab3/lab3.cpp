#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void moveRObject(GLFWwindow *window, int vertexRLocation);

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

float countX = 0.0f;
float countY = 0.0f;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform vec4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform + vec4(aPos.x + 0.4f, aPos.y, aPos.z, 1.5f);\n" // vec4(aPos.x, aPos.y, aPos.z, 1.0)
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.4f, 0.2f, 0.6f, 1.0f);\n"
    "}\n\0";

// ---------------------------------------------------------------------

const char *vertexShaderSourceR = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform vec4 transform;\n"
    "void main()\n"
    "{\n"
    " gl_Position = transform + vec4(aPos.x + 0.4f, aPos.y, aPos.z, 1.0f);\n"
    "}\0";
const char *fragmentShaderSourceR = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 r2Color;\n"
    "void main()\n"
    "{\n"
    "   FragColor = r2Color;\n"
    "}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL 68039", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // shaders
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int vertexShaderR;
    vertexShaderR = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderR, 1, &vertexShaderSourceR, NULL);
    glCompileShader(vertexShaderR);

    unsigned int fragmentShaderR;
    fragmentShaderR = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderR, 1, &fragmentShaderSourceR, NULL);
    glCompileShader(fragmentShaderR);

    // linking shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    unsigned int shaderProgramR;
    shaderProgramR = glCreateProgram();
    glAttachShader(shaderProgramR, vertexShaderR);
    glAttachShader(shaderProgramR, fragmentShaderR);
    glLinkProgram(shaderProgramR);

    // vertex data
    float vertices[] = {
        -0.6f, 0.4f, 0.0f, // 0
        -0.6f, -0.4f, 0.0f, //1
        -0.7f, -0.4f, 0.0f, //2
        -0.7f, 0.4f, 0.0f, // 3

        0.1f, 0.4f, 0.0f, //  4
        0.1f, -0.4f, 0.0f, // 5
        0.2f, -0.4f, 0.0f, // 6
        0.2f, 0.4f, 0.0f, //  7
    // -------------------------------
        -0.2f, 0.3f, 0.0f, // 8
        -0.3f, 0.4f, 0.0f, // 9
        -0.6f, 0.3f, 0.0f, // 10

        0.5f, 0.4f, 0.0f, // 11
        0.6f, 0.3f, 0.0f, // 12
        0.2f, 0.3f, 0.0f, // 13
    // -------------------------------
        -0.2f, 0.1f, 0.0f, // 14 
        -0.3f, 0.0f, 0.0f, // 15
        -0.6f, 0.1f, 0.0f, // 16
        -0.6f, 0.0f, 0.0f, // 17

        0.6f, 0.1f, 0.0f, //  18
        0.5f, 0.0f, 0.0f, //  19
        0.2f, 0.1f, 0.0f, //  20
        0.2f, 0.0f, 0.0f, //  21
    // -------------------------------
        -0.25f, 0.2f, 0.0f,  // 22
        -0.35f, 0.3f, 0.0f,  // 23
        -0.175f, 0.2f, 0.0f,   // 24
        -0.35f, 0.1f, 0.0f,   // 25

        0.55f, 0.2f, 0.0f,  // 26
        0.45f, 0.3f, 0.0f,  // 27
        0.625f, 0.2f, 0.0f,   // 28
        0.45f, 0.1f, 0.0f,   // 29
    // ------------------------------
        -0.1f, -0.4f, 0.0f,  // 30
        -0.4f, 0.0f, 0.0f,   // 31
        -0.2f, -0.4f, 0.0f,  // 32

        0.7f, -0.4f, 0.0f,// 33
        0.4f, 0.0f, 0.0f,// 34
        0.6f, -0.4f, 0.0f// 35
    };
    unsigned int indices[] = { // note that we start from 0!
        0, 1, 3,
        1, 2, 3,

        // 4, 5, 7,
        // 5, 6, 7,
    // ----------
        0, 8, 9,
        8, 10, 0,

        // 11, 12, 7,
        // 12, 13, 7,
    // ------------
        14, 15, 16,
        15, 17, 16,

        // 18, 19, 20,
        // 19, 21, 20,
    // -------------   
        8, 22, 23,
        8, 24, 23,
        24, 14, 8,
        8, 14, 25,
        24, 15, 9,

        // 12, 26, 27,
        // 12, 28, 26,
        // 28, 18, 26,
        // 26, 18, 29,
        // 11, 28, 19,
    // -------------
        15, 30, 31,
        30, 32, 31,

        // 19, 33, 34,
        // 33, 35, 34
    };

    unsigned int VAO[2];
    unsigned int VBO[2];
    unsigned int EBO[2];

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
  
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // swap buffers

        glBindVertexArray(VAO[0]);

        float timeValue = glfwGetTime();
        int vertexLocation = glGetUniformLocation(shaderProgram, "transform");
        glUseProgram(shaderProgram);
        glUniform4f(vertexLocation, -cos(timeValue * 2.5f), sin(timeValue * 2.5f), 0.0f, 0.0f);
        glDrawElements(GL_TRIANGLES, 39, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO[1]);
        float colorValue = (sin(timeValue * 5) / 2.0f) + 0.5f;
        int vertexRColorLocation = glGetUniformLocation(shaderProgramR, "r2Color");
        int vertexRLocation = glGetUniformLocation(shaderProgramR, "transform");
        glUseProgram(shaderProgramR);
        moveRObject(window, vertexRLocation);
        glUniform4f(vertexRColorLocation, colorValue, colorValue, colorValue, 1.0f);

        glDrawElements(GL_TRIANGLES, 39, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void moveRObject(GLFWwindow *window, int vertexRLocation) {
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { 
        if(countY < 0.6f)
            countY += 0.0003f;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { 
        if(countY > -0.6f)
            countY += -0.0003f;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { 
        if(countX > -0.7f)
            countX += -0.0003f;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { 
        if(countX < 0.7f)
            countX += 0.0003f;
    }
    glUniform4f(vertexRLocation, countX, countY, 0.0f, 0.0f);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}