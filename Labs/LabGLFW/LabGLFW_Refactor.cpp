#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include "HeadGLFW.h"

#ifdef _MSC_VER
#pragma comment(lib, "opengl32.lib")
#endif

// Anonymouse namespace for storing stuff
namespace {
	constexpr int MAX_KEYS = GLFW_KEY_LAST;
	std::vector<int> keys(MAX_KEYS, 0);
}

void HandleKeyCallback(GLFWwindow*, int, int, int, int);

int main(void) {
	// first open the triangle + circle window
	triangleCircle();

	// then do this one
	GLFWwindow* window;

	// Initialize the library
	if (!glfwInit())
		return -1;

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, HandleKeyCallback);

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Create a texture map
	GLuint somethingTextureId = 0;
	glGenTextures(1, &somethingTextureId);
	glBindTexture(GL_TEXTURE_2D, somethingTextureId);
	static GLubyte something[] =
		".........xxxxxx........."
		"......xxx......xxx......"
		"...xxx...AAAAAA...xxx..."
		"xxx...AAAAAAAAAAAA...xxx"
		"xxx...AAAAAAAAAAAA...xxx"
		"xxxAAA...AAAAAA...AAAxxx"
		"xxxAAA............AAAxxx"
		"...xxxxxxxxxxxxxxxxxx..."
		; // note: every three characters in a row = RGB
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, something);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Create a texture map
	GLuint checkerTextureId = 0;
	glGenTextures(1, &checkerTextureId);
	glBindTexture(GL_TEXTURE_2D, checkerTextureId);
	static GLubyte checkers[] =
		"xxxxxx......xxxxxx......"
		"xxxxxx......xxxxxx......"
		"......xxxxxx......xxxxxx"
		"......xxxxxx......xxxxxx"
		"xxxxxx......xxxxxx......"
		"xxxxxx......xxxxxx......"
		"......xxxxxx......xxxxxx"
		"......xxxxxx......xxxxxx"
		; // note: every three characters in a row = RGB
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, checkers);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		//////////////////////////////////////////////////////////
		// SETUP THE VIEWPORT AND PROJECTION MATRIX //////////////
		//////////////////////////////////////////////////////////
		int w = 1;
		int h = 1;
		glfwGetWindowSize(window, &w, &h);
		glViewport(0, 0, w, h);
		double aspectRatio = (double)w / (double)h;
		constexpr double DEGREES_TO_RADIANS = 0.01745329251994329576923690768489; // PI / 180
		constexpr double FIELD_OF_VIEW_Y = 45.0;
		constexpr double ZNEAR = 0.01;
		constexpr double ZFAR = 100.0;
		GLdouble f = 1.0f / std::tan(0.5f * DEGREES_TO_RADIANS * FIELD_OF_VIEW_Y);
		GLdouble m11 = f / aspectRatio;
		GLdouble m22 = f;
		GLdouble m33 = (ZFAR + ZNEAR) / (ZNEAR - ZFAR);
		GLdouble m34 = 2 * ZFAR * ZNEAR / (ZNEAR - ZFAR);
		GLdouble projection[16] = {
			m11,   0,   0,  0,
			0,   m22,   0,  0,
			0,     0, m33, -1,
			0,     0, m34,  0 };
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glLoadMatrixd(projection);
		glMatrixMode(GL_MODELVIEW);

		////////////////////////////////////////////////////
		// CLEAR SCREEN AND DEPTH BUFFER ///////////////////
		////////////////////////////////////////////////////

		// Begin Rendering here
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f); // Set RGBA color to clear screen buffer
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);	// Use Z-Buffering
		glEnable(GL_CULL_FACE);		// Ensure we only show front faces

		////////////////////////////////////////////////////
		// SETUP CAMERA + LIGHTING + ENVIRONMENT ///////////
		////////////////////////////////////////////////////

		// Setup camera
		glLoadIdentity();
		GLfloat cameraLocation[] = { 0.0f, 0.0f, -4.0f };
		glTranslatef(cameraLocation[0], cameraLocation[1], cameraLocation[2]);

		// Setup one white directional light pointing almost "up"
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		GLfloat lightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
		GLfloat lightDir[4] = { 0.1f, 0.9f, 0.1f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightDir);

		// We want color materials so that materials work with glColor3f
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_FOG);
		GLfloat fogColor[4] = { 0.1f, 0.2f, 0.3f };
		glFogf(GL_FOG_DENSITY, 0.05f);
		glFogfv(GL_FOG_COLOR, fogColor);

		////////////////////////////////////////////////////
		// CONFIGURE MATERIALS + TRANSFORMATION ////////////
		////////////////////////////////////////////////////

		// Configure material options here
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, somethingTextureId);
		glMaterialf(GL_FRONT, GL_SHININESS, 64);

		// Begin drawing the cube
		glPushMatrix();
		double t = glfwGetTime();
		float sint = (float)std::sin(t);
		float cost = (float)std::cos(t);
		glTranslatef(0.0f, 0.0f, cost);
		float scale = (float)t - (int)t + 0.5f;
		//glScalef(scale, scale, 1.0f);
		glRotatef((float)t * 30.f, 1.0f, 0.0f, 0.0f);
		glRotatef((float)t * 53.f, 0.0f, 1.0f, 0.0f);
		glRotatef((float)t * 27.f, 0.0f, 0.0f, 1.0f);

		//////////////////////////////////////////////////////////
		// DRAW THE 3D OBJECT ////////////////////////////////////
		//////////////////////////////////////////////////////////

		// Prepare data to draw shape
		constexpr unsigned NUM_VERTICES = 8;
		constexpr unsigned NUM_FACES = 6;
		constexpr unsigned NUM_VERTICES_PER_FACE = 6;
		GLfloat vertices[NUM_VERTICES][3] = {
			{ -0.5f, -0.5f,  0.5f },
			{  0.5f, -0.5f,  0.5f },
			{  0.5f,  0.5f,  0.5f },
			{ -0.5f,  0.5f,  0.5f },
			{ -0.5f, -0.5f, -0.5f },
			{  0.5f, -0.5f, -0.5f },
			{  0.5f,  0.5f, -0.5f },
			{ -0.5f,  0.5f, -0.5f },
		};
		GLint elements[6][6] = {
			{0,1,2,2,3,0}, // +Z
			{4,7,6,6,5,4}, // -Z
			{3,2,6,6,7,3}, // +Y
			{4,5,1,1,0,4}, // -Y
			{1,5,6,6,2,1}, // +X
			{4,0,3,3,7,4}, // -X
		};
		// array of colors
		GLfloat colors[NUM_FACES][4] = {
			{0,0,1,1},
			{1,1,0,1},
			{0,1,0,1},
			{1,0,1,1},
			{1,0,0,1},
			{0,1,1,1},
		};
		// array of normals (the direction each face points in)
		GLfloat normals[NUM_FACES][3] = {
			{ 0,  0,  1}, // +Z
			{ 0,  0, -1}, // -Z
			{ 0,  1,  0}, // +Y
			{ 0, -1,  0}, // -Y
			{ 1,  0,  0}, // +X
			{-1,  0,  0}, // -X
		};
		// array of texture coordinates
		GLfloat texcoords[NUM_VERTICES_PER_FACE][2] = {
			{0.0f, 0.0f},
			{1.0f, 0.0f},
			{1.0f, 1.0f},
			{1.0f, 1.0f},
			{0.0f, 1.0f},
			{0.0f, 0.0f},
		};

		glBegin(GL_TRIANGLES);
		glNormal3f(0.0f, 0.0f, -1.0f);
		for (int face = 0; face < NUM_FACES; face++) {
			glColor3fv(colors[face]);
			glNormal3fv(normals[face]);
			for (int i = 0; i < NUM_VERTICES_PER_FACE; i++) {
				// each face uses the same texture coordinates
				glTexCoord2fv(texcoords[i]);
				// elements[face] returns a pointer to the elements of a face
				// elements[face][i] returns the index of the vertex
				// vertices[k] returns the pointer to the vertex
				// thereforce vertices[elements[face][i]] returns the pointer to the vertex indexed by elements
				glVertex3fv(vertices[elements[face][i]]);
			}
		}
		glEnd();

		////////////////////////////////////////////////////
		// RESTORE MATERIALS + TRANSFORMATION //////////////
		////////////////////////////////////////////////////

		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();

		////////////////////////////////////////////////////
		// CONFIGURE MATERIALS + TRANSFORMATION ////////////
		////////////////////////////////////////////////////

		// Configure material options here
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, checkerTextureId);
		glMaterialf(GL_FRONT, GL_SHININESS, 1);

		// Set the world transformation
		glPushMatrix();
		glTranslatef(0.0f, -1.0f, 0.0f);

		//////////////////////////////////////////////////////////
		// DRAW THE 3D OBJECT ////////////////////////////////////
		//////////////////////////////////////////////////////////

		// Draw ground plane
		constexpr float SIZEMIN = -10.0f;
		constexpr float SIZEMAX = 10.0f;
		constexpr float GROUNDY = 0.0f;
		GLfloat groundVertices[4][3] = {
			{SIZEMIN, GROUNDY, SIZEMIN},
			{SIZEMAX, GROUNDY, SIZEMIN},
			{SIZEMAX, GROUNDY, SIZEMAX},
			{SIZEMIN, GROUNDY, SIZEMAX},
		};
		GLfloat gtexcoords[4][2] = {
			{ 0.0f,  0.0f},
			{10.0f,  0.0f},
			{10.0f, 10.0f},
			{ 0.0f, 10.0f},
		};

		glBegin(GL_TRIANGLES);
		glNormal3f(0, 1, 0);
		glColor3f(1, 0, 0);
		glTexCoord2fv(gtexcoords[2]);
		glVertex3fv(groundVertices[2]);
		glTexCoord2fv(gtexcoords[1]);
		glVertex3fv(groundVertices[1]);
		glTexCoord2fv(gtexcoords[0]);
		glVertex3fv(groundVertices[0]);
		glTexCoord2fv(gtexcoords[0]);
		glVertex3fv(groundVertices[0]);
		glTexCoord2fv(gtexcoords[3]);
		glVertex3fv(groundVertices[3]);
		glTexCoord2fv(gtexcoords[2]);
		glVertex3fv(groundVertices[2]);
		glEnd();

		////////////////////////////////////////////////////
		// RESTORE MATERIALS + TRANSFORMATION //////////////
		////////////////////////////////////////////////////

		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();

		////////////////////////////////////////////////////
		// SWAP BUFFERS AND POLL EVENTS ////////////////////
		////////////////////////////////////////////////////

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();

		////////////////////////////////////////////////////
		// HANDLE KEYBOARD EVENTS //////////////////////////
		////////////////////////////////////////////////////

		if (keys[GLFW_KEY_ESCAPE]) {
			glfwSetWindowShouldClose(window, 1);
		}
	}

	glfwTerminate();
	return 0;
}

void HandleKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key < 0 && key >= MAX_KEYS) return;
	switch (action) {
	case GLFW_PRESS:
		keys[key] = 1; break;
	case GLFW_RELEASE:
		keys[key] = 0; break;
	default:
		// ignore all other options such as GLFW_REPEAT for now
		break;
	}
}