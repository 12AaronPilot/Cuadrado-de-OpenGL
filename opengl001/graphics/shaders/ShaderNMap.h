#pragma once
#include <string>
#include "ShaderBase.h"

class CShaderNMap : public CShaderBase
{
public:
	CShaderNMap();
	~CShaderNMap();

	void initializeParticularShader() override;
	void setParticularUniforms() override { }

	GLuint getPosLoc() override { return positionLoc; }
	GLuint getUVLoc() override { return uvLoc; }
	GLuint getNormalLoc() override { return normalLoc; }
	GLuint getTangentLoc() override { return tangentLoc; }
	GLuint getBinormalLoc() override { return binormalLoc; }

	void setUniforms() override;
	void setLightPosition(float x, float y, float z) override {
		lpx = x; lpy = y; lpz = z;
	}

private:
	GLuint positionLoc;
	GLuint normalLoc, tangentLoc, binormalLoc;
	GLuint uvLoc;
	GLuint lightPosLoc;

	float lpx, lpy, lpz;
};
