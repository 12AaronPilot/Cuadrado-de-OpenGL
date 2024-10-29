#include "CMCTexture.h"
#include "../../objects/CCubo.h"
#include "../shaders/ShaderBase.h"

CMCTexture::CMCTexture(CShaderBase *shader)
	: CMeshBase(shader)
{
	setGeometry();
}

void CMCTexture::setGeometry()
{
	GLfloat points[] = {
		0.5f, -0.5f, 0.5f,  -0.5f,  0.5f, 0.5f, 	-0.5f,  -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,   0.5f,  0.5f, 0.5f, 	-0.5f,  0.5f, 0.5f,

		0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, 0.5f, 	-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,  0.5f, -0.5f, 0.5f, 	-0.5f, -0.5f, 0.5f,

		0.5f, -0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,  0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f,

		0.5f, 0.5f, 0.5f,  -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,  0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f,

		-0.5f, -0.5f, -0.5f,  0.5f, 0.5f, -0.5f, 	0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,  -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f,

		-0.5f, -0.5f, 0.5f,  -0.5f, 0.5f, -0.5f, 	-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,  -0.5f, 0.5f, 0.5f, 	-0.5f, 0.5f, -0.5f,
	};

	GLfloat uves[] = {
		0.5f, 0.5f,   0.25f, 0.25f,   0.25f, 0.5f, 
		0.5f, 0.5f,   0.5f, 0.25f,   0.25f, 0.25f, 
															  
		0.5f, 0.5f,   0.25f, 0.25f,   0.25f, 0.5f,
		0.5f, 0.5f,   0.5f, 0.25f,   0.25f, 0.25f,
															  
		0.5f, 0.5f,   0.25f, 0.25f,   0.25f, 0.5f,
		0.5f, 0.5f,   0.5f, 0.25f,   0.25f, 0.25f,
															  
		0.5f, 0.5f,   0.25f, 0.25f,   0.25f, 0.5f,
		0.5f, 0.5f,   0.5f, 0.25f,   0.25f, 0.25f,
															  
		0.5f, 0.5f,   0.25f, 0.25f,   0.25f, 0.5f,
		0.5f, 0.5f,   0.5f, 0.25f,   0.25f, 0.25f,
															  
		0.5f, 0.5f,   0.25f, 0.25f,   0.25f, 0.5f,
		0.5f, 0.5f,   0.5f, 0.25f,   0.25f, 0.25f,
	};

	int pointCount = sizeof(points) / sizeof(points[0]);
	int uvesCount = sizeof(uves) / sizeof(uves[0]);

	primCount = pointCount / 3;

	prepareVertexColorData(points, pointCount, uves, uvesCount);
}

void CMCTexture::prepareVertexColorData(
	GLfloat *puntos, int pointCount, GLfloat *uves, int uvesCount)
{
	GLuint vbo[2];
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, &vbo[0]);

	GLuint posLoc = mShader->getShaderBuffer(eBufferType::POSITION);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pointCount * sizeof(GLfloat), puntos, GL_STATIC_DRAW);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(posLoc);

	GLuint uveLoc = mShader->getShaderBuffer(eBufferType::TEXTURE);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, uvesCount * sizeof(GLfloat), uves, GL_STATIC_DRAW);
	glVertexAttribPointer(uveLoc, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(uveLoc);
}


