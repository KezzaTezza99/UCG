#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Librairies/stb/stb_image.h"
#include "Librairies/glm/glm.hpp"
#include "Librairies/glm/gtc/matrix_transform.hpp"
#include "Librairies/glm/gtc/type_ptr.hpp"
#include "src/common/Buffers/VertexArray.h"
#include "src/common/Buffers/VertexBuffer.h"
#include "src/common/Buffers/IndexBuffer.h"
#include "src/common/Shaders/Shaders.h"
#include "src/common/Models/TextureLoader.h"

// --- TODO: 
//  Create a camera class
//  Create a shader class
//  Make my own maths class?
//  Clean code up
//	Performance class?
//	Image class?

// --- Global constants ---
const int WIDTH = 800;
const int HEIGHT = 600;

//Camera stuff
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//Eualer stuff
float lastX = WIDTH / 2;
float lastY = HEIGHT / 2;
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;

//Performance
float deltaTime = 0.0f;								//Time between current frame and last frame
float lastFrame = 0.0f;								//Time of last frame

//Callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);

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
	
	//Enabling the use of the z buffer
	glEnable(GL_DEPTH_TEST);

	//------------------------------------------------------------------
	// Add all code here
	//------------------------------------------------------------------
	
	GLuint indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	//3D Cube
	GLfloat vertices[] = 
	{
		//Positions					//Texture Coords
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,		0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,		1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,		1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,		0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,		0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,		0.0f, 1.0f
	};

	////World space positions of a bunch of cubes
	//glm::vec3 cubePositions[] =
	//{
	//	glm::vec3(0.0f,  0.0f,  0.0f),
	//	glm::vec3(2.0f,  5.0f, -15.0f),
	//	glm::vec3(-1.5f, -2.2f, -2.5f),
	//	glm::vec3(-3.8f, -2.0f, -12.3f),
	//	glm::vec3(2.4f, -0.4f, -3.5f),
	//	glm::vec3(-1.7f,  3.0f, -7.5f),
	//	glm::vec3(1.3f, -2.0f, -2.5f),
	//	glm::vec3(1.5f,  2.0f, -2.5f),
	//	glm::vec3(1.5f,  0.2f, -1.5f),
	//	glm::vec3(-1.3f,  1.0f, -1.5f)
	//};

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
	
	//Setting the vertex attributes in the vertex shader - Position then UVs
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// --- Shaders ---
	//Textured cube
	Shaders shaders;
	shaders.LoadShader("src/common/Shaders/GLSL/BasicVertex.shader", "src/common/Shaders/GLSL/BasicFragment.shader");

	// --- Textures ---
	TextureLoader texture;
	texture.Bind();
	texture.SetTextureParams();

	//TODO: Create an image class?
	//Loading the image that will be used as a texture
	int width, height, channels;
	unsigned char* data = stbi_load("src/assets/Textures/wood.png", &width, &height, &channels, 0);

	if (data)
	{
		//TODO: Image class and pass image object to texture class and do this stuff there?
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
	
	//Hiding the cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Setting the mouse callback
	glfwSetCursorPosCallback(window, mouse_callback);

	//Projection Matrix - Doesn't change so no point recalculating every frame
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

	//------------------------------------------------------------------
	//Render loop / Game loop
	//------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		// --- Performance ---
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Clear the screen 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// --- Handle Input ---
		processInput(window);


		// --- Rendering ---
		
		//Activating shaders
		shaders.ActivateShaders();
		
		//Re-binding
		texture.Bind();
		vertexArray.Bind();

		// --- Matrices ---
		//Model Matrix - One Cube
		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		
		//View Matrix
		glm::mat4 viewMatrix = glm::mat4(1.0f);
		//viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0, 0.0f, -3.0f));
		viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		//Getting the matrix uniform locations
		unsigned int modelLocation = glGetUniformLocation(shaders.GetID(), "model");
		unsigned int viewLocation = glGetUniformLocation(shaders.GetID(), "view");
		unsigned int projLocation = glGetUniformLocation(shaders.GetID(), "projection");

		//Passing the matrices to the vertex shader
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

;		// --- Draw Calls ---
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Cube without indices
		glDrawArrays(GL_TRIANGLES, 0, 36);	

		/*
			//Multiple Cubes
			for (unsigned int i = 0; i < 10; i++)
			{
				glm::mat4 modelMatrix = glm::mat4(1.0f);
				modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
				float angle = 20.0f * i;
				modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		*/
		
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

void processInput(GLFWwindow* window)
{
	//Press ESC to quit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//Camera Movement
	const float cameraSpeed = 2.5f * deltaTime;

	//Forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	
	//Backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	
	//Left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	
	//Right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	const float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	//Restricting users ability to look up and down -89 > 89
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	//Euler Angles
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}