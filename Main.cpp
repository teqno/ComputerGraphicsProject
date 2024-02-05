#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// Vertices coordinates
GLfloat vertices[] =
{ //			COORDINATES					/			COLORS				//
	-0.5f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f,	0.3f,	0.02f,	// Lower left
	 0.5f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f,	0.3f,	0.02f,		// Lower right
	 0.0f,	 0.5f * float(sqrt(3)) * 2 / 3,	0.0f,	1.0f,	0.6f,	0.32f,	// Top middle
	-0.25f,	 0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f,	0.45f,	0.17f,	// Inner left
	 0.25f,	 0.5f * float(sqrt(3)) / 6,		0.0f,	0.9f,	0.45f,	0.17f,	// Inner right
	 0.0f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.8f,	0.3f,	0.02f		// Inner down
};

// Indices that indicate the order of walking through the vertices
GLuint indices[] =
{
	0, 3, 5,	// Lower left triangle
	3, 2, 4,	// Lower right triangle
	5, 4, 1		// Upper triangle
};

int main() {
	// Initialize GLFW
	glfwInit();
	
	// Tell GLFW what version of OpenGL we are using (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using CORE profile - only modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFWwindow object of width and hight 800 and 800 pixels
	GLFWwindow* window = glfwCreateWindow(800, 800, "Computer Graphics Project", NULL, NULL);
	// If the window doesn't exist then exit the program
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Make the context of the provided wsindow current
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the window 
	glViewport(0, 0, 800, 800);

	// Creates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Elelemt Buffer object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which shader program we want to use
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		// Bind VAO for OpenGL to use it
		VAO1.Bind();
		// Draw the triangles using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Process GLFW events
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before exiting the program
	glfwDestroyWindow(window);
	// Terminate GLFW before exiting the program
	glfwTerminate();
	return 0;
}