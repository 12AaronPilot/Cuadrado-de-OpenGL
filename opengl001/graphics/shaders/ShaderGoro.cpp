#include "ShaderGoro.h"
#include <fstream>
#include <vector>

using namespace std;

CShaderGoro::CShaderGoro()
{
}

CShaderGoro::~CShaderGoro()
{
}

void CShaderGoro::initializeParticularShader()
{
	GLuint programme = getShaderProgram();

	positionLoc = glGetAttribLocation(programme, "in_Position");
	normalLoc = glGetAttribLocation(programme, "in_Normal");

	pointLightLoc = glGetUniformLocation(programme, "pointLight");
	ambientLoc = glGetUniformLocation(programme, "ambient");

	KdLoc = glGetUniformLocation(programme, "Kd");
	KsLoc = glGetUniformLocation(programme, "Ks");
	KaLoc = glGetUniformLocation(programme, "Ka");

	n_specularLoc = glGetUniformLocation(programme, "n_specular");
	lightPosLoc = glGetUniformLocation(programme, "lightPos");
	eyePosLoc = glGetUniformLocation(programme, "eyePosition");
}

void CShaderGoro::setUniforms()
{
	float amc[] = { 0.8f,0.8f,0.8f };
	glUniform3fv(ambientLoc, 1, amc);

	float pli[] = { 0.2078f,0.4706f,1.f };
	glUniform3fv(pointLightLoc, 1, pli);

	glUniform1f(KdLoc, 0.7f);
	glUniform1f(KsLoc, 0.8f);
	glUniform1f(KaLoc, 0.5f);
	glUniform1f(n_specularLoc, 4.0f);

	float lpo[] = { 5.f, 5.f, 0.f };
	glUniform3fv(lightPosLoc, 1, lpo);
	//float eyp[] = { 7.f,4.f,7.f };
	//glUniform3fv(eyePosLoc, 1, eyp);
	glUniform3fv(eyePosLoc, 1, eyePos);
}

GLuint CShaderGoro::getShaderBuffer(eBufferType bufferType)
{
	switch (bufferType)
	{
	case eBufferType::POSITION:	return positionLoc; break;
	case eBufferType::NORMAL:	return normalLoc; break;
	default: break;
	}
	return GLuint();
}


