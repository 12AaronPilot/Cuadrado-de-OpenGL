#include "CMeshCubo.h"
#include "../../objects/CCubo.h"
#include "../shaders/ShaderBase.h"

CMeshCubo::CMeshCubo(CShaderBase *shader)
	: CMeshBase(shader)
{
	setGeometry();
}

void CMeshCubo::setGeometry()
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

	GLfloat normals[] = {
		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

		0.0f, -1.0f, 0.0f,	0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,	0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		1.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,	0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,	0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, -1.0f,	0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,	0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f

		- 1.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,	-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f
	};

	int pointCount = sizeof(points) / sizeof(points[0]);
	int normalCount = sizeof(normals) / sizeof(normals[0]);

	primCount = pointCount / 3;

	prepareVertexColorData(points, pointCount, normals, normalCount);
}

void CMeshCubo::prepareVertexColorData(
	GLfloat *puntos, int pointCount, GLfloat *normals, int normalCount)
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

	GLuint norLoc = mShader->getShaderBuffer(eBufferType::NORMAL);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normalCount * sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(norLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(norLoc);
}


