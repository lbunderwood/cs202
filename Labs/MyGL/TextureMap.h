#include<GLFW\glfw3.h>

#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H

namespace mgl
{
	class TextureMap
	{
	public:
		TextureMap();

		TextureMap(static GLubyte textMap[]);

		void assignMap(static GLubyte textMap[]);

	private:

	};
}

#endif