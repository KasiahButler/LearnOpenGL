#include "shader.h"

//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW\glfw3.h>
//#include <iostream>

//KeyCallback function takes in a Framebuffer, key code, whether its pressed or released, if shift/ctrl/alt or super keys are pressed
//This is templated in a way described by OpenGL so that it can be called by an OpenGL function
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//If a user presses ESC then the WindowShouldClose property is set to false and the program will
	//close out if we have set it to do so.
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main()
{
	//Initialized OpenGL
	glfwInit();
	//Sets the Major Version of OpenGL (3.0)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//Sets the Minor Version of OpenGL (Now the OpenGL version is 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell OpenGL we are using the CORE Profile instead of IMMEDIATE
	//CORE profile allows custom shaders and a NON-FIXED SHADER PIPELINE, IMMEDIATE uses the FIXED SHADER PIPELINE (Old School)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Tells OpenGL that the rendering Window is not user Resizeable (No drag to stretch)
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Creates an OpenGL Windowing Framebuffer called window with a Width of 800, Height of 600, Named "Tester"
	GLFWwindow* window = glfwCreateWindow(800, 600, "Tester", nullptr, nullptr);
	//If the Window is not created enter this loop
	if (window == nullptr)
	{
		//Output that the Window did not instantiate and close out of the Program
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Set the current OpenGL to our window Context
	glfwMakeContextCurrent(window);

	//Starts up GLEW
	glewExperimental = GL_TRUE;
	//If GLEW doesn't start up or has an error close out of the Program.
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//Viewport size variables
	int width, height;
	//Checks the window Framebuffer for it's width and height and sets them to our Viewport size variables
	glfwGetFramebufferSize(window, &width, &height);
	
	//Set the OpenGL viewport to be the same size as our window Framebuffer
	glViewport(0, 0, width, height);

	//Register our key_callback function with the proper OpenGL callback
	//Register callback functions after the window is created but before the game loop is initiated
	glfwSetKeyCallback(window, key_callback);

	GLfloat vertices[] = {-0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
						   0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
						   0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f };

	Shader basicShader("../dep/shaders/vertex.txt", "../dep/shaders/frag.txt");

	//VBO = Vertex Buffer Object, holds a bunch of Vertices in GPU Memory, faster than passing data from CPU to GPU constantly.
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;
	//Generate the Buffer (Creating an Empty Variable in GPU Memory) for the VBO and VAO, first we tell it how many Buffers of this Size (1 in this case) 
	//and then give it an index (GLuint VBO/VAO holds this index number)
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	//Bind the VAO
	glBindVertexArray(VAO);
	//Now we bind the Buffer to a Buffer Type (Array Buffer in this Case)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//Finally we copy our vertices array into the Buffer we just created
	//GL_ARRAY_BUFFER is the Buffer type we bound to earlier, tell it how many bytes its going to use, pass the vertices data, then tell it the data will be Static
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Link our Vertex Attributes and tell it how it should interperet our Vertex Data then enable the Array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Unbind the VAO
	glBindVertexArray(0);

	//Game Loop, keeps the Window open until it's told to close out
	while (!glfwWindowShouldClose(window))
	{
		//Check for inputs and other events
		glfwPollEvents();

		//Sets the OpenGL Clear Color and then clear the Color Buffer
		glClearColor(0.5f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Ready the Shader Program, Bind the VAO and Draw our Triangle then unbind the VAO
		basicShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//Swap the Front Buffer with the Back Buffer that has the window loaded into it
		//Our context is drawn to the GPU's Back Buffer and then passed to the Front Buffer once fully loaded to help avoid artifacting.
		glfwSwapBuffers(window);
	}
	//De-Allocate all resources once they're done being used
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	//Terminates OpenGL (GLFW) and frees up our used resources.
	glfwTerminate();
	return 0;
}