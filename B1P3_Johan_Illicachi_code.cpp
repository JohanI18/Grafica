#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B1P3 CI:1600877458 Johan Illicachi", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program

    Shader ourShader("shaders/shader_B1P3.vs", "shaders/shader_B1P3.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
       -0.58f,  0.63f, 0.00f,   1.0f, 0.4f, 0.4f,//A
       -0.58f,  0.20f, 0.00f,   1.0f, 0.4f, 0.4f,//B
       -0.79f,  0.41f, 0.00f,   1.0f, 0.4f, 0.4f,//C

       -0.58f,  0.63f, 0.00f,   1.0f, 0.4f, 0.4f,//A
       -0.58f,  0.20f, 0.00f,   1.0f, 0.4f, 0.4f,//B
       -0.37f,  0.41f, 0.00f,   1.0f, 0.4f, 0.4f,//D

       -0.58f,  0.20f, 0.00f,   0.2f, 0.8f, 0.4f,//B
        0.01f,  0.20f, 0.00f,   0.2f, 0.8f, 0.4f,//F
       -0.29f, -0.10f, 0.00f,   0.2f, 0.8f, 0.4f,//R

        0.01f,  0.20f, 0.00f,   0.2f, 0.6f, 1.0f,//F
       -0.20f,  0.41f, 0.00f,   0.2f, 0.6f, 1.0f,//G
        0.22f,  0.41f, 0.00f,   0.2f, 0.6f, 1.0f,//H

       -0.58f,  0.20f, 0.00f,   0.9f, 0.8f, 0.2f,//B
       -0.58f, -0.65f, 0.00f,   0.9f, 0.8f, 0.2f,//E
       -0.16f, -0.23f, 0.00f,   0.9f, 0.8f, 0.2f,//J

       -0.58f, -0.65f, 0.00f,   0.4f, 0.5f, 0.7f,//E
       -0.35f, -0.42f, 0.00f,   0.4f, 0.5f, 0.7f,//K
       -0.20f, -0.65f, 0.00f,   0.4f, 0.5f, 0.7f,//N

       -0.35f, -0.42f, 0.00f,   0.4f, 0.5f, 0.7f,//K
       -0.20f, -0.65f, 0.00f,   0.4f, 0.5f, 0.7f,//N
        0.03f, -0.42f, 0.00f,   0.4f, 0.5f, 0.7f,//O

       -0.35f, -0.42f, 0.00f,   0.2f, 0.8f, 0.4f,//K
        0.50f, -0.42f, 0.00f,   0.2f, 0.8f, 0.4f,//L
        0.07f,  0.00f, 0.00f,   0.2f, 0.8f, 0.4f,//I

        0.76f, -0.42f, 0.00f,   1.0f, 0.6f, 0.2f,//P
        0.55f, -0.65f, 0.00f,   1.0f, 0.6f, 0.2f,//Q
        0.35f, -0.42f, 0.00f,   1.0f, 0.6f, 0.2f,//M
    };

    // Habilito buffers

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    // Copia y guarda en el VBO y en la GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Leyendo los atributos hacia donde tiene que enviar (location 0)
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render loop

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        const double timeValue = glfwGetTime();

        // render the triangles
        ourShader.use();

        ourShader.setFloat("time", timeValue);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 27);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}