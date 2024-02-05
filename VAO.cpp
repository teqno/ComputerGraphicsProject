#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO VBO, GLuint layout) {
	VBO.Bind();
	// Configure the Vertex Attribute so OpenGL knows how to read the VBO
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// Enable the Vertex Attribute for OpenGL to use it
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind() {
	// Bind VAO for OpenGL to use it
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	// Unbing VAO to stop using it
	glBindVertexArray(0);
}

void VAO::Delete() {
	// Delete VAO object
	glDeleteVertexArrays(1, &ID);
}