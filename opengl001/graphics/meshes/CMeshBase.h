#pragma once
#include <vector>
#include "../../core/opengl.h"
//#include "../shaders/ShaderBase.h"

class CShaderBase;
class CCubo;

class CMeshBase
{
public:
	CMeshBase(CShaderBase *shader);
	virtual ~CMeshBase();

	GLuint getVAO() { return vao; }

	void addCube(CCubo *cubo);
	std::vector<CCubo *> getCubeVector() { return mvCubes; }
	int getPrimitiveCount() { return primCount; }

protected:
	virtual void setGeometry() { };

protected:
	GLuint vao;

	CShaderBase *mShader;
	int primCount;

	std::vector<CCubo*> mvCubes;
};

