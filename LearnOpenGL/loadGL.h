#pragma once
#include "objectsGL.h"
#include "utils.h"

Shader loadShader(const char* vertexPath, const char* fragmentPath, bool depth = true, bool add = false, bool face = true);
Texture loadTexture(const char *texPath);