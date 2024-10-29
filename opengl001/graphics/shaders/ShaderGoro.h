#pragma once
#include <string>
//#include "../core/opengl.h"
#include "ShaderBase.h"

class CShaderGoro : public CShaderBase
{
public:
	CShaderGoro();
	~CShaderGoro();

	void initializeParticularShader() override;
	void setUniforms() override;

	GLuint getShaderBuffer(eBufferType bufferType) override;
	//getEyePosition(float x, float y, float z) { return eyePos; }
	float *getEyePosition() { return eyePos; }

private:
	GLuint positionLoc;
	GLuint normalLoc;	

	GLuint pointLightLoc, ambientLoc;
	GLuint KdLoc, KsLoc, KaLoc, n_specularLoc;
	
	GLuint lightPosLoc, eyePosLoc;

	float eyePos[3];
};
