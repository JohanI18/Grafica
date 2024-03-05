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

unsigned int loadTexture(const char *path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 4.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float tiempo = 0;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


glm::vec3 lightPos(0.0f);

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
    Shader lightCubeShader("shaders/B2T3_lightcube.vs", "shaders/B2T3_lightcube.fs");

   
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
    //PERSONAJES
    //Cara1
    // positions        //normals            // texture coords
   -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.533f, 0.326f,
    0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.533f, 0.078f,
    0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.730f, 0.078f,
    0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.730f, 0.078f,
   -0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.730f, 0.326f,
   -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.533f, 0.326f,
   
   //Cara2
   -0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.534f, 0.743f,
    0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.729f, 0.743f,
    0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.729f, 0.500f,
    0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.729f, 0.500f,
   -0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.534f, 0.500f,
   -0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.534f, 0.743f,
   //Cara3
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.922f, 0.500f,
   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.922f, 0.327f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.731f, 0.327f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.731f, 0.327f,
   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.731f, 0.500f,
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.922f, 0.500f,
   //Cara4
    0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.339f, 0.500f,
    0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.339f, 0.327f,
    0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.531f, 0.327f,
    0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.531f, 0.327f,
    0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.531f, 0.500f,
    0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.339f, 0.500f,
    //Cara5
   -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.533f, 0.326f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.730f, 0.326f,
    0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  0.730f, 0.500f,
    0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  0.730f, 0.500f,
   -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  0.533f, 0.500f,
   -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.533f, 0.326f,
   //Cara6
   -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.143f, 0.327f,
    0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.337f, 0.327f,
    0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.337f, 0.500f,
    0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.337f, 0.500f,
   -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.143f, 0.500f,
   -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.143f, 0.327f,
   //BLOQUES
   //Cara1
   // positions          // texture coords
   -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.295f, 0.160f,
    0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.508f, 0.160f,
    0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.508f, 0.416f,
    0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.508f, 0.416f,
   -0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.295f, 0.416f,
   -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.295f, 0.160f,
   //Cara2
   -0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.295f, 0.928f,
    0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.508f, 0.928f,
    0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.508f, 0.754f,
    0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.508f, 0.754f,
   -0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.295f, 0.754f,
   -0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.295f, 0.928f,
   //Cara3
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.295f, 0.650f,
   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.295f, 0.416f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.082f, 0.416f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.082f, 0.416f,
   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.082f, 0.650f,
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.295f, 0.650f,
   //Cara4
    0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.508f, 0.650f,
    0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.508f, 0.416f,
    0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.722f, 0.416f,
    0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.722f, 0.416f,
    0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.722f, 0.650f,
    0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.508f, 0.650f,
    //Cara5
   -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f,  0.0f,  0.508f, 0.416f,
    0.5f, -0.5f, -0.5f, 0.0f,  -1.0f,  0.0f,  0.295f, 0.416f,
    0.5f, -0.5f,  0.5f, 0.0f,  -1.0f,  0.0f,  0.295f, 0.650f,
    0.5f, -0.5f,  0.5f, 0.0f,  -1.0f,  0.0f,  0.295f, 0.650f,
   -0.5f, -0.5f,  0.5f, 0.0f,  -1.0f,  0.0f,  0.508f, 0.650f,
   -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f,  0.0f,  0.508f, 0.416f,
   //Cara6
   -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.722f, 0.416f,
    0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.935f, 0.416f,
    0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.935f, 0.650f,
    0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.935f, 0.650f,
   -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.722f, 0.650f,
   -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.722f, 0.416f,
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

    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //load textures
    unsigned int diffuseMap1 = loadTexture("textures/Texture8.jpg");
    unsigned int diffuseMap2 = loadTexture("textures/TextureA.jpg");
    unsigned int diffuseMap3 = loadTexture("textures/TextureC.jpg");
    unsigned int diffuseMap4 = loadTexture("textures/TextureG.jpg");
    unsigned int specularMap = loadTexture("textures/specularmap.jpg");
    unsigned int emissionMap = loadTexture("textures/specularmap.jpg");
    // shader configuration
    // --------------------
    lightingShader.use();
    
    lightingShader.setInt("material.specular", 4);
    lightingShader.setInt("material.emission", 5);

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
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Time vars
        tiempo = glfwGetTime();
        float movimiento = sin(tiempo);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();

        //COORDENADAS
        lightPos.x = sin(tiempo) * -10.5;
        lightPos.y = 0;
        lightPos.z = (cos(tiempo) * -10.5) - 5;

        lightingShader.setVec3("light.position", lightPos );
        lightingShader.setVec3("viewPos", camera.Position);

       
       // light properties
        lightingShader.setVec3("light.ambient", 0.05f, 0.05f, 0.0f);
        lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.4f);
        // material properties
        lightingShader.setVec3("light.specular", 0.7f, 0.7f, 0.04f);
        lightingShader.setFloat("material.shininess", 0.05);

        

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
     lightingShader.setMat4("model", model);
	 
	 
	 // bind diffuse map
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, diffuseMap1);
     glActiveTexture(GL_TEXTURE1);
     glBindTexture(GL_TEXTURE_2D, diffuseMap2);
     glActiveTexture(GL_TEXTURE2);
     glBindTexture(GL_TEXTURE_2D, diffuseMap3);
     glActiveTexture(GL_TEXTURE3);
     glBindTexture(GL_TEXTURE_2D, diffuseMap4);

	 // bind specular map
	 glActiveTexture(GL_TEXTURE4);
     glBindTexture(GL_TEXTURE_2D, specularMap);

     // bind emission map
     glActiveTexture(GL_TEXTURE5);
     glBindTexture(GL_TEXTURE_2D, emissionMap);

     //PERSONAJE
     glBindVertexArray(cubeVAO);
     for (unsigned int i = 0; i < 2; i++)
     {
         lightingShader.setInt("material.diffuse", 0);
         glm::mat4 model = glm::mat4(1.0f);

         model = glm::translate(model, cubePositions[i]);
         model = glm::rotate(model, glm::radians(180.0f), glm::vec3(movimiento, 1.0f, 0.0f));
         model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
         lightingShader.setMat4("model", model);
         glDrawArrays(GL_TRIANGLES, 0, 36);
     }

     //BloquesComandos
     for (unsigned int i = 2; i < 4; i++)
     {
         lightingShader.setInt("material.diffuse", 1);
         glm::mat4 model = glm::mat4(1.0f);
         model = glm::rotate(model, glm::radians(tiempo * 100), glm::vec3(0.0f, 0.0f, 1.0f));
         model = glm::translate(model, cubePositions[i]);
         model = glm::rotate(model, glm::radians(tiempo * 100), glm::vec3(1.0f, 0.0f, 1.0f));
         model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
         lightingShader.setMat4("model", model);
         glDrawArrays(GL_TRIANGLES, 36, 72);
     }
     //Bloquesamatista
     for (unsigned int i = 4; i < 6; i++)
     {
         lightingShader.setInt("material.diffuse", 2);
         glm::mat4 model = glm::mat4(1.0f);
         model = glm::rotate(model, glm::radians(tiempo * 100), glm::vec3(0.0f, 0.0f, 1.0f));
         model = glm::translate(model, cubePositions[i]);
         model = glm::rotate(model, glm::radians(tiempo * 100), glm::vec3(1.0f, 0.0f, 1.0f));
         model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
         lightingShader.setMat4("model", model);
         glDrawArrays(GL_TRIANGLES, 36, 72);
     }

     //Bloquesgrass
     for (unsigned int i = 6; i < 8; i++)
     {
         lightingShader.setInt("material.diffuse", 3);
         glm::mat4 model = glm::mat4(1.0f);
         model = glm::translate(model, cubePositions[i]);
         model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
         model = glm::scale(model, glm::vec3(movimiento, movimiento, movimiento));
         lightingShader.setMat4("model", model);
         glDrawArrays(GL_TRIANGLES, 36, 72);
     }

     // also draw the lamp object
     lightCubeShader.use();
     lightCubeShader.setMat4("projection", projection);
     lightCubeShader.setMat4("view", view);
     model = glm::mat4(1.0f);
     model = glm::translate(model, lightPos);
     model = glm::scale(model, glm::vec3(0.6f)); // tamaño del cubo
     lightCubeShader.setMat4("model", model);

     glBindVertexArray(lightCubeVAO);



     glDrawArrays(GL_TRIANGLES, 0, 36);
    
     // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
     // -------------------------------------------------------------------------------
     glfwSwapBuffers(window);
     glfwPollEvents();
 }

 // optional: de-allocate all resources once they've outlived their purpose:
 // ------------------------------------------------------------------------
 glDeleteVertexArrays(1, &cubeVAO);
 glDeleteVertexArrays(1, &lightCubeVAO);
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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
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

unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}