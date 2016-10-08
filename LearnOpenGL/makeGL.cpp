#include "makeGL.h"
#include "utils.h"

Shader makeShader(const char * vertexCode, const char * fragCode, bool depth, bool add, bool face)
{
	Shader retShader;

	//Load in Vertex Shader and check if it works
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);
	shaderCheck(vertexShader);

	//Do the same for the Fragment Shader
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragCode, NULL);
	glCompileShader(fragShader);
	shaderCheck(fragShader);

	//Create the Shader Program and set our Shaders Handle to the Program
	retShader.handle = glCreateProgram();
	//Attach the Vert and Frag Shaders to our newly made Program
	glAttachShader(retShader.handle, vertexShader);
	glAttachShader(retShader.handle, fragShader);
	//Link the Shader Program
	glLinkProgram(retShader.handle);
	//Double check that everything linked properly
	programCheck(retShader.handle);

	//Delete the Shaders now that they're linked
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	//Return our finished Shader Program
	return retShader;
}

void freeShader(Shader & shader)
{
	//Delete the passed in Shader Program and set this Shaders Handle to 0
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}

Texture makeTexture(GLuint width, GLuint height, GLuint channel, const void *img, const bool isFloat)
{
	//Multi Channel Texture Making like a bass
	GLenum eformat = GL_RGBA;
	GLenum iformat = isFloat ? GL_RGBA32F : eformat;
	switch (channel)
	{
	case 0: eformat = GL_DEPTH_COMPONENT; iformat = GL_DEPTH24_STENCIL8; break;
	case 1: eformat = GL_RED;  iformat = isFloat ? GL_R32F    : eformat; break;
	case 2: eformat = GL_RG;   iformat = isFloat ? GL_RG32F   : eformat; break;
	case 3: eformat = GL_RGB;  iformat = isFloat ? GL_RGB32F  : eformat; break;
	case 4: eformat = GL_RGBA; iformat = isFloat ? GL_RGBA32F : eformat; break;
	default: std::cout << "ERROR, CHANNELS MUST BE 0-4" << std::endl;
	}

	//Prep the retTexture and generate a Texture in OpenGL then set retTexture's handle to the generated Texture
	//glGenTextures(numOfTexturesToGen, whereToPlaceTheTextureHandle)
	Texture retTexture = { 0, width, height, channel };
	glGenTextures(1, &retTexture.handle);

	//Bind the Texture we just generated so that we can apply modifications to it
	glBindTexture(GL_TEXTURE_2D, retTexture.handle);

	//After Binding we can setup our Texture using glTexImage2D (Since its a 2D Texture)
	//textureTarget, mipmapLevel (base of 0), formatToStoreTexture (R, RG, RGB, RGBA), width, height, 0, formatOfTexture, dataTypeOfTexture, textureImage
	glTexImage2D(GL_TEXTURE_2D, 0, iformat, width, height, 0, eformat, isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE, img);
	//Auto Generate a mipMap for our Texture, Could also iterate through and generate mipmaps ourself
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Unbind the Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return retTexture;
}

void freeTexture(Texture & texture)
{
	glDeleteTextures(1, &texture.handle);
	texture = {0, 0, 0, 0};
}

Geometry makeGeometry(const Vertex *verts, GLuint vsize, const GLuint *tris, GLuint tsize)
{
	Geometry retGeo;
	retGeo.size = tsize;

	//Generate our Buffers (VBO,VAO,EBO/IBO)
	glGenBuffers(1, &retGeo.vbo);
	glGenBuffers(1, &retGeo.ibo);
	glGenVertexArrays(1, &retGeo.vao);

	//Bind all three to their respective Buffers so that we can manipulate them
	glBindVertexArray(retGeo.vao);
	glBindBuffer(GL_ARRAY_BUFFER, retGeo.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retGeo.ibo);

	//Set the size of our Buffers and pass the data into them (vertices in the VBO, indices in the IBO)
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(GLuint), tris, GL_STATIC_DRAW);

	//Enable all of the Vertex Arrays for the VAO (Lets us know how the VBO data is layed out)
	glEnableVertexAttribArray(0); //Position
	glEnableVertexAttribArray(1); //Color
	glEnableVertexAttribArray(2); //Normal
	glEnableVertexAttribArray(3); //TexCoord

	//Set the Attrib Pointers to their location number (This way we can call the data using layout(location) in the shader
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::NORMAL);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::TEXCOORD);

	//Unbind everything now that we've set it up so nothing messes with it unintentionally
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return retGeo;
}

void freeGeometry(Geometry & geometry)
{
	glDeleteBuffers(1, &geometry.vbo);
	glDeleteBuffers(1, &geometry.ibo);
	glDeleteVertexArrays(1, &geometry.vao);
	geometry = { 0,0,0,0 };
}
