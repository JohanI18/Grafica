#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader_s.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>
#include <iostream>

using namespace std;
using namespace glm;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Variables globales
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

bool sunAuxCode = false;
float playerOrientation = 1;
float xPlayer = 0;
float crecimientoBoss = 0;
float rotationBackground = 0;

int main()
{
    //Inicializacion OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Daniel Velin 1600787855", NULL, NULL);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
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

    //Shader Program
    Shader ourShader("shaders/vertexshaderB2T2.vs", "shaders/fragmentshaderB2T2.fs");

    float vertices[] = {
        // Position          // Texture
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  
    };
    unsigned int indices[] = {
        0, 1, 3, 
        1, 2, 3  
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Lectura de datos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Activacion canal Alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Carga de texturas
    unsigned int textures[6];
    const char *texturePaths[6] = {"textures/cheems1.png", 
                                   "textures/cheems2.png", 
                                   "textures/sol.png", 
                                   "textures/solRojo.png" , 
                                   "textures/dogeCoin.png",
                                   "textures/campo.png"
                                    };


    int width, height, nrChannels;
    for (int i = 0; i < 5; i++) {
        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        // Wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Filtering 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(texturePaths[i], &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    glGenTextures(1, &textures[5]);
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    // Wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Filtering 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePaths[5], &width, &height, &nrChannels, 0);
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

    //Activacion Shader Program
    ourShader.use(); 
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    ourShader.setInt("texture3", 2);
    ourShader.setInt("texture4", 3);
    ourShader.setInt("texture5", 4);
    ourShader.setInt("texture6", 5);


    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        float a = 0;
        // input
        processInput(window);

        //Limpieza de color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind de textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, textures[3]);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, textures[5]);


        //Campo
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glm::mat4 transform = glm::mat4(1.0f); 
        transform = scale(transform, vec3(2.0f, 2.0f, 0.0f));
        transform = glm::rotate(transform, rotationBackground, glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setFloat("codeT", 5);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        //Boss
        transform = glm::mat4(1.0f);
        transform = glm::scale(transform, glm::vec3(-0.6f - crecimientoBoss, 0.6f + crecimientoBoss, 0.0f));
        transform = glm::translate(transform, glm::vec3(-0.9f + crecimientoBoss * 1.2f, -1.0f + crecimientoBoss * 1.1f, 0.0f));
        ourShader.setFloat("codeT", 0);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Player
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(-0.8f + xPlayer, -0.8f, 0.0f));
        transform = glm::scale(transform, glm::vec3(playerOrientation * 0.3f, 0.3f, 0.3f));
        ourShader.setFloat("codeT", 1);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        if (xPlayer > 0.45) {
            crecimientoBoss = xPlayer - 0.45;
        }
        else {
            crecimientoBoss = 0;
        }


        //SOLES
        int sunOrientation = 1;
        for (int i = 0; i < 2; i++) {
            transform = glm::mat4(1.0f); 
            transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
            transform = glm::translate(transform, glm::vec3(sunOrientation * 1.0f, 0.8f, 0.0f));
            transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
            transform = glm::translate(transform, glm::vec3(0.3f * sunOrientation, 0.3f * sunOrientation, 0.0f));

            if (!sunAuxCode) {
                ourShader.setFloat("codeT", 2 + i);
            }
            else if(sunAuxCode && i == 0){
                ourShader.setFloat("codeT", 3);
            }
            else if (sunAuxCode && i == 1) {
                ourShader.setFloat("codeT", 2);
            }
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            sunOrientation = -sunOrientation;
        }

        //DogeCoin
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.1f, -0.85f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime() * 2, glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::scale(transform, glm::vec3(0.3f, 0.2f, 0.0f));
        ourShader.setFloat("codeT", 4);
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        //Ejecucion operaciones en la cola
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Liberacion de recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

//Procesamiento entrada de teclado
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_J) == GLFW_RELEASE) {
        sunAuxCode = !sunAuxCode;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (xPlayer >= -0.15) {
            xPlayer -= 0.0002f;
        }
        playerOrientation = 1;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (xPlayer < 0.70) {
            xPlayer += 0.0002f;
        }
        playerOrientation = -1;
    }
    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
        rotationBackground -= 0.1f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE) {
        rotationBackground += 0.1f;
    }

}

//Reajuste de pantalla
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}