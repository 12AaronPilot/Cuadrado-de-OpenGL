#include "ShaderColor.h"
#include <fstream>

using namespace std;

CShaderColor::CShaderColor()
{
}

CShaderColor::~CShaderColor()
{
}

void CShaderColor::initializeParticularShader()
{
	GLuint programme = getShaderProgram();

	positionLoc = glGetAttribLocation(programme, "in_Position");
	colorLoc = glGetAttribLocation(programme, "in_Color");
}


