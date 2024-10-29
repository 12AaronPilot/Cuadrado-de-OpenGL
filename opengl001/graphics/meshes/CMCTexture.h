#pragma once
#include <vector>
#include "CMeshBase.h"

class CShaderBase;
class CCubo;

class CMCTexture : public CMeshBase
{
public:
	CMCTexture(CShaderBase *shader);

private:
	void setGeometry() override;
	void prepareVertexColorData(
		GLfloat *puntos, int pointCount, GLfloat *uves, int uvesCount);
};

