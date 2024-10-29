#pragma once
#include <string>
#include "ShaderBase.h"

class CShaderColor : public CShaderBase
{
public:
	CShaderColor();
	~CShaderColor();

	void initializeParticularShader() override;
	void setParticularUniforms() override { }

	GLuint getPosLoc() override { return positionLoc; }
	GLuint getColorLoc() override { return colorLoc; }

private:
	GLuint positionLoc, colorLoc;
};
