#define STB_IMAGE_IMPLEMENTATION 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_s.h>
#include <learnopengl/stb_image.h>
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

    //Linea de codigo si se trabaja con MacOs
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B1T5 CI:1600877458 Johan Illicachi", NULL, NULL);
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

    Shader ourShader("shaders/vertexshader.vs", "shaders/fragmentshader.fs");

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

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //set the factor for the visibility
    float visibility = 0.0f;

    unsigned int texture1, texture2;
    
    // Load texture1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // Wrapping Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load("textures/texture1.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // Load texture2

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // Wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("textures/texture2.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //Program Activation
    ourShader.use();
    // Set the vars
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    //Render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // change visibility
        float timeValue = glfwGetTime();
        visibility = sin(timeValue);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Activate and bind the textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        
        float scale = sin(glfwGetTime());
        transform = glm::translate(transform, glm::vec3(scale, 0.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(scale, scale, scale));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        // render all
        ourShader.use();
        ourShader.setFloat("visible", visibility);
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

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