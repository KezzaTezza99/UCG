#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

//Global constants
const int WIDTH = 800;
const int HEIGHT = 600;

//Callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// SHADER STUFF - TEMP
const char* vertexShaderSource = "#version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "void main()\n"
								 "{\n"
								 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
								 "}\0";

const char* fragmentShaderSource =  "#version 330 core\n"
									"out vec4 FragColor;\n"
									"void main()\n"
									"{\n"
									"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
									"}\0";

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

	
	GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);

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

	//Setting the viewport
	//Registering the window resize callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//glViewport(0, 0, 800, 600);


	//------------------------------------------------------------------
	// Add all code here
	// 
	
	//Creating the models etc
	//GLfloat vertices[] = {
	//	// first triangle
	//	 0.5f,  0.5f, 0.0f,  // top right
	//	 0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f,  0.5f, 0.0f,  // top left 
	//	// second triangle
	//	 0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f,  // bottom left
	//	-0.5f,  0.5f, 0.0f   // top left
	//};

	//GLuint indices[] =
	//{
	//	0, 1, 3,			//First triangle
	//	1, 2, 3				//Second triangle
	//};

	//Simple Triangle
	static const GLfloat vertices[] =
	{
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};

	//Buffers
	//TODO: Make these into seperate classes
	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	//Creating the buffer
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Vertex Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//Fragment Shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Creating a shader program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	//Attaching the compiled shaders to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//Cleaning up the shaders as they are now not needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//------------------------------------------------------------------
	//Render loop / Game loop
	//
	while (!glfwWindowShouldClose(window))
	{
		//Clear the screen 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Handle Input

		//Render
		glUseProgram(shaderProgram);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//Drawing
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		//Check / call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//De-allocating resources
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteProgram(shaderProgram);

	//Clearing all allocated GLFW resources
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}