#pragma once
#include <fstream>
#include <iostream>
#include "utils.h"

#include <GL\glew.h>
#include <GLM\glm.hpp>

class Window
{
private:
	GLint width, height;
	GLchar title[64];
	bool isInit = false;

public:
	struct GLFWwindow *winHandle = nullptr;

	inline bool getInit() { return isInit; }
	inline GLint getWidth() { return width; }
	inline GLint getHeight() { return height; }
	inline GLchar* getTitle() { return title; }

	bool init(GLint wWidth = 800, GLint wHeight = 600, GLchar *wTitle = "Corgs",
			  GLint isResizable = GL_TRUE, GLint verMajor = 3, GLint verMinor = 3);

	bool update();
	bool terminate();
};

class Shader
{
public:
	GLuint handle;

	bool depthTest;
	bool additiveBlend;
	bool faceCulling;

	inline void update() { glUseProgram(handle); }
};

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;
	glm::vec4 normal;
	glm::vec2 texcoord;

	enum{POSITION = 0, COLOR = 16, NORMAL = 32, TEXCOORD = 48};
};

struct Geometry
{
	GLuint vbo, vao, ibo;
	GLuint size;

	//Vertex Buffer Object : Holds our array of Vertices
	//Index/Element Buffer Object : Holds an array of Indices for drawing polygons (Triangles/Squares)
	//Size : Number of polygons (Triangles/Squares) in the Geometry Object
};

struct Texture
{
	GLuint handle;
	GLuint width, height, format;
};

struct Framebuffer
{
	GLuint handle;
	GLuint width, height, nColors;

	Texture depth;
	Texture colors[8];
};