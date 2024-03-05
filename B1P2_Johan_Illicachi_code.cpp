#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 750;
const unsigned int SCR_HEIGHT = 750;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Blue
const char* fragmentShaderBlueSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.2f, 0.6f, 1.0f, 0.0f);\n"
"}\n\0";
//Purple
const char* fragmentShaderPurpleSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.43f, 0.46f, 0.73f, 0.0f);\n"
"}\n\0";
//Shining green
const char* fragmentShaderShiningGreenSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.6f, 0.8f, 0.2f, 0.0f);\n"
"}\n\0";
//Red
const char* fragmentShaderRedSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.4f, 0.4f, 0.0f);\n"
"}\n\0";
//Yellow
const char* fragmentShaderYellowSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.9f, 0.79f, 0.2f, 0.0f);\n"
"}\n\0";
//Orange
const char* fragmentShaderOrangeSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.6f, 0.2f, 0.0f);\n"
"}\n\0";
//Green
const char* fragmentShaderGreenSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.2f, 0.8f, 0.4f, 0.0f);\n"
"}\n\0";


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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B1P2 CI:1600877458 Johan Illicachi", NULL, NULL);
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
    // ------------------------------------
    // we skipped compile log checks this time for readability (if you do encounter issues, add the compile-checks! see previous code samples)
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShaderBlue = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramBlue = glCreateProgram();
    glShaderSource(fragmentShaderBlue, 1, &fragmentShaderBlueSource, NULL);
    glCompileShader(fragmentShaderBlue);

    unsigned int fragmentShaderPurple = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramPurple = glCreateProgram();
    glShaderSource(fragmentShaderPurple, 1, &fragmentShaderPurpleSource, NULL);
    glCompileShader(fragmentShaderPurple);

    unsigned int fragmentShaderShiningGreen = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramShiningGreen = glCreateProgram();
    glShaderSource(fragmentShaderShiningGreen, 1, &fragmentShaderShiningGreenSource, NULL);
    glCompileShader(fragmentShaderShiningGreen);

    unsigned int fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramRed = glCreateProgram();
    glShaderSource(fragmentShaderRed, 1, &fragmentShaderRedSource, NULL);
    glCompileShader(fragmentShaderRed);

    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramYellow = glCreateProgram();
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderYellowSource, NULL);
    glCompileShader(fragmentShaderYellow);

    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramOrange = glCreateProgram();
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderOrangeSource, NULL);
    glCompileShader(fragmentShaderOrange);

    unsigned int fragmentShaderGreen = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int shaderProgramGreen = glCreateProgram();
    glShaderSource(fragmentShaderGreen, 1, &fragmentShaderGreenSource, NULL);
    glCompileShader(fragmentShaderGreen);

    // link program object

    glAttachShader(shaderProgramBlue, vertexShader);
    glAttachShader(shaderProgramBlue, fragmentShaderBlue);
    glLinkProgram(shaderProgramBlue);

    glAttachShader(shaderProgramPurple, vertexShader);
    glAttachShader(shaderProgramPurple, fragmentShaderPurple);
    glLinkProgram(shaderProgramPurple);

    glAttachShader(shaderProgramShiningGreen, vertexShader);
    glAttachShader(shaderProgramShiningGreen, fragmentShaderShiningGreen);
    glLinkProgram(shaderProgramShiningGreen);

    glAttachShader(shaderProgramRed, vertexShader);
    glAttachShader(shaderProgramRed, fragmentShaderRed);
    glLinkProgram(shaderProgramRed);

    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);

    glAttachShader(shaderProgramGreen, vertexShader);
    glAttachShader(shaderProgramGreen, fragmentShaderGreen);
    glLinkProgram(shaderProgramGreen);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.58f,  0.63f, 0.00f, //A 0
        -0.58f,  0.20f, 0.00f, //B 1
        -0.79f,  0.41f, 0.00f, //C 2
        -0.37f,  0.41f, 0.00f, //D 3
        -0.58f, -0.65f, 0.00f, //E 4
         0.01f,  0.20f, 0.00f, //F 5
        -0.20f,  0.41f, 0.00f, //G 6
         0.22f,  0.41f, 0.00f, //H 7
         0.07f,  0.00f, 0.00f, //I 8
        -0.16f, -0.23f, 0.00f, //J 9
        -0.35f, -0.42f, 0.00f, //K 10
         0.50f, -0.42f, 0.00f, //L 11
         0.76f, -0.42f, 0.00f, //M 12
        -0.20f, -0.65f, 0.00f, //N 13
         0.03f, -0.42f, 0.00f, //O 14
         0.55f, -0.65f, 0.00f, //P 15
         0.35f, -0.42f, 0.00f, //Q 16
        -0.29f, -0.10f, 0.00f, //R 17
    };
    unsigned int indices[] = {
        //head
        0,1,2,
        0,1,3,
        //arms
        1,5,17,
        //hands
        5,6,7,
        //body
        1,4,9,
        //butt
        4,10,13,
        13,14,10,
        //legs
        10,11,8,
        //feet
        15,16,12
    };

    // Habilito buffers
    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Copia y guarda en el VBO y en la GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Leyendo los atributos hacia donde tiene que enviar (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Deshabilita buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        //head
        glUseProgram(shaderProgramRed);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(0 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));

        //arms
        glUseProgram(shaderProgramShiningGreen);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(unsigned int)));

        //hands
        glUseProgram(shaderProgramBlue);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(9 * sizeof(unsigned int)));

        //body
        glUseProgram(shaderProgramYellow);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(12 * sizeof(unsigned int)));

        //butt
        glUseProgram(shaderProgramPurple);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(15 * sizeof(unsigned int)));
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(18 * sizeof(unsigned int)));

        //legs
        glUseProgram(shaderProgramGreen);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(21 * sizeof(unsigned int)));

        //feet
        glUseProgram(shaderProgramOrange);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(24 * sizeof(unsigned int)));

        // draw the second triangle using the data from our second VAO


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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
    glViewport(0, 0, width, height);
}