#include "utils.h"

char* fileLoader(const char *filepath)
{
	long long fileSize = 0;

	//Open the source file with ifstream
	std::ifstream sourceFile(filepath, std::ios::in);

	//Go to the end of the Source File then get the size of the file for fileSize, then return to the beginning of the file
	sourceFile.seekg(0, std::ios::end);
	fileSize = sourceFile.tellg();
	sourceFile.seekg(0, std::ios::beg);

	//Create a pointer to hold the char array and allocate memory based on the fileSize
	char* fileData = (char*)(malloc(((size_t)fileSize + 1) * sizeof(char)));
	//Set a null terminating character at the end of the Char Pointer
	fileData[fileSize] = 0;

	//Iterate through the sourceFile and copy every character to our fileData array we created
	unsigned int i = 0;
	while (sourceFile.good())
	{
		fileData[i] = sourceFile.get();
		if (!sourceFile.eof())
		{
			++i;
		}
	}

	//Ensure the Null character is at the end of our data that we read in
	fileData[i] = 0;
	//Close the sourceFile
	sourceFile.close();
	//Return the File Contents
	return fileData;
}

void shaderCheck(GLuint shader)
{
	//Shader Error Reporting Code;
	GLint success;
	GLchar infoLog[512];
	//Checks if the Shader has compiled properly
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	//If the Shader fails to Compile get the error info and output to console
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void programCheck(GLuint program)
{
	//Shader Error Reporting Code;
	GLint success;
	GLchar infoLog[512];
	//Checks if the Shader has compiled properly
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	//If the Shader fails to Compile get the error info and output to console
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}