#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex shader source
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Fragment shader source
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {
	// Initialize GLFW
	glfwInit();
	
	// Tell GLFW what version of OpenGL we are using (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using CORE profile - only modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// Lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Lower right
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f	// Top middle
	};

	// Create GLFWwindow object of width and hight 800 and 800 pixels
	GLFWwindow* window = glfwCreateWindow(800, 800, "Computer Graphics Project", NULL, NULL);
	// If the window doesn't exist then exit the program
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Make the context of the provided window current
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the window 
	glViewport(0, 0, 800, 800);

	// Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader
	glCompileShader(vertexShader);

	// Create Fragment Shader Object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Fragment Shader
	glCompileShader(fragmentShader);

	// Create Shader Program and get reference
	GLuint shaderProgram = glCreateProgram();

	// Attach Vertex and Fragment shaders to the Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link the shaders into a Shader Program
	glLinkProgram(shaderProgram);

	// Delete Vertex and Fragment shader objects because they are not needed anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Create reference containers for Vertex Array Object and Vertex Buffer Object
	GLuint VAO, VBO;

	// Generate VAO and VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Pass vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute for OpenGL to use it
	glEnableVertexAttribArray(0);

	// Bind both VAO and VBO to 0 so we don't accidentally modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign a new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which shader program we want to use
		glUseProgram(shaderProgram);
		// Bind VAO for OpenGL to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		// Process GLFW events
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Delete window before exiting the program
	glfwDestroyWindow(window);
	// Terminate GLFW before exiting the program
	glfwTerminate();
	return 0;
}