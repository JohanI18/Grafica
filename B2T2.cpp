#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float tiempo = 0;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Johan Illicachi, CI:1600877458", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);


    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("shaders/B2T3_materials.vs", "shaders/B2T3_materials.fs");
    Shader lightCubeShader("shaders/shader_exercise13_lightcube.vs", "shaders/shader_exercise13_lightcube.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
    //PERSONAJES
        //Cara1
            // positions          // texture coords
        -0.5f, -0.5f, -0.5f,  0.551f, 0.921f,
         0.5f, -0.5f, -0.5f,  0.728f, 0.921f,
         0.5f,  0.5f, -0.5f,  0.728f, 0.675f,
         0.5f,  0.5f, -0.5f,  0.728f, 0.675f,
        -0.5f,  0.5f, -0.5f,  0.551f, 0.675f,
        -0.5f, -0.5f, -0.5f,  0.551f, 0.921f,

        //Cara2
        -0.5f, -0.5f,  0.5f,  0.551f, 0.258f,
         0.5f, -0.5f,  0.5f,  0.728f, 0.258f,
         0.5f,  0.5f,  0.5f,  0.728f, 0.506f,
         0.5f,  0.5f,  0.5f,  0.728f, 0.506f,
        -0.5f,  0.5f,  0.5f,  0.551f, 0.506f,
        -0.5f, -0.5f,  0.5f,  0.551f, 0.258f,

        //Cara3
        -0.5f,  0.5f,  0.5f,  0.532f, 0.500f,
        -0.5f,  0.5f, -0.5f,  0.532f, 0.674f,
        -0.5f, -0.5f, -0.5f,  0.338f, 0.674f,
        -0.5f, -0.5f, -0.5f,  0.338f, 0.674f,
        -0.5f, -0.5f,  0.5f,  0.338f, 0.500f,
        -0.5f,  0.5f,  0.5f,  0.532f, 0.500f,

        //Cara4
         0.5f,  0.5f,  0.5f,  0.730f, 0.500f,
         0.5f,  0.5f, -0.5f,  0.730f, 0.674f,
         0.5f, -0.5f, -0.5f,  0.924f, 0.674f,
         0.5f, -0.5f, -0.5f,  0.924f, 0.674f,
         0.5f, -0.5f,  0.5f,  0.924f, 0.500f,
         0.5f,  0.5f,  0.5f,  0.730f, 0.500f,

         //Cara5
         -0.5f, -0.5f, -0.5f,  0.338f, 0.660f,
          0.5f, -0.5f, -0.5f,  0.143f, 0.660f,
          0.5f, -0.5f,  0.5f,  0.143f, 0.506f,
          0.5f, -0.5f,  0.5f,  0.143f, 0.506f,
         -0.5f, -0.5f,  0.5f,  0.338f, 0.506f,
         -0.5f, -0.5f, -0.5f,  0.338f, 0.660f,

         //Cara6
         -0.5f,  0.5f, -0.5f,  0.532f, 0.660f,
          0.5f,  0.5f, -0.5f,  0.721f, 0.660f,
          0.5f,  0.5f,  0.5f,  0.721f, 0.506f,
          0.5f,  0.5f,  0.5f,  0.721f, 0.506f,
         -0.5f,  0.5f,  0.5f,  0.532f, 0.506f,
         -0.5f,  0.5f, -0.5f,  0.532f, 0.660f,
    //BLOQUES
        //Cara1
            // positions          // texture coords
        -0.5f, -0.5f, -0.5f,  0.298f, 0.836f,
         0.5f, -0.5f, -0.5f,  0.502f, 0.836f,
         0.5f,  0.5f, -0.5f,  0.502f, 0.580f,
         0.5f,  0.5f, -0.5f,  0.502f, 0.580f,
        -0.5f,  0.5f, -0.5f,  0.298f, 0.580f,
        -0.5f, -0.5f, -0.5f,  0.298f, 0.836f,

        //Cara2
        -0.5f, -0.5f,  0.5f,  0.298f, 0.070f,
         0.5f, -0.5f,  0.5f,  0.508f, 0.070f,
         0.5f,  0.5f,  0.5f,  0.508f, 0.324f,
         0.5f,  0.5f,  0.5f,  0.508f, 0.324f,
        -0.5f,  0.5f,  0.5f,  0.298f, 0.324f,
        -0.5f, -0.5f,  0.5f,  0.298f, 0.070f,

        //Cara3
        -0.5f,  0.5f,  0.5f,  0.298f, 0.327f,
        -0.5f,  0.5f, -0.5f,  0.298f, 0.580f,
        -0.5f, -0.5f, -0.5f,  0.085f, 0.580f,
        -0.5f, -0.5f, -0.5f,  0.085f, 0.580f,
        -0.5f, -0.5f,  0.5f,  0.085f, 0.327f,
        -0.5f,  0.5f,  0.5f,  0.298f, 0.327f,

        //Cara4
         0.5f,  0.5f,  0.5f,  0.510f, 0.327f,
         0.5f,  0.5f, -0.5f,  0.510f, 0.580f,
         0.5f, -0.5f, -0.5f,  0.720f, 0.580f,
         0.5f, -0.5f, -0.5f,  0.720f, 0.580f,
         0.5f, -0.5f,  0.5f,  0.720f, 0.327f,
         0.5f,  0.5f,  0.5f,  0.510f, 0.327f,

        //Cara5
        -0.5f, -0.5f, -0.5f,  0.933f, 0.580f,
         0.5f, -0.5f, -0.5f,  0.722f, 0.580f,
         0.5f, -0.5f,  0.5f,  0.722f, 0.327f,
         0.5f, -0.5f,  0.5f,  0.722f, 0.327f,
        -0.5f, -0.5f,  0.5f,  0.933f, 0.327f,
        -0.5f, -0.5f, -0.5f,  0.933f, 0.580f,

        //Cara6
         -0.5f,  0.5f, -0.5f,  0.298f, 0.580f,
          0.5f,  0.5f, -0.5f,  0.508f, 0.580f,
          0.5f,  0.5f,  0.5f,  0.508f, 0.324f,
          0.5f,  0.5f,  0.5f,  0.508f, 0.324f,
         -0.5f,  0.5f,  0.5f,  0.298f, 0.324f,
         -0.5f,  0.5f, -0.5f,  0.298f, 0.580f,
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        //PERSONAJE
        glm::vec3(0.0f,  0.0f,  -1.0f),
        glm::vec3(0.0f,  0.0f,  -10.0f),

        //BLOQUES
        glm::vec3(2.0f,  2.0f, -6.0f),
        glm::vec3(-2.0f,  2.0f, -6.0f),
        glm::vec3(-2.0f,  -2.0f, -6.0f),
        glm::vec3(2.0f,  -2.0f, -6.0f),
        glm::vec3(4.0f,  0.0f, -6.0f),
        glm::vec3(-4.0f, 0.0f, -6.0f),
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
 
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // load and create a texture 
    // -------------------------
    unsigned int texture1, texture2, texture3, texture4;

    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("textures/Texture8.png", &width, &height, &nrChannels, 0);    if (data)
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/Texturegrass.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture 3
   // ---------
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/TextureA.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);

    // texture 4
   // ---------
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("textures/TextureC.png", &width, &height, &nrChannels, 0);
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
    stbi_image_free(data);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    lightingShader.use(); 
      
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
       // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Time vars
        tiempo = glfwGetTime();
        float movimiento = sin(tiempo);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, texture4);
        glActiveTexture(GL_TEXTURE4);

        // activate shader
        lightingShader.use();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		lightingShader.setMat4("projection", projection);
		 // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("view", view);
        // render boxes
        glBindVertexArray(VAO);
        
        //PERSONAJE
        for (unsigned int i = 0; i < 2; i++)
        {
            lightingShader.setInt("selector", 1);
            lightingShader.setInt("texture1", 0);
            glm::mat4 model = glm::mat4(1.0f);
            
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(180.0f), glm::vec3(movimiento, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            lightingShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //Bloquesgrass
        lightingShader.setInt("selector", 2);
        lightingShader.setInt("texture2", 1);
        for (unsigned int i =  2; i < 4; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(tiempo * 100), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(tiempo * 100), glm::vec3(1.0f, 0.0f, 1.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            lightingShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 36, 72);
        }
        //Bloquesamatista
        lightingShader.setInt("selector", 3);
        lightingShader.setInt("texture3", 2);
        for (unsigned int i = 4; i < 6; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(tiempo*100), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(tiempo*100), glm::vec3(1.0f, 0.0f, 1.0f));
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            lightingShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 36, 72);
        }
        //BloquesComandos
        lightingShader.setInt("selector", 4);
        lightingShader.setInt("texture4", 3);
        for (unsigned int i = 6; i < 8; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(movimiento, movimiento, movimiento));
            lightingShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 36, 72);
        }

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
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    //If I want to stay in ground level (xz plane)
    //camera.Position.y = 0.0f;
	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);    
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}