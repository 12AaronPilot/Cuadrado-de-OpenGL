#pragma once
class CMeshBase;

class CCubo
{
public:
	CCubo(CMeshBase *cube);
	virtual ~CCubo(void);

	void setPosition(float x, float y, float z);

	bool Initialize();
	void getWorldMatrix(float worldm[16]);

private:
	CMeshBase *mMesh;
	float px, py, pz;

};
