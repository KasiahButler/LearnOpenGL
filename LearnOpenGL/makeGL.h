#pragma once
#include "objectsGL.h"

Shader makeShader(const char* vertexCode, const char* fragmentCode, bool depth = true, bool add = false, bool face = true);
void freeShader(Shader &shader);

Texture makeTexture(GLuint width, GLuint height, GLuint channel, const void *img, const bool isFloat = false);
void freeTexture(Texture &texture);

Geometry makeGeometry(const struct Vertex *verts, GLuint vsize, const GLuint *tris, GLuint tsize);
void freeGeometry(Geometry &geometry);