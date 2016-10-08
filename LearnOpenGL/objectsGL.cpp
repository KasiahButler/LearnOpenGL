#include "objectsGL.h"

bool Window::init(GLint wWidth, GLint wHeight, GLchar * wTitle, GLint isResizable, GLint verMajor, GLint verMinor)
{
	width = wWidth;
	height = wHeight;
	strcpy_s(title, 64, wTitle);

	//Initialize GLFW
	glfwInit();
	//Instantiate our Window in GLFW and pass the Handle to our Window Class
	winHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);

	//Make our window context the active one
	glfwMakeContextCurrent(winHandle);
	//Set isInit to true so that we know there is already an active Window
	isInit = true;

	//Initialize GLEW and set our Clear Color to Black
	glewInit();
	glClearColor(0.5f, 0.0f, 1.0f, 0.0f);

	//Sets if the Window is Resizeable, Major/Minor version of OpenGL, and that we are using the CORE Profile
	glfwWindowHint(GLFW_RESIZABLE, isResizable);
	glfwWindowHint(GLFW_VERSION_MAJOR, verMajor);
	glfwWindowHint(GLFW_VERSION_MINOR, verMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

bool Window::update()
{
	//If not initialized return false and don't update
	if (!isInit) { return false; }

	//Poll for events and swap the Back Buffer to the Front Buffer
	glfwPollEvents();
	glfwSwapBuffers(winHandle);

	//Clear Buffer Data in back Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return !glfwWindowShouldClose(winHandle);
}

bool Window::terminate()
{
	//Destroy our Windoow and Terminate GLFW, set window handle and to null and isInit back to false
	glfwDestroyWindow(winHandle);
	glfwTerminate();

	winHandle = nullptr;
	isInit = false;

	return true;
}
