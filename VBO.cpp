#include "VBO.h"

VBO::VBO(std::vector<Vertex>& vertices) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::Bind() {
	// Bind VBO for OpenGL to use it
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	// Unbind VBO to stop using it
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	// Delete VBO object
	glDeleteBuffers(1, &ID);
}