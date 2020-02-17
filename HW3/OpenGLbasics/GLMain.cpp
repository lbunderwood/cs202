// Luke Underwood
// 2/12/2020
// cs202
// HW3
// OpenGLBasics
// GLMain.cpp

#include<iostream>

#include<glad\glad.h>
#include<GLFW\glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"

"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

// callback for window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void inputError()
{
	std::cout << "ERROR::BAD_INPUT\nPlease enter a single argument of the "
		<< "shape you would like, either square triangle, or line";
}

int main(int argc, char** argv)
{
	std::string arg;
	if (argc == 2)
	{
		arg = argv[1];

		for (auto n : arg)
		{
			if (n < 96) n += 32;
		}
		
		if (!(arg == "square" || arg == "triangle" || arg == "line"))
		{
			inputError();
			return 0;
		}
	}
	else
	{
		inputError();
		return 0;
	}

	//since these values are used a couple places...
	int xSize = 1920;
	int ySize = 1080;

	// initialize glfw with version number and opengl profile
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// create the window with glfw plus error handling
	GLFWwindow* window = glfwCreateWindow(xSize, ySize, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// initialize GLAD with error handling
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// create opengl viewport
	glViewport(0, 0, xSize, ySize);

	// create callback for resizing the window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// create vertices array
	float vertices[] = 
	{
		-0.5f,  -0.5f, 0.0f, // bottom left
		 0.5f,  -0.5f, 0.0f, // bottom right
		 0.5f,   0.5f, 0.0f, // top right
		-0.5f,   0.5f, 0.0f, // top left
		 0.0f,   0.5f, 0.0f, // middle top
		-0.5f,  0.01f, 0.0f, // middle top left
		-0.5f, -0.01f, 0.0f, // middle bottom left
		 0.5f,  0.01f, 0.0f, // middle top right
		 0.5f, -0.01f, 0.0f, // middle bottom right
	};
	unsigned int indices[] =
	{
		0, 1, 4, // triangle
		0, 1, 2, // 
		0, 2, 3, // square
		5, 6, 8, //
		5, 7, 8  // line 
	};

	int offset = sizeof(unsigned int);
	int vertexNum;
	if (arg == "square")
	{
		vertexNum = 6;
		offset *= 3;
	}
	else if (arg == "triangle")
	{
		vertexNum = 3;
		offset *= 0;
	}
	else if (arg == "line")
	{
		vertexNum = 6;
		offset *= 9;
	}

	// initialize VBO = vector buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// initialize and compile vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// initialize and compile fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check that shader compiled correctly
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders in shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// error handling for shader program
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	
	// create VAO = vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// bind Vertex Array Object
	glBindVertexArray(VAO);
	// copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// create EBO = element buffer object
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// main event loop
	while (!glfwWindowShouldClose(window))
	{
		// check for input
		processInput(window);

		// reset the window
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); 
		glDrawElements(GL_TRIANGLES, vertexNum, GL_UNSIGNED_INT, (const void*)offset);
		glBindVertexArray(0);

		// check for events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// terminate glfw
	glfwTerminate();
	return 0;

	// clean up
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}