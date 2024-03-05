#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>//añadimos camara
#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camara
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// tiempo
float deltaTime = 0.0f;
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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Johanna Huaraca CI: 172497756-4", NULL, NULL);
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
	glEnable(GL_DEPTH_TEST);


	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader("shaders/shader_exercise12.vs", "shaders/shader_exercise12.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
	//PERSONAJES
		//CABEZA ARRIBA
			// positions          // texture coords
		-0.5f, -0.5f, -0.5f,  0.551f, 0.921f, //abi
		0.5f, -0.5f, -0.5f,  0.728f, 0.921f, //abd
					  0.5f,  0.5f, -0.5f,  0.728f, 0.675f, //ard
					  0.5f,  0.5f, -0.5f,  0.728f, 0.675f, //ard
					 -0.5f,  0.5f, -0.5f,  0.551f, 0.675f, //ari
					 -0.5f, -0.5f, -0.5f,  0.551f, 0.921f, //abi

					 //CUELLO
					 -0.5f, -0.5f,  0.5f,  0.551f, 0.258f, //abi
					  0.5f, -0.5f,  0.5f,  0.728f, 0.258f, //abd
					  0.5f,  0.5f,  0.5f,  0.728f, 0.506f, //ard
					  0.5f,  0.5f,  0.5f,  0.728f, 0.506f, //ard
					 -0.5f,  0.5f,  0.5f,  0.551f, 0.506f, //ari
					 -0.5f, -0.5f,  0.5f,  0.551f, 0.258f, //abi

					 //OREJA DERECHA
					 -0.5f,  0.5f,  0.5f,  0.532f, 0.5f, //ard
					 -0.5f,  0.5f, -0.5f,  0.532f, 0.674f, //abd
					 -0.5f, -0.5f, -0.5f,  0.338f, 0.674f, //abi
					 -0.5f, -0.5f, -0.5f,  0.338f, 0.674f, //abi
					 -0.5f, -0.5f,  0.5f,  0.338f, 0.5f, //ari
					 -0.5f,  0.5f,  0.5f,  0.532f, 0.5f, //ard

					 //OREJA IZQUIERDA
					  0.5f,  0.5f,  0.5f,  0.73f, 0.5f, //ari
					  0.5f,  0.5f, -0.5f,  0.73f, 0.674f, //abi
					  0.5f, -0.5f, -0.5f,  0.924f, 0.674f, //abd
					  0.5f, -0.5f, -0.5f,  0.924f, 0.674f, //abd
					  0.5f, -0.5f,  0.5f,  0.924f, 0.5f, //ard
					  0.5f,  0.5f,  0.5f,  0.73f, 0.5f, //ari

					  //CABEZA ATRAS
					  -0.5f, -0.5f, -0.5f,  0.338f, 0.66f, //abi
					   0.5f, -0.5f, -0.5f,  0.143f, 0.66f, //abd
					   0.5f, -0.5f,  0.5f,  0.143f, 0.506f, //ard
					   0.5f, -0.5f,  0.5f,  0.143f, 0.506f, //ard
					  -0.5f, -0.5f,  0.5f,  0.338f, 0.506f, //ari
					  -0.5f, -0.5f, -0.5f,  0.338f, 0.66f, //abi

					  //CARA
					  -0.5f,  0.5f, -0.5f,  0.532f, 0.66f, //abi
					   0.5f,  0.5f, -0.5f,  0.721f, 0.66f, //abd
					   0.5f,  0.5f,  0.5f,  0.721f, 0.506f, //ard
					   0.5f,  0.5f,  0.5f,  0.721f, 0.506f, //ard
					  -0.5f,  0.5f,  0.5f,  0.532f, 0.506f, //ari
					  -0.5f,  0.5f, -0.5f,  0.532f, 0.66f,  //abi
	};

	// world space positions of our cubes
	glm::vec3 cubePositions[] = {
		 glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.5f, -1.2f, -22.5f)
	};

	//Para Textura 2 Homero 
	float vertices2[] = {
		//CARA 1 PARTE TRASERA DE Homero  
		// positions          // texture coords
	-0.5f, -0.5f, -0.5f,  0.6310f + 0.492f, 0.22f + 0.12f,//a
	 0.5f, -0.5f, -0.5f,  0.439f + 0.568f, 0.22f + 0.12f , //b
	 0.5f,  0.5f, -0.5f,  0.439f + 0.568f, 0.236f + 0.02f ,//c d
	 0.5f,  0.5f, -0.5f,  0.439f + 0.568f, 0.236f + 0.02f ,//d
	-0.5f,  0.5f, -0.5f,  0.6310f + 0.492f,0.236f + 0.02f ,//e
	-0.5f, -0.5f, -0.5f,  0.6310f + 0.492f,0.22f + 0.12f,//f a

	//CARA 2  CARA DE Homero 
	-0.5f, -0.5f,  0.5f,   0.73f, 0.33f,//a
	 0.5f, -0.5f,  0.5f,   0.73f, 0.5f, //b
	0.5f,  0.5f,  0.5f,    0.52f, 0.5f,//c 
	0.5f,  0.5f,  0.5f,    0.52, 0.33f,//d
	-0.5f,  0.5f,  0.5f,   0.73f, 0.33f,//e
	-0.5f, -0.5f,  0.5f,   0.73f, 0.33f,//f a

	//CARA 3  Lado izquierdo
	-0.5f,  0.5f,  0.5f,   0.210f + 0.04f, 0.236f + 0.02f,//d
	-0.5f,  0.5f, -0.5f, 0.124195f , 0.236f + 0.02f,//e
	-0.5f, -0.5f, -0.5f, 0.124195f , 0.22f + 0.12f,//a
	-0.5f, -0.5f, -0.5f,  0.124195f , 0.22f + 0.12f,//a
	-0.5f, -0.5f,  0.5f,  0.210f + 0.04f, 0.22f + 0.12f,//b
	-0.5f,  0.5f,  0.5f,  0.210f + 0.04f ,0.236f + 0.02f,//d

	//CARA 4  Lado derecho
	 0.5f,  0.5f,  0.5f,  0.210f + 0.04f, 0.236f + 0.02f,//d
	 0.5f,  0.5f, -0.5f,   0.124195f, 0.236f + 0.02f,//e
	 0.5f, -0.5f, -0.5f,   0.124195f, 0.22f + 0.12f,//a
	 0.5f, -0.5f, -0.5f,   0.124195f, 0.22f + 0.12f,//a
	 0.5f, -0.5f,  0.5f,  0.210f + 0.04f, 0.22f + 0.12f,//b
	 0.5f,  0.5f,  0.5f, 0.210f + 0.04f, 0.236f + 0.02f,//d

	 //Abajo de homero
 -0.5f, -0.5f, -0.5f, 0.220f + 0.04f,0.130f + 0.12f,//d
  0.5f, -0.5f, -0.5f,  0.24f + 0.14f, 0.130f + 0.12f,//e
  0.5f, -0.5f,  0.5f,  0.24f + 0.14f, 0.038f + 0.1f,//a
  0.5f, -0.5f,  0.5f,  0.24f + 0.14f, 0.038f + 0.1f,//a
 -0.5f, -0.5f,  0.5f,  0.220f + 0.04f, 0.038f + 0.1f,//b
 -0.5f, -0.5f, -0.5f,  0.220f + 0.04f, 0.130f + 0.12f,//d

 //Arriba de homero
 -0.5f,  0.5f, -0.5f,  0.220f + 0.04f, 0.436f + 0.02f,//d
  0.5f,  0.5f, -0.5f,  0.24f + 0.14f, 0.436f + 0.02f,//e
  0.5f,  0.5f,  0.5f,  0.24f + 0.14f, 0.33f + 0.02f,//a
  0.5f,  0.5f,  0.5f,  0.24f + 0.14f, 0.33f + 0.02f,//a
 -0.5f,  0.5f,  0.5f, 0.220f + 0.04f, 0.33f + 0.02f,//b
 -0.5f,  0.5f, -0.5f,  0.220f + 0.04f,0.436f + 0.02f,//d

	};

	// world space positions of our cubes
	glm::vec3 cubePositions2[] = {
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(-2.7f, 0.5f, -4.5f)
	};




	float vertices3[] = {
		//CARA 1 PARTE TRASERA DEL MICHI AMARILLO
		// positions          // texture coords
	-0.5f, -0.5f, -0.5f,   0.638f, 0.335f ,//a
	 0.5f, -0.5f, -0.5f,  0.738f, 0.335f, //b
	 0.5f,  0.5f, -0.5f,  0.738f, 0.37f ,//c d
	 0.5f,  0.5f, -0.5f,  0.738f, 0.37f ,//d
	-0.5f,  0.5f, -0.5f,   0.638f, 0.37f ,//e
	-0.5f, -0.5f, -0.5f,   0.638f, 0.335f ,//f a

	//CARA 2  CARA DEL MICHI 
	-0.5f, -0.5f,  0.5f,   0.638f, 0.228f ,//a
	0.5f, -0.5f,  0.5f,  0.748f , 0.228f, //b
	0.5f,  0.5f,  0.5f,  0.748f , 0.32f,//c d
	0.5f,  0.5f,  0.5f,  0.748f , 0.32f,//d
	-0.5f,  0.5f,  0.5f,  0.638f, 0.32f,//e
	-0.5f, -0.5f,  0.5f,  0.638f, 0.228f,//f a

	//CARA 3  Lado izquierdo
	-0.5f,  0.5f,  0.5f,   0.638f, 0.32f,//d
	-0.5f,  0.5f, -0.5f, 0.530f, 0.32f,//e
	-0.5f, -0.5f, -0.5f, 0.530f, 0.228f,//a
	-0.5f, -0.5f, -0.5f,  0.530f, 0.228f,//a
	-0.5f, -0.5f,  0.5f,  0.638f, 0.228f,//b
	-0.5f,  0.5f,  0.5f,  0.638f, 0.32f,//d


	//CARA 4  Lado derecho
		0.5f,  0.5f,  0.5f,  0.638f, 0.32f,//d
	 0.5f,  0.5f, -0.5f,   0.583f, 0.32f,//e
	 0.5f, -0.5f, -0.5f,   0.583f, 0.228f,//a
	 0.5f, -0.5f, -0.5f,   0.583f, 0.228f,//a
	 0.5f, -0.5f,  0.5f,  0.638f, 0.228f,//b
	 0.5f,  0.5f,  0.5f,  0.638f, 0.32f,//d

	 //Abajo del michi

	-0.5f, -0.5f, -0.5f,  0.638f, 0.148f,//d
	 0.5f, -0.5f, -0.5f,  0.748f, 0.148f,//e
	0.5f, -0.5f,  0.5f,  0.748f, 0.235f,//a
	 0.5f, -0.5f,  0.5f,  0.748f, 0.235f,//a
	-0.5f, -0.5f,  0.5f, 0.638f, 0.235f,//b
	-0.5f, -0.5f, -0.5f,  0.638f, 0.148f,//d

	//Arriba del michi
	-0.5f,  0.5f, -0.5f,  0.66f, 0.42f,//d
	 0.5f,  0.5f, -0.5f, 0.73f, 0.42f,//e
	 0.5f,  0.5f,  0.5f,  0.73f, 0.32f,//a
	 0.5f,  0.5f,  0.5f,  0.73f, 0.32f,//a
	-0.5f,  0.5f,  0.5f,  0.66f, 0.32f,//b
	-0.5f,  0.5f, -0.5f,  0.66f, 0.42f,//d

	};

	// world space positions of our cubes
	glm::vec3 cubePositions3[] = {
		 glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -5.5f),
		glm::vec3(1.5f,  0.2f, -10.5f),
		 glm::vec3(-3.0f,  0.2f, -2.5f)
	};


	float vertices4[] = {
		//CARA 1 PARTE TRASERA DEL MICHI NEGRO
		//         // positions          // texture coords
	-0.5f, -0.5f, -0.5f,  0.14f, 0.78f,//a
	 0.5f, -0.5f, -0.5f,  0.26f  , 0.78f , //b
	 0.5f,  0.5f, -0.5f,  0.26f  , 0.87f,//c d
	 0.5f,  0.5f, -0.5f,  0.26f  , 0.87f,//d
	-0.5f,  0.5f, -0.5f,  0.14f , 0.87f,//e
	-0.5f, -0.5f, -0.5f,  0.14f , 0.78f,//f a

	//CARA 2  CARA DEL MICHI 
	-0.5f, -0.5f,  0.5f,   0.14f, 0.659f,//a
	0.5f, -0.5f,  0.5f,  0.26f , 0.659f, //b
	0.5f,  0.5f,  0.5f,  0.26f , 0.775f,//c d
	0.5f,  0.5f,  0.5f,  0.26f , 0.775f,//d
	-0.5f,  0.5f,  0.5f,  0.14f, 0.775f,//e
	-0.5f, -0.5f,  0.5f,  0.14f, 0.659f,//f a

	//CARA 3  Lado izquierdo
	-0.5f,  0.5f,  0.5f,   0.054f , 0.775f,//d
	-0.5f,  0.5f, -0.5f, 0.13f , 0.775f,//e
	-0.5f, -0.5f, -0.5f, 0.13f , 0.669f,//a
	-0.5f, -0.5f, -0.5f,  0.13f , 0.669f,//a
	-0.5f, -0.5f,  0.5f,  0.054f , 0.669f,//b
	-0.5f,  0.5f,  0.5f,  0.054f, 0.775f,//d


	//CARA 4  Lado derecho
		0.5f,  0.5f,  0.5f,   0.054f , 0.775f,//d
	 0.5f,  0.5f, -0.5f,   0.13f, 0.775f,//e
	 0.5f, -0.5f, -0.5f,   0.13f, 0.669f,//a
	 0.5f, -0.5f, -0.5f,   0.13f , 0.669f,//a
	 0.5f, -0.5f,  0.5f,  0.054f , 0.669f,//b
	 0.5f,  0.5f,  0.5f,   0.054f , 0.775f,//d

	 //Abajo del michi
 -0.5f, -0.5f, -0.5f,  0.14f , 0.659f,//d
  0.5f, -0.5f, -0.5f, 0.25f , 0.659f ,//e
  0.5f, -0.5f,  0.5f,  0.25f , 0.58f ,//a
  0.5f, -0.5f,  0.5f,  0.25f , 0.58f ,//a
 -0.5f, -0.5f,  0.5f, 0.14f , 0.58f ,//b
 -0.5f, -0.5f, -0.5f,  0.14f , 0.659f ,//d

 //Arriba del michi
 -0.5f,  0.5f, -0.5f,  0.14f , 0.835f,//d
  0.5f,  0.5f, -0.5f,  0.25f , 0.835f,//e
  0.5f,  0.5f,  0.5f,  0.25f  , 0.775f,//a
  0.5f,  0.5f,  0.5f,  0.25f , 0.775f ,//a
 -0.5f,  0.5f,  0.5f,  0.14f  , 0.775f ,//b
 -0.5f,  0.5f, -0.5f,  0.14f  , 0.835f,//d

	};

	// world space positions of our cubes
	glm::vec3 cubePositions4[] = {
		glm::vec3(2.0f,  10.0f,  -20.0f),
		glm::vec3(-5.0f,  4.0f, -8.0f),
		 glm::vec3(1.3f,  0.5f, -4.5f),
		 glm::vec3(1.0f,  4.0f,  -20.0f),
	};


	unsigned int VBO, VAO, VAO2, VBO2, VAO3, VBO3, VAO4, VBO4;
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO2);
	glGenVertexArrays(1, &VAO3);
	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &VBO4);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);


	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);


	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
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
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
	stbi_image_free(data);

	// texture 2
	// ---------
	glGenTextures(2, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("textures/Texturegrass.jpg", &width, &height, &nrChannels, 0);    if (data)
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

	ourShader.use();
	



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
		glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		ourShader.use();
		glBindVertexArray(VAO);

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		// camara
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);


		//Dibuja MICHI MINECRAFT
		ourShader.setInt("texture1", 0);
		for (unsigned int i = 0; i < 5; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			float scale = sin(glfwGetTime());
			model = glm::translate(model, cubePositions[i]+scale);
			float angle = 30.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.5f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// Dibuja HOMERO 

		glBindVertexArray(VAO2);
		ourShader.setInt("texture2", 1);
		for (unsigned int i = 0; i < 5; i++)
		{
			
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions2[i]);
			float scale = sin(glfwGetTime());
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(scale, 0.3f, 0.5f));

			model = glm::scale(model, glm::vec3(scale, scale, scale));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Dibuja el MICHI AMARILLO 

	  // ourShader.use();
	   /*glBindVertexArray(VAO3);
	   for (unsigned int i = 0; i < 5; i++)
	   {
		   glm::mat4 model = glm::mat4(1.0f);
		   float scale = sin(glfwGetTime());
		   model = glm::translate(model, cubePositions3[i]);
		   model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		   ourShader.setMat4("model", model);

		   glDrawArrays(GL_TRIANGLES, 0, 36);
	   }

	   //Dibuja el MICHI NEGRO
	   glBindVertexArray(VAO4);
	   for (unsigned int i = 0; i < 5; i++)
	   {
		   float scale = sin(glfwGetTime())+0.2;
		   glm::mat4 model = glm::mat4(1.0f);
		   model = glm::translate(model, cubePositions4[i]);
		   model = glm::scale(model, glm::vec3(scale, scale, scale));
		   model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		   ourShader.setMat4("model", model);

		   glDrawArrays(GL_TRIANGLES, 0, 36);
	   }*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Limpieza de recursos al finalizar
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteVertexArrays(1, &VAO3);
	glDeleteBuffers(1, &VBO3);
	glDeleteVertexArrays(1, &VAO4);
	glDeleteBuffers(1, &VBO4);

	glfwTerminate();
	return 0;
}

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}