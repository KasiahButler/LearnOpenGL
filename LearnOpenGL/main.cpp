#include "loadGL.h"
#include "makeGL.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB\stb_image.h>

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
	Window window;
	window.init();
	
	//Set the OpenGL viewport to be the same size as our window Framebuffer
	glViewport(0, 0, window.getWidth(), window.getHeight());

	//Register our key_callback function with the proper OpenGL callback
	//Register callback functions after the window is created but before the game loop is initiated
	glfwSetKeyCallback(window.winHandle, key_callback);
						//Vertices			         Colors			    TexCoords
	GLfloat vertices[] = { 0.5f,  0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
						   0.5f, -0.5f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
						  -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
						  -0.5f,  0.5f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f };

	Vertex verts[4];
	verts[0] = { {  0.5f,  0.5f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0, 0, 1.0f, 0 }, { 1.0f, 1.0f } };
	verts[1] = { {  0.5f, -0.5f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0, 0, 1.0f, 0 }, { 1.0f, 0.0f } };
	verts[2] = { { -0.5f, -0.5f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0, 0, 1.0f, 0 }, { 0.0f, 0.0f } };
	verts[3] = { { -0.5f,  0.5f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 0, 0, 1.0f, 0 }, { 0.0f, 1.0f } };

	GLuint tris[] = { 0,1,3,1,2,3 };

	Shader  basicShader = loadShader("../dep/shaders/vertex.txt", "../dep/shaders/frag.txt");
	Texture boxTexture = loadTexture("../dep/textures/container.jpg");
	Texture faceTexture = loadTexture("../dep/textures/awesomeface.png");

	Geometry testGeo = makeGeometry(verts, 4, tris, 6);

	//Game Loop, keeps the Window open until it's told to close out
	while (window.update())
	{
		//Ready the Shader Program, Bind the VAO and Draw our Triangle then unbind the VAO
		basicShader.update();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, boxTexture.handle);
		glUniform1i(glGetUniformLocation(basicShader.handle, "boxTexture"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, faceTexture.handle);
		glUniform1i(glGetUniformLocation(basicShader.handle, "faceTexture"), 1);

		glBindVertexArray(testGeo.vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	//De-Allocate all resources once they're done being used
	glDeleteVertexArrays(1, &testGeo.vao);
	glDeleteBuffers(1, &testGeo.vbo);

	//Terminates OpenGL (GLFW) and frees up our used resources.
	window.terminate();
	return 0;
}