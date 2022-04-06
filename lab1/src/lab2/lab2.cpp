#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y - 0.5f, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.4f, 0.2f, 0.6f, 1.0f);\n"
    "}\n\0";
// ---------------------------------------------------------------------
const char *vertexShaderSource1 = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x - 0.5f, aPos.y + 0.3f, aPos.z, 1.0);\n"
    "}\0";
    const char *fragmentShaderSource1 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";
// ---------------------------------------------------------------------
const char *vertexShaderSource2 = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x + 0.5f, aPos.y + 0.3f, aPos.z, 1.0);\n"
    "}\0";
    const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.0f, 1.0f);\n"
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
    // ---------------------------------------------------------------
    unsigned int vertexShader1;
    vertexShader1 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader1, 1, &vertexShaderSource1, NULL);
    glCompileShader(vertexShader1);

    unsigned int fragmentShader1;
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);
    // ---------------------------------------------------------------
    unsigned int vertexShader2;
    vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader2, 1, &vertexShaderSource2, NULL);
    glCompileShader(vertexShader2);

    unsigned int fragmentShader2;
    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    // linking shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    unsigned int shaderProgram1;
    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader1);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);

    unsigned int shaderProgram2;
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader2);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

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

        4, 5, 7,
        5, 6, 7,
    // ----------
        0, 8, 9,
        8, 10, 0,

        11, 12, 7,
        12, 13, 7,
    // ------------
        14, 15, 16,
        15, 17, 16,

        18, 19, 20,
        19, 21, 20,
    // -------------   
        8, 22, 23,
        8, 24, 23,
        24, 14, 8,
        8, 14, 25,
        24, 15, 9,

        12, 26, 27,
        12, 28, 26,
        28, 18, 26,
        26, 18, 29,
        11, 28, 19,
    // -------------
        15, 30, 31,
        30, 32, 31,

        19, 33, 34,
        33, 35, 34
    };

    float vertices1[] = {
        0.3f, 0.3f, 0.0f,  // top right
        0.3f, -0.3f, 0.0f, // bottom right
        -0.3f, -0.3f, 0.0f, // bottom left
        -0.3f, 0.3f, 0.0f // top left
        
    };
    unsigned int indices1[] = { // note that we start from 0!
        0, 1, 3,
        1, 2, 3
    };

    float vertices2[15];
    float angle = 360.0f / 5.0f;
    angle *= M_PI / 180.0f;
    float start = M_PI_2;

    for(int i = 0; i < 15; i+=3) {
        vertices2[i] = 0.3f * cos(start);
        vertices2[i+1] = 0.3f * sin(start);
        vertices2[i+2] = 0.0f;

        start += angle;
    }

    unsigned int VAO[3];
    unsigned int VBO[3];
    unsigned int EBO[2];

    glGenVertexArrays(3, VAO);
    glGenBuffers(3, VBO);
    glGenBuffers(2, EBO);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
// ------------------------------------------------------------------------------------
    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
// ------------------------------------------------------------------------------------
    glBindVertexArray(VAO[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // swap buffers

        glBindVertexArray(VAO[0]);

        glUseProgram(shaderProgram);
        glDrawElements(GL_TRIANGLES, 78, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO[1]);

        glUseProgram(shaderProgram1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO[2]);

        glUseProgram(shaderProgram2);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 5);

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}