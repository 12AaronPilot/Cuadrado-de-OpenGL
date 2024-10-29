#include "ShaderNone.h"
#include <fstream>

using namespace std;

CShaderNone::CShaderNone()
{
}

CShaderNone::~CShaderNone()
{
}

void CShaderNone::initializeParticularShader()
{
	GLuint programme = getShaderProgram();

	positionLoc = glGetAttribLocation(programme, "in_Position");	
}


