#pragma once
#include <vector>
#include "winapplication.h"
//#include "timer.h"
#include "GameTimer.h"
#include "opengl.h"

class CShaderBase;

class OGLApp : public WinApplication
{
private:
	bool AppBegin() override;
	bool AppUpdate() override;
	bool AppEnd() override;

	bool Size(HWND AppHwnd, WPARAM Wparam, LPARAM Lparam) override;
	bool DisplayChange(HWND AppHwnd, WPARAM Wparam, LPARAM Lparam) override;

	bool InitializeScene();
	bool InitializeOpenGL(int screenWidth, int screenHeight, bool vsync);

	void BuildObjects();
	void ReleaseObjects();
	void ProcessInput(float elapsedTime);

	void MouseInput(short x, short y) override;

public:
	OGLApp(void);
	virtual ~OGLApp(void);

private:
	HDC m_deviceContext;
	HGLRC m_renderingContext;

	RECT rc;
	//CTimer timer;
	GameTimer timer;

	unsigned int scWidth, scHeight;

	CShaderBase *colorShader;
	CShaderBase* colorShaderTWO;
	
	int primCount;
	int indicesCount;

	int primCountTWO;
	int indicesCountTWO;

	GLuint vao;	
	GLuint vbo[2];
	GLuint indexBufferId;

	GLuint vaoTWO;
	GLuint vboTWO[2];
	GLuint indexBufferIdTWO;

	GLuint textureLoc, bumpLoc;	

	float rotAng{ 0.f };
};
