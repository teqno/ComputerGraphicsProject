#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
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
	GLFWwindow* window = glfwCreateWindow(width, height, "Computer Graphics Project", NULL, NULL);
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
	glViewport(0, 0, width, height);

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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	Shader lightShader("light.vert", "light.frag");

	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	
	// Texture
	Texture planksTex("planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	planksTex.texUnit(shaderProgram, "tex0", 0);
	Texture planksSpec("planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
	planksSpec.texUnit(shaderProgram, "tex1", 1);

	// Enables depth buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		// Color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Activate inputs from the user
		camera.Inputs(window);
		// Updates and exports the camera matrix into the vertex shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		
		// Tell OpenGL which shader program we want to use
		shaderProgram.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		camera.Matrix(shaderProgram, "camMatrix");

		// Binds texture so it renders
		planksTex.Bind();
		planksSpec.Bind();
		// Bind VAO for OpenGL to use it
		VAO1.Bind();
		// Draw the triangles using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Process GLFW events
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	planksTex.Delete();
	shaderProgram.Delete();
	// Delete window before exiting the program
	glfwDestroyWindow(window);
	// Terminate GLFW before exiting the program
	glfwTerminate();
	return 0;
}