#include "ShaderTexture.h"
#include <fstream>
#include <vector>
#include "../textures/lodepng.h"

using namespace std;

CShaderTexture::CShaderTexture(const std::string &filename)
{
	std::vector<unsigned char> image;
	unsigned int width, height;
	unsigned int error = lodepng::decode(image, width, height, filename);
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
}

CShaderTexture::~CShaderTexture()
{
}

void CShaderTexture::initializeParticularShader()
{
	GLuint programme = getShaderProgram();

	positionLoc = glGetAttribLocation(programme, "in_Position");
	vertexuvLoc = glGetAttribLocation(programme, "vertexUV");

	textureLoc = glGetUniformLocation(programme, "myTextureSampler");
}

void CShaderTexture::setUniforms()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glUniform1i(textureLoc, 0);
}

GLuint CShaderTexture::getShaderBuffer(eBufferType bufferType)
{
	switch (bufferType)
	{
	case eBufferType::POSITION:	return positionLoc; break;
	case eBufferType::TEXTURE:	return vertexuvLoc; break;
	default: break;
	}
	return GLuint();
}


