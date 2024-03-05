#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Screen dimensions

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";


int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Johan Illicachi CI:1600877458", NULL, NULL);
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

    // Compile vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Compile fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders into a shader program
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float Points[] = {
        -0.58f,  0.53f, 0.00f, //A
        -0.58f,  0.20f, 0.00f, //B
        -0.79f,  0.41f, 0.00f, //C
        -0.37f,  0.41f, 0.00f, //D
        -0.58f, -0.65f, 0.00f, //E
         0.01f,  0.20f, 0.00f, //F
        -0.20f,  0.41f, 0.00f, //G
         0.22f,  0.41f, 0.00f, //H
         0.07f,  0.00f, 0.00f, //I
        -0.16f, -0.23f, 0.00f, //J
        -0.35f, -0.42f, 0.00f, //K
         0.50f, -0.42f, 0.00f, //L
         0.76f, -0.42f, 0.00f, //M
        -0.20f, -0.65f, 0.00f, //N
         0.03f, -0.42f, 0.00f, //O
         0.55f, -0.65f, 0.00f, //P
        -0.35f, -0.42f, 0.00f, //Q
        -0.29f, -0.10f, 0.00f, //R
        
    };

    //Define the vertices of the triangles.
    float Triangle1[] = {
        //Triangle1
        -0.79f,  0.41f, 0.00f,
        -0.58f,  0.63f, 0.00f,
        -0.58f,  0.20f, 0.00f,
        -0.37f,  0.41f, 0.00f,
    };

    float Triangle2[] = {
        //Triangle3
        -0.58f, -0.65f, 0.0f, // V1
        -0.58f, 0.20f, 0.0f, // V2
        -0.16f, -0.23f, 0.0f, // V3
        //Triangle4
        -0.58f, 0.20f, 0.0f, // V1
        -0.29f, -0.09f, 0.0f, // V2
         0.01f, 0.20f, 0.0f  // V3
    };

    float Triangle3[] = {
        //Triangle5
         0.5f,  0.5f, 0.0f, // V1
         0.5f, -0.5f, 0.0f, // V2
         0.7f,  0.0f, 0.0f, // V3
        //Triangle6
        -0.5f, -0.5f, 0.0f, // V1
        -0.5f,  0.5f, 0.0f, // V2
        -0.7f,  0.0f, 0.0f  // V3
    };

    // Set up vertex data and buffers
    unsigned int VBOs[3], VAOs[3];
    glGenVertexArrays(3, VAOs);
    glGenBuffers(3, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle1), Triangle1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ---------------------

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle2), Triangle2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // ---------------------

    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle3), Triangle3, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader program
        glUseProgram(shaderProgram);

        glBindVertexArray(VAOs[0]);
        //Draw T1
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Draw T2
        glDrawArrays(GL_TRIANGLES, 1, 4);

        glBindVertexArray(VAOs[1]);
        //Draw T3
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Draw T4
        glDrawArrays(GL_TRIANGLES, 3, 3);

        glBindVertexArray(VAOs[2]);
        //Draw T1
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Draw T1
        glDrawArrays(GL_TRIANGLES, 3, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(3, VAOs);
    glDeleteBuffers(3, VBOs);

    glfwTerminate();
    return 0;
}

// Function to handle input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Callback function for framebuffer size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}