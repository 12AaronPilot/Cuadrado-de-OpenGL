#pragma once
#include <vector>
#include "CMeshBase.h"

class CShaderBase;
class CCubo;

class CMeshCubo : public CMeshBase
{
public:
	CMeshCubo(CShaderBase *shader);

private:
	void setGeometry() override;
	void prepareVertexColorData(
		GLfloat *puntos, int pointCount, GLfloat *normals, int normalCount);
};

