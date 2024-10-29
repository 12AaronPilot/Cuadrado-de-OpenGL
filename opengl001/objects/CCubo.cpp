#include "CCubo.h"
#include <string>
#include <iostream>
#include "../graphics/meshes/CMeshBase.h"
#include "../core/mathfunc.h"

CCubo::CCubo(CMeshBase *cube)
	: mMesh(cube)
{
	mMesh->addCube(this);
}

CCubo::~CCubo(void)
{	
}

void CCubo::setPosition(float x, float y, float z)
{
	px = x; py = y; pz = z;
}

bool CCubo::Initialize()
{
	
	return true;
}

void CCubo::getWorldMatrix(float worldm[16])
{
	setTranslationMatrix(worldm, px, py, pz);
}

