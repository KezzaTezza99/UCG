#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Librairies/stb/stb_image.h"
#include "src/common/Buffers/VertexArray.h"
#include "src/common/Buffers/VertexBuffer.h"
#include "src/common/Buffers/IndexBuffer.h"
#include "src/common/Shaders/Shaders.h"

//Global constants
const int WIDTH = 800;
const int HEIGHT = 600;

//Callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	//Initialising GLFW
	glewExperimental = true;

	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	//Creating the window object
	glfwWindowHint(GLFW_SAMPLES, 4); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	//Instantiating the window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "UCG", NULL, NULL);

	//Checking the window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window object" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Creating the window context
	glfwMakeContextCurrent(window);

	//Initialising GLEW
	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//Registering the window resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//Setting the viewport
	//glViewport(0, 0, 800, 600);

	//------------------------------------------------------------------
	// Add all code here
	// 
	//TODO: Make a primitive shapes class? - Easily add shapes if needed	
	//------------------------------------------------------------------
	
	////Simple Triangle
	//GLfloat vertices[] =
	//{
	//	//Positions					//Colours
	//	-0.5f, -0.5f, 0.0f,			0.0f, 1.0f, 0.0f,			//Bottom left
	//	 0.5f, -0.5f, 0.0f,			1.0f, 0.0f, 0.0f,			//Bottom right
	//	 0.0f,  0.5f, 0.0f,			0.0f, 0.0f, 1.0f			//Top
	//};

	//Textured Quad
	float vertices[] = 
	{
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//Shapes
	//maths::vec3 bottomLeft = maths::vec3(-0.5f, -0.5f, 0.0f);
	//maths::vec3 bottomRight = maths::vec3(0.5f, -0.5f, 0.0f);
	//maths::vec3 top = maths::vec3(0.0f, 0.5f, 0.0f);

	////TODO: Clean this up, not efficent but dont have the energy to come up with a solution rn
	//PrimitiveShapes triangle;
	//GLfloat* vertices = triangle.DrawTriangle(bottomLeft, bottomRight, top);
	//std::cout << "Debug Info (EntryPoint) -" << "		" << "Vertices " << vertices << std::endl;

	// --- Buffers ---
	//VAO
	VertexArray vertexArray;
	vertexArray.Bind();
	
	//VBO
	VertexBuffer vertexBuffer;
	vertexBuffer.Bind();
	//TODO: Think of an efficent way to pass in the data to send data to opengl in buffer classess instead of here
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//IBO
	IndexBuffer indexBuffer;
	indexBuffer.Bind();
	//TODO: Also need to think about handling this inside the IBO class
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// --- Setting attributes ---
	//Position 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Colour
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texcoords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// --- Shaders ---
	Shaders shaders;
	shaders.LoadShader("src/common/Shaders/GLSL/VertexShader.vs", "src/common/Shaders/GLSL/FragmentShader.vs");

	// --- Textures ---
	//Creating and binding a texture - TODO: Make this into a class
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// Setting the textures wrapping / filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Loading the image that will be used as a texture
	int width, height, channels;
	unsigned char* data = stbi_load("src/assets/Textures/wood.png", &width, &height, &channels, 0);

	if (data)
	{
		//Generating the texture from the loaded image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR: Failed to load texture" << std::endl;
	}

	//Freeing image data
	stbi_image_free(data);

	//------------------------------------------------------------------
	//Render loop / Game loop
	//------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		//Clear the screen 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// --- Handle Input ---

		// --- Rendering ---
		
		//Activating shaders
		shaders.ActivateShaders();
		
		// --- New way ---		
		//Re-binding the texture
		glBindTexture(GL_TEXTURE_2D, texture);
		vertexArray.Bind();

;		// --- Draw Calls ---
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Check / call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//De-allocating resources
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}