#version 330 core

// Positions / Coordinates
layout (location = 0) in vec3 aPos;

// Normal
layout (location = 1) in vec3 aNormal;

// Colors
layout (location = 2) in vec3 aColor;

// Texture 
layout (location = 3) in vec2 aTex;

// Outputs the current position for the fragment shader
out vec3 crntPos;
// Outputs the normal for the fragment shader
out vec3 normal;
// Outputs the color to the fragment shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;

uniform mat4 model;

void main() {
	// Calculates current position
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Assigns the normal from the Vertex Data to normal
	normal = aNormal;
	// Assigns the colors from the Vertex Data to color
	color = aColor;
	// Assigns the texture coordinates from the Texture Data to texCoord
	texCoord = aTex;
	// Outputs the coordinates of all vertices
	gl_Position = camMatrix * vec4(aPos, 1.0);
}