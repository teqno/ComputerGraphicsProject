#version 330 core

// Positions / Coordinates
layout (location = 0) in vec3 aPos;

// Colors
layout (location = 1) in vec3 aColor;

// Texture 
layout (location = 2) in vec2 aTex;

// Normal
layout (location = 3) in vec3 aNormal;

// Outputs the color to the fragment shader
out vec3 color;

out vec2 texCoord;

out vec3 normal;
out vec3 crntPos;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;

uniform mat4 model;

void main() {
	crntPos = vec3(model * vec4(aPos, 1.0f));

	// Outputs the coordinates of all vertices
	gl_Position = camMatrix * vec4(aPos, 1.0);
	color = aColor;
	texCoord = aTex;
	normal = aNormal;
}