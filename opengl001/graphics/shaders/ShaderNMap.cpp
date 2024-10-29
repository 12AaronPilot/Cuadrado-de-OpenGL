#include "ShaderNMap.h"
#include <fstream>

using namespace std;

CShaderNMap::CShaderNMap()
	:lpx(1.f), lpy(1.f), lpz(1.f)
{
}

CShaderNMap::~CShaderNMap()
{
}

void CShaderNMap::initializeParticularShader()
{
	GLuint programme = getShaderProgram();

	positionLoc = glGetAttribLocation(programme, "in_Position");
	uvLoc = glGetAttribLocation(programme, "in_UV");
	normalLoc = glGetAttribLocation(programme, "in_Normal");
	tangentLoc = glGetAttribLocation(programme, "in_Tangent");
	binormalLoc = glGetAttribLocation(programme, "in_Binormal");


	lightPosLoc = glGetUniformLocation(programme, "lightPos");
}


void CShaderNMap::setUniforms()
{
	float pli[] = { lpx, lpy, lpz };
	glUniform3fv(lightPosLoc, 1, pli);
}
