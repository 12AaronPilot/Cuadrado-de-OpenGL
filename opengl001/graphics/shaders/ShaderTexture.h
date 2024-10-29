#pragma once
#include <string>
#include "ShaderBase.h"

class CShaderTexture : public CShaderBase
{
public:
	CShaderTexture(const std::string &filename);
	~CShaderTexture();

	void initializeParticularShader() override;
	void setUniforms() override;

	GLuint getShaderBuffer(eBufferType bufferType) override;

private:
	GLuint positionLoc;
	GLuint vertexuvLoc;	

	GLuint textureID;
	GLuint textureLoc;
};
