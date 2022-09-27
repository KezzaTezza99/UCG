#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "src/common/Buffers/VertexArray.h"
#include "src/common/Buffers/VertexBuffer.h"
#include "src/common/Shaders/Shaders.h"

//TODO: Break shaders into a class
//Global constants
const int WIDTH = 800;
const int HEIGHT = 600;

//Callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//TODO: Break this into their own classes
// SHADER STUFF - Original
/*
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
*/

//Added Colours to the vertices data
//const char* vertexShaderSource = "#version 330 core\n"
//								 "layout (location = 0) in vec3 aPos;\n"
//								 "layout (location = 1) in vec3 aColour;\n"
//								 "out vec3 ourColour;\n"
//								 "void main()\n"
//								 "{\n"
//								 "   gl_Position = vec4(aPos, 1.0);\n"
//								 "	 ourColour = aColour;\n"
//								 "}\0";
//
//const char* fragmentShaderSource = "#version 330 core\n"
//								   "out vec4 FragColour;\n"
//								   "in vec3 ourColour;\n"
//								   "void main()\n"
//								   "{\n"
//								   "   FragColour = vec4(ourColour, 1.0);\n"
//								   "}\0";

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
	
	//Simple Triangle
	GLfloat vertices[] =
	{
		//Positions					//Colours
		-0.5f, -0.5f, 0.0f,			0.0f, 1.0f, 0.0f,			//Bottom left
		 0.5f, -0.5f, 0.0f,			1.0f, 0.0f, 0.0f,			//Bottom right
		 0.0f,  0.5f, 0.0f,			0.0f, 0.0f, 1.0f			//Top
	};
	
	////Simple Quad
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

	//Shapes
	//maths::vec3 bottomLeft = maths::vec3(-0.5f, -0.5f, 0.0f);
	//maths::vec3 bottomRight = maths::vec3(0.5f, -0.5f, 0.0f);
	//maths::vec3 top = maths::vec3(0.0f, 0.5f, 0.0f);

	////TODO: Clean this up, not efficent but dont have the energy to come up with a solution rn
	//PrimitiveShapes triangle;
	//GLfloat* vertices = triangle.DrawTriangle(bottomLeft, bottomRight, top);
	//std::cout << "Debug Info (EntryPoint) -" << "		" << "Vertices " << vertices << std::endl;

	//Buffers
	VertexArray vertexArray;
	vertexArray.Bind();
	
	VertexBuffer vertexBuffer;
	vertexBuffer.Bind();
	//TODO: Think of an efficent way to pass in the data to send data to opengl in buffer classess instead of here
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//OLD WAY
	/*
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
	*/

	Shaders shaders;
	shaders.LoadShader("src/common/Shaders/GLSL/VertexShader.vs", "src/common/Shaders/GLSL/FragmentShader.vs");

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
		//glUseProgram(shaderProgram);
		shaders.ActivateShaders();

		//Re-bindng
		glEnableVertexAttribArray(0);
		vertexBuffer.Bind();
		
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//Now using colour data and more attributes
		//Position 
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//Colour
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

;		//Drawing
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		//Check / call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//De-allocating resources
	//glDeleteProgram(shaderProgram);

	//Clearing all allocated GLFW resources
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}