#pragma once
#include <fstream>
#include <iostream>
#include "utils.h"

#include <GL\glew.h>

class Shader
{
public:
	GLuint handle;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
		const GLchar* vShaderCode = fileLoader(vertexPath);
		const GLchar* fShaderCode = fileLoader(fragmentPath);

		//Load up the vertex shader and check that all is well
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		shaderCheck(vertex);

		//Load up the fragment shader and check that all is well
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		shaderCheck(fragment);

		this->handle = glCreateProgram();
		glAttachShader(this->handle, vertex);
		glAttachShader(this->handle, fragment);
		glLinkProgram(this->handle);
		programCheck(this->handle);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	inline void use() { glUseProgram(this->handle); }
};