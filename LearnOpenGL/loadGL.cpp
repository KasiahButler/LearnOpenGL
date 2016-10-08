#include "loadGL.h"
#include "makeGL.h"

#define STBI_IMAGE_IMPLEMENTATION
#include <STB\stb_image.h>

Shader loadShader(const char * vertexPath, const char * fragmentPath, bool depth, bool add, bool face)
{
	char* vertCode = fileLoader(vertexPath);
	char* fragCode = fileLoader(fragmentPath);

	return makeShader(vertCode, fragCode);
}

Texture loadTexture(const char *texPath)
{
	//Setup variables for making the Texture
	GLint width, height, channel;
	unsigned char *imgHolder;

	//Prep the return Texture
	Texture retTexture = { 0,0,0,0 };

	//Load in the texture image using STBI and set it to the texHolder
	stbi_set_flip_vertically_on_load(true);
	imgHolder = stbi_load(texPath, &width, &height, &channel, STBI_default);

	//If nothing loads in return an empty texture
	//TODO::MAKE A BETTER DEBUG THAN JUST RETURN EMPTY
	if (!imgHolder) return retTexture;

	//If the texture loads then call makeTexture and pass the returned Texture to our retTexture
	retTexture = makeTexture(width, height, channel, imgHolder);

	//Free up the image we loaded in for the Texture
	stbi_image_free(imgHolder);

	return retTexture;
}
