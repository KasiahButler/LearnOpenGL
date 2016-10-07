#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <fstream>
#include <iostream>

char* fileLoader(const char *filepath);

void shaderCheck(GLuint shader);
void programCheck(GLuint program);