#pragma once
#include <string>
#include "ShaderBase.h"

class CShaderFong : public CShaderBase
{
public:
	CShaderFong();
	~CShaderFong();

	void initializeParticularShader() override;
	void setUniforms() override;

	GLuint getShaderBuffer(eBufferType bufferType) override;
	float *getEyePosition() { return eyePos; }

private:
	GLuint positionLoc;
	GLuint normalLoc;	

	GLuint pointLightLoc, ambientLoc;
	GLuint KdLoc, KsLoc, KaLoc, n_specularLoc;
	
	GLuint lightPosLoc, eyePosLoc;

	float eyePos[3];
};
