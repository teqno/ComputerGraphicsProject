#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Takes the color from the vertex shader
in vec3 color;

in vec2 texCoord;

uniform sampler2D tex0;

void main() {
	FragColor = texture(tex0, texCoord);
}