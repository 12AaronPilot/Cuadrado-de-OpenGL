#include "OGLApp.h"
#include <string>
#include <iostream>
#include "mathfunc.h"

#include "../graphics/shaders/ShaderColor.h"
#include "../graphics/textures/lodepng.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

OGLApp::OGLApp(void)
	: WinApplication()
{
}

OGLApp::~OGLApp(void)
{	
}

bool OGLApp::InitializeScene()
{
	bool result;
	HWND fakeWND = CreateWindow(
		GetLpszClassName(), L"Fake Window",      
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 
		0, 0,
		1, 1,
		NULL, NULL,
		GetAppInstance(), NULL);

	auto effr = GetLastError();
	HDC fakeDC = GetDC(fakeWND);
	if (!fakeDC) {
		return false;
	}

	PIXELFORMATDESCRIPTOR fakePFD;
	ZeroMemory(&fakePFD, sizeof(fakePFD));
	fakePFD.nSize = sizeof(fakePFD);
	fakePFD.nVersion = 1;
	fakePFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	fakePFD.iPixelType = PFD_TYPE_RGBA;
	fakePFD.cColorBits = 32;
	fakePFD.cAlphaBits = 8;
	fakePFD.cDepthBits = 24;
	int fakePFDID = ChoosePixelFormat(fakeDC, &fakePFD);
	if (fakePFDID == 0) {	
		return false;
	}

	// temporary begin
	{
		int error = SetPixelFormat(fakeDC, fakePFDID, &fakePFD);
		if (error != 1) {
			return false;
		}

		HGLRC fakeRC = wglCreateContext(fakeDC);
		if (!fakeRC) {
			return false;
		}

		error = wglMakeCurrent(fakeDC, fakeRC);
		if (error != 1) {
			return false;
		}

		result = LoadExtensionList();
		if (!result) {
			return false;
		}

		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(fakeRC);
		fakeRC = NULL;
	}
	// Temporary end
	ReleaseDC(fakeWND, fakeDC);
	fakeDC = 0;

	return true;
}

bool OGLApp::InitializeOpenGL(int screenWidth, int screenHeight, bool vsync)
{
	int result;

	m_deviceContext = GetDC(GetAppHwnd());
	if (!m_deviceContext) {
		return false;
	}

	int attributeListInt[19];
	attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;

	attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;

	attributeListInt[4] = WGL_ACCELERATION_ARB;
	attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;

	attributeListInt[6] = WGL_COLOR_BITS_ARB;
	attributeListInt[7] = 24;

	attributeListInt[8] = WGL_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;

	attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;

	attributeListInt[12] = WGL_SWAP_METHOD_ARB;
	attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;

	attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
	attributeListInt[15] = WGL_TYPE_RGBA_ARB;

	attributeListInt[16] = WGL_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;

	attributeListInt[18] = 0;

	unsigned int formatCount;
	int pixelFormat[1];
	result = wglChoosePixelFormatARB(m_deviceContext, attributeListInt, NULL, 1, pixelFormat, &formatCount);
	if (result != 1) {
		return false;
	}

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor{ 0 };
	result = SetPixelFormat(m_deviceContext, pixelFormat[0], &pixelFormatDescriptor);
	if (result != 1) {
		auto effr = GetLastError();
		return false;
	}
	int attributeList[5];
	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 3;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 3;
	attributeList[4] = 0;

	m_renderingContext = wglCreateContextAttribsARB(m_deviceContext, 0, attributeList);
	if (m_renderingContext == NULL)	{
		return false;
	}
	result = wglMakeCurrent(m_deviceContext, m_renderingContext);
	if (result != 1) {
		return false;
	}
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glFrontFace(GL_CW);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_TEXTURE_2D);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_BLEND);
	//glDisable(GL_ALPHA_TEST);

	char *vendorString = (char*)glGetString(GL_VENDOR);
	char *rendererString = (char*)glGetString(GL_RENDERER);
	char *versionString = (char*)glGetString(GL_VERSION);

	std::cout << vendorString << "-->" << rendererString 
		<< " / " << versionString << std::endl;

	if (vsync)	{ result = wglSwapIntervalEXT(1); }
	else				{	result = wglSwapIntervalEXT(0);	}

	if (result != 1) { return false; }

	colorShader = new CShaderColor();
	colorShader->initializeShader("data/color.vxs", "data/color.pxs");

	colorShaderTWO = new CShaderColor();
	colorShaderTWO->initializeShader("data/color.vxs", "data/color.pxs");

	GLfloat points[] = {
		-2.0f,  2.0f, 2.0f, 
		-2.0f, -2.0f, 2.0f, 
		 2.0f, -2.0f, 2.0f, 
		 2.0f,  2.0f, 2.0f,

		-2.0f,  2.0f, -2.0f,
		-2.0f, -2.0f, -2.0f,
		 2.0f, -2.0f, -2.0f,
		 2.0f,  2.0f, -2.0f
	};

	GLushort indices[] = {
		0,1,2,
		0,2,3,
		3,2,6,
		3,6,7,
		7,6,5,
		7,5,4,
		4,5,1,
		4,1,0,
		0,3,7,
		0,7,4,
		1,5,6,
		1,6,2
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,

		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	int pointCount = sizeof(points) / sizeof(points[0]);
	int colorsCount = sizeof(colors) / sizeof(colors[0]);

	primCount = static_cast<int>(pointCount / 3.f);
	indicesCount = sizeof(indices) / sizeof(indices[0]);
	/////--------OO

	GLfloat pointsTWO[] = {
	-2.0f,  0.0f, 0.0f,
	 0.0f,  0.0f, 3.4641f,
	 2.0f,  0.0f, 0.0f,
	 
	 0.0f,  3.4641f, 1.7320f
	};

	GLushort indicesTWO[] = {
		0,2,1,
		0,1,3,
		1,2,3,
		0,3,2
	};

	GLfloat colorsTWO[] = {
		1.0f, 0.5f, 0.7f,
		1.0f, 0.5f, 0.7f,
		1.0f, 0.5f, 0.7f,

		1.0f, 0.0f, 0.0f,
	};

	int pointCountTWO = sizeof(pointsTWO) / sizeof(pointsTWO[0]);
	int colorsCountTWO = sizeof(colorsTWO) / sizeof(colorsTWO[0]);

	primCountTWO = static_cast<int>(pointCountTWO / 3.f);
	indicesCountTWO = sizeof(indicesTWO) / sizeof(indicesTWO[0]);

	/////---------

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, &vbo[0]);
	//--------------------------------------------------------------
	GLuint posLoc = colorShader->getPosLoc();
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pointCount * sizeof(GLfloat), points, GL_STATIC_DRAW);

	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(posLoc);
	//--------------------------------------------------------------
	GLuint colorLoc = colorShader->getColorLoc();
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, colorsCount * sizeof(GLfloat), colors, GL_STATIC_DRAW);

	glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(colorLoc);
	//--------------------------------------------------------------

	glGenBuffers(1, &indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(GLushort), indices, GL_STATIC_DRAW);

	//----------------------------------------------------------------------------------------------------OTHER

	glGenVertexArrays(1, &vaoTWO);
	glBindVertexArray(vaoTWO);

	glGenBuffers(2, &vboTWO[0]);
	//--------------------------------------------------------------
	GLuint posLoc2 = colorShaderTWO->getPosLoc();
	glBindBuffer(GL_ARRAY_BUFFER, vboTWO[0]);
	glBufferData(GL_ARRAY_BUFFER, pointCountTWO * sizeof(GLfloat), pointsTWO, GL_STATIC_DRAW);

	glVertexAttribPointer(posLoc2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(posLoc2);
	//--------------------------------------------------------------
	GLuint colorLoc2 = colorShaderTWO->getColorLoc();
	glBindBuffer(GL_ARRAY_BUFFER, vboTWO[1]);
	glBufferData(GL_ARRAY_BUFFER, colorsCountTWO * sizeof(GLfloat), colorsTWO, GL_STATIC_DRAW);

	glVertexAttribPointer(colorLoc2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(colorLoc2);
	//--------------------------------------------------------------

	glGenBuffers(1, &indexBufferIdTWO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferIdTWO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCountTWO * sizeof(GLushort), indicesTWO, GL_STATIC_DRAW);




	return true;
}


void OGLApp::BuildObjects()
{

}

void OGLApp::ReleaseObjects()
{
	glDisableVertexAttribArray(vbo[0]);
	glDisableVertexAttribArray(vbo[1]);

	GLuint posLoc = colorShader->getPosLoc();
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glDeleteBuffers(1, &posLoc);

	GLuint colorLoc = colorShader->getColorLoc();
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glDeleteBuffers(1, &colorLoc);

	delete colorShader;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &indexBufferId);

	///-----OTHER
	glDisableVertexAttribArray(vboTWO[0]);
	glDisableVertexAttribArray(vboTWO[1]);

	GLuint posLoc2 = colorShaderTWO->getPosLoc();
	glBindBuffer(GL_ARRAY_BUFFER, vboTWO[0]);
	glDeleteBuffers(1, &posLoc);

	GLuint colorLoc2 = colorShaderTWO->getColorLoc();
	glBindBuffer(GL_ARRAY_BUFFER, vboTWO[1]);
	glDeleteBuffers(1, &colorLoc2);

	delete colorShaderTWO;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &indexBufferIdTWO);
}

void OGLApp::ProcessInput(float elapsedTime)
{
	static UCHAR pKeyBuffer[ 256 ];
	if ( !GetKeyboardState( pKeyBuffer ) ) return;

	const float sleept = 0.02f;
	static float ontime = 0.f;
	static bool iswait = false;

	if(iswait) {
		ontime += elapsedTime;
		if(ontime > sleept) {
			iswait = false;
			ontime = 0.f;
		} else { return; }
	}

	if(KEY_DOWN(VK_RIGHT)) {
		
		//iswait = true;
	}
	if(KEY_DOWN(VK_LEFT)) {
		
		//iswait = true;
	}
	if(KEY_DOWN(VK_UP)) {
		
		//iswait = true;
	}
	if(KEY_DOWN(VK_DOWN)) {
		
		//iswait = true;
	}
	if(KEY_DOWN(0x57)) { // W
	//	mpSceneMgr->ChangeCamera(0, 0, 1);
		iswait = true;
	}
	//if(KEY_DOWN(0x53)) {
	//	mpSceneMgr->ChangeCamera(0, 0, -1);
	//	iswait = true;
	//}
	//if ( pKeyBuffer[ VK_LEFT  ] & 0xF0 ) {
	//	mpSceneMgr->ChangeCamera(-1, 0, 0);
	//}
	//if ( pKeyBuffer[ VK_RIGHT ] & 0xF0 ) {
	//	mpSceneMgr->ChangeCamera(1, 0, 0);
	//}
	//if ( pKeyBuffer[ VK_UP  ] & 0xF0 ) {
	//	mpSceneMgr->ChangeCamera(0, 1, 0);
	//}
	//if ( pKeyBuffer[ VK_DOWN ] & 0xF0 ) {
	//	mpSceneMgr->ChangeCamera(0, -1, 0);
	//}
}

void OGLApp::MouseInput(short x, short y)
{
	//std::cout << "mousex: " << x << " / mousey: " << y << std::endl;
}

bool OGLApp::AppBegin()
{	
	//unsigned int w = 0, h = 0;
	GetWindowDims(scWidth, scHeight);

	std::cout << "Iniciando: " << scWidth << "," << scHeight << std::endl;

	InitializeScene();
	InitializeOpenGL(scWidth, scHeight, false);

	BuildObjects();

	timer.Reset();

	return true;
}


bool OGLApp::AppUpdate()
{
	timer.Tick();
	float elapsedTime = timer.DeltaTime();

	ProcessInput(elapsedTime);
	RECT rc;
	GetClientRect(GetAppHwnd(), &rc);

	glViewport(0, 0, rc.right - rc.left, rc.bottom - rc.top);
	glClearColor(0.3921f, 0.5843f, 0.9294f, 1.0f); // cornflower blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float perspectiveMatrix[4][4]{ 0 };

	//orthoMatrix4x4(-1.0f, 1.0f, -1.3333f, 1.3333f, -0.01f, 100.f, perspectiveMatrix);

	float angleOfView = 90.f;
	float nearDim = 0.1f;
	float farDim = 100.f;
	float imageAspectRatio = scWidth / (float)scHeight;
	float b, t, l, r;
	setPerspectiveBTLR(angleOfView, imageAspectRatio, nearDim, farDim, b, t, l, r);
	setFrustum4x4(b, t, l, r, nearDim, farDim, perspectiveMatrix);



	float identitymm[16];
	setIdentityMatrix(identitymm, 4);

	const float deltaAngRad = M_PI / 180.f * 30.f; // by angle in deg
	rotAng += deltaAngRad * elapsedTime;
	rotAng = rotAng > TWO_PI ? TWO_PI - rotAng : rotAng;

	float rotationMatrix[16] = {
		 cosf(rotAng),	0.f, sinf(rotAng),	0.f,
		 0.f,						1.f, 0.f,						0.f,
		-sinf(rotAng),	0.f, cosf(rotAng),	0.f,
		 0.f,						0.f, 0.f,						1.f
	};



	float viewMatrix[4][4]{ 0 };
	float eye[3]		{ 5.f, 2.5f, 8.f };
	float center[3]	{ 0.f, 0.f, 0.f };
	float up[3]			{ 0.f, 1.f, 0.f };

	lookAtRH(eye, center, up, viewMatrix);


	float* perspPtr = reinterpret_cast<float*>(perspectiveMatrix);
	float* viewPtr = reinterpret_cast<float*>(viewMatrix);
	
	glUseProgram(colorShader->getShaderProgram());

	colorShader->setWorldMatrix(identitymm);
	colorShader->setCamera(viewPtr, perspPtr);//identitymm);

	

	//colorShader->setCamera(identityMatrix, identityMatrix);


	glBindVertexArray(vao);
	//glDrawArrays(GL_TRIANGLES, 0, primCount);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_SHORT, (void*)0);


	//-------------------------OTHER
	glUseProgram(colorShaderTWO->getShaderProgram());

	colorShaderTWO->setWorldMatrix(identitymm);
	colorShaderTWO->setCamera(viewPtr, perspPtr);

	glBindVertexArray(vaoTWO);	
	//glDrawElements(GL_TRIANGLES, indicesCountTWO, GL_UNSIGNED_SHORT, (void*)0);


	colorShaderTWO->setWorldMatrix(rotationMatrix);
	colorShaderTWO->setCamera(viewPtr, perspPtr);

	glBindVertexArray(vaoTWO);
	//glDrawElements(GL_TRIANGLES, indicesCountTWO, GL_UNSIGNED_SHORT, (void*)0);

	glFlush();
	SwapBuffers(m_deviceContext);
	
	return true;
}

bool OGLApp::AppEnd()
{
	ReleaseObjects();
	return true;
}

bool OGLApp::Size(HWND AppHwnd, WPARAM Wparam, LPARAM Lparam)
{
	UINT width = LOWORD(Lparam);
	UINT height = HIWORD(Lparam);
	return true;
}

bool OGLApp::DisplayChange(HWND AppHwnd, WPARAM Wparam, LPARAM Lparam)
{
	InvalidateRect(AppHwnd, NULL, FALSE);
	return true;
}
