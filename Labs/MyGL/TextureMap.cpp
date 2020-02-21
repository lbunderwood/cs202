#include "pch.h"
#include "TextureMap.h"
#include<GLFW\glfw3.h>

namespace mgl
{
	TextureMap::TextureMap()
	{
		GLuint somethingTextureId = 0;
		glGenTextures(1, &somethingTextureId);
		glBindTexture(GL_TEXTURE_2D, somethingTextureId);
	}

	TextureMap::TextureMap(static GLubyte textMap[])
	{
		GLuint somethingTextureId = 0;
		glGenTextures(1, &somethingTextureId);
		glBindTexture(GL_TEXTURE_2D, somethingTextureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, textMap);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void TextureMap::assignMap(static GLubyte textMap[])
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, textMap);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
}