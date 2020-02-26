#include "pch.h"
#include<GLFW\glfw3.h>
#include<string>

#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H

namespace mgl
{
	class TextureMap
	{
	public:
		TextureMap();

		TextureMap(int h, int w, std::string& textMap);

		void initialize(static GLubyte textMap[]);

	private:

	};
}

#endif