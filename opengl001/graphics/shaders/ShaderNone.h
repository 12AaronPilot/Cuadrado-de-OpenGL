#pragma once
#include <string>
#include "ShaderBase.h"

class CShaderNone : public CShaderBase
{
public:
	CShaderNone();
	~CShaderNone();

	void initializeParticularShader() override;
	void setParticularUniforms() override { }

	GLuint getPosLoc() override { return positionLoc; }

private:
	GLuint positionLoc;
};
