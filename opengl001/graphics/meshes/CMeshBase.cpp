#include "CMeshBase.h"
#include "../shaders/ShaderBase.h"
#include "../../objects/CCubo.h"

CMeshBase::CMeshBase(CShaderBase *shader)
	: mShader(shader)
{
	mShader->addMesh(this);
}

CMeshBase::~CMeshBase() 
{
	for (CCubo *cubo : mvCubes) {
		delete cubo; cubo = nullptr;
	}
}

void CMeshBase::addCube(CCubo *cubo) 
{
	mvCubes.push_back(cubo);
}


