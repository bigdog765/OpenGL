#include <GL/glew.h> // Include the GLEW header for OpenGL functions

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int createTexture() {
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	unsigned int texture;
	glGenTextures(1, &texture); // Ensure OpenGL headers are included
	glBindTexture(GL_TEXTURE_2D, texture);
}