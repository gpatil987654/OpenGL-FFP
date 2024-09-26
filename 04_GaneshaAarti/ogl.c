// Standard Headers
#include <windows.h> //Win 32 API
#include <stdio.h>	 //FileIO
#include <stdlib.h>	 //exit()
#include "ogl.h"	 //For Icon resource

#define _USE_MATH_DEFINES 1
#include <math.h>
// OpenGL Header Files
#include <gl/GL.h>
#include <gl/glu.h>

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Link with OpenGl Library
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")

// Global Function Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Ganapati(void);
void circle(GLfloat fxRadius, GLfloat fyRadius, GLfloat xCenter, GLfloat yCenter, GLfloat fAngleFrom, GLfloat fAngleTo);
void petals(void);
void lotus(void);
void AartiThali(void);
void ChainedLamp(void);

// Gloabal Variable Declaration
FILE *gpFILE = NULL;
HWND ghwnd = NULL;
DWORD dwStyle;
BOOL gbFullScreen = FALSE;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};
BOOL gbActive = FALSE;

// OpenGL Related Global Variables
PIXELFORMATDESCRIPTOR pfd;
int iPixelFormatIndex = 0;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

GLfloat lerp(GLfloat start, GLfloat end, GLfloat t)
{
	return (start + (end - start) * t);
}

GLfloat zRot = 0.0f;
GLfloat xTransArti = 0.0f;
GLfloat yTransArti = 0.0f;
GLfloat fArtiangle = 0.0f;
GLfloat fFlameMove = 0.0f;
GLint iFlameMovement = 0;
GLfloat fSmokeMove = 0.0f;
GLfloat fChainedLampMov = 0.0f;
GLfloat iChainedLampMov = 0;
GLboolean bStartAnimation = FALSE;
GLfloat fEyes = 0.0f;
GLboolean bOpenEyes = TRUE;

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function Declarations
	int initialise(void);
	void uninitialise(void);
	void display(void);
	void update(void);

	// Local Variable Declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");
	int iResult = 0;
	BOOL bDone = FALSE;

	// code
	gpFILE = fopen("Log.txt", "w");

	if (gpFILE == NULL)
	{
		MessageBox(NULL, TEXT("LOG FILE OPENING ERROR"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	fprintf(gpFILE, "Programme Started Successfully\n");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		szAppName,
		TEXT("MyWindow"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		GetSystemMetrics(SM_CXSCREEN) / 2.0 - WIN_WIDTH / 2.0,
		GetSystemMetrics(SM_CYSCREEN) / 2.0 - WIN_HEIGHT / 2.0,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ghwnd = hwnd;

	// Initialisation
	iResult = initialise();

	if (iResult != 0)
	{
		MessageBox(hwnd, TEXT("Initialisation Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		DestroyWindow(hwnd);
	}

	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	// GameLoop
	while (bDone == FALSE)
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT)
				bDone = TRUE;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{

			if (gbActive == TRUE)
			{
				// Render
				display();

				// Update
				update();
			}
		}
	}

	// Uninitialisation
	uninitialise();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Function Declarations
	void ToggleFullScreen(void);
	void resize(int, int);

	switch (iMsg)
	{
	case WM_SETFOCUS:
		gbActive = TRUE;
		break;

	case WM_KILLFOCUS:
		gbActive = FALSE;
		break;

	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_ERASEBKGND:
		return 0;

	case WM_KEYDOWN:

		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);

			break;

		case VK_SPACE:
			bStartAnimation = !bStartAnimation;
			PlaySound(TEXT("Aarti.wav"), NULL, SND_FILENAME | SND_ASYNC);
			break;
		}

		break;

	case WM_CHAR:

		switch (LOWORD(wParam))
		{
		case 'f':
		case 'F':

			ToggleFullScreen();
			break;
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void ToggleFullScreen(void)
{
	MONITORINFO mi = {sizeof(MONITORINFO)};

	// code
	if (gbFullScreen == FALSE)
	{ // 1
		// A
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			// a b c
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				// i
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);

				// ii
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}

		// B
		ShowCursor(FALSE);
		gbFullScreen = TRUE;
	}
	else
	{ // 2

		// A
		SetWindowPlacement(ghwnd, &wpPrev);

		// B
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);

		// C
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

		// D
		ShowCursor(TRUE);

		gbFullScreen = FALSE;
	}
}

int initialise(void)
{
	// Function Declarations

	// code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	// Initialisation of PIXELFORMATDESRIPTOR
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	ghdc = GetDC(ghwnd);

	if (ghdc == NULL)
	{
		fprintf(gpFILE, "GetDC() Failed\n");
		return -1;
	}

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0)
	{
		fprintf(gpFILE, "ChoosePixelFormat()  Failed\n");
		return -2;
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpFILE, "SetPixelFormat() Failed\n");
		return -3;
	}

	// Create OpenGL context from device context
	ghrc = wglCreateContext(ghdc);

	if (ghrc == NULL)
	{
		fprintf(gpFILE, "wglCreateContext() Failed\n");
		return -4;
	}

	// Make Rendering Context Current
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFILE, "wglMakeCurrent() Failed\n");
		return -5;
	}

	// Here OpenGL Starts
	// Set The Clear Color Of Window To Blue
	glClearColor(118.0f / 255.0f, 215.0f / 255.0f, 196.0f / 255.0f, 1.0f);
	// glEnable(GL_LINE_SMOOTH);
	return 0;
}

void resize(int width, int height)
{
	// code
	if (height <= 0)
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/*
		if (width < height)
		{
			glOrtho(-1.0f, 1.0f, -(GLfloat)height / (GLfloat)width, (GLfloat)height / (GLfloat)width, -1.0f, 1.0f);
		}
		else
		{
			glOrtho(-(GLfloat)width / (GLfloat)height, (GLfloat)width / (GLfloat)height, -1.0f, 1.0f, -1.0f, 1.0f);
		}
	*/
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void)
{
	int num;
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Background
	num = 50;
	for (int i = 0; i < num; i++)
	{
		glColor3f(1.0f, lerp(0.3f, 1.0f, (GLfloat)i / (GLfloat)num), 0.0f);
		glBegin(GL_POLYGON);
		circle(lerp(1.5f, 0.0f, (GLfloat)i / (GLfloat)num), lerp(1.5f, 0.0f, (GLfloat)i / (GLfloat)num), 0.0f, 0.0f, 0.0f, 360.0f);
		glEnd();
	}

	// Black Shadow Below Ganapti Asan
	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(85.0f, 1.0f, 0.0f, 0.0f);
	num = 50;
	for (int i = 0; i < num; i++)
	{
		glColor3f(lerp(1.0f, 0.1f, (GLfloat)i / (GLfloat)num), lerp(0.6f, 0.1f, (GLfloat)i / (GLfloat)num), 0.0f);
		glBegin(GL_POLYGON);
		circle(lerp(0.8f, 0.0f, (GLfloat)i / (GLfloat)num), lerp(0.8f, 0.0f, (GLfloat)i / (GLfloat)num), 0.0f, 0.0f, 0.0f, 360.0f);
		glEnd();
	}
	glPopMatrix();
	// Background circular Design behind head
	/*
	num = 50;
	for (int i = 0; i < num; i++)
	{
		glColor3f(lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num), 1.0f);
		glBegin(GL_POLYGON);
		circle(lerp(0.5f, 0.0f, (GLfloat)i / (GLfloat)num), lerp(0.5f, 0.0f, (GLfloat)i / (GLfloat)num), 0.0f, 0.5f, 0.0f, 360.0f);
		glEnd();
	}
*/
	// Rays
	num = 100;
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	// glColor3f(1.0f, 0.7f, 0.0f);
	for (int i = 0; i < num; i++)
	{
		glColor3f(1.0f, 0.8f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 0.8f);
		glVertex2f(0.5f * cos(2 * M_PI * (GLfloat)i / (GLfloat)num), 0.5f * sin(2 * M_PI * (GLfloat)i / (GLfloat)num));
		i++;
		glVertex2f(0.5f * cos(2 * M_PI * (GLfloat)i / (GLfloat)num), 0.5f * sin(2 * M_PI * (GLfloat)i / (GLfloat)num));
	}
	glEnd();
	glPopMatrix();

	Ganapati();

	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glTranslatef(xTransArti, yTransArti, 0.0f);
	AartiThali();
	glPopMatrix();

	ChainedLamp();
	SwapBuffers(ghdc);
}

void update(void)
{
	// code

	if (bStartAnimation)
	{

		zRot += 0.1f;
		if (zRot >= 360.0f)
			zRot -= 360.0f;

		fArtiangle += 0.01f;
		if (fArtiangle >= 360.0f)
			fArtiangle -= 360.0f;

		fSmokeMove += 0.2f;
		if (fSmokeMove >= 100.0f)
		{
			fSmokeMove -= 100.0f;
		}

		fFlameMove += 0.4f;
		if (fFlameMove >= 100.0f)
		{
			fFlameMove -= 100.0f;
			iFlameMovement = !iFlameMovement;
		}
		xTransArti = 0.3f * cos(-fArtiangle);
		yTransArti = 0.15f * sin(-fArtiangle);

		if (iChainedLampMov == 0)
		{
			fChainedLampMov += 0.0001f;
			if (fChainedLampMov >= 0.03f)
				iChainedLampMov = 1;
		}
		else
		{
			fChainedLampMov -= 0.0001f;
			if (fChainedLampMov <= -0.03f)
				iChainedLampMov = 0;
		}

		if (bOpenEyes)
		{
			fEyes += 0.01f;
			if (fEyes >= 1.0f)
				bOpenEyes = !bOpenEyes;
		}
		else
		{
			fEyes -= 0.01f;
			if (fEyes <= 0.0f)
				bOpenEyes = !bOpenEyes;
		}
	}
}

void uninitialise(void)
{
	// Function Declaration
	void ToggleFullScreen(void);

	// code
	// If Application is Exiting in fullScreen
	if (gbFullScreen == TRUE)
		ToggleFullScreen();

	// Make the ghdc as current Dc
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}
	// Destroy Rendering context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	// Relase ghdc
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	// Destroy Window
	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	// close the log File
	if (gpFILE)
	{
		fprintf(gpFILE, "Programme Ended Successfully\n");
		fclose(gpFILE);
		gpFILE = NULL;
	}
}

void Panati(void)
{
	// Panati
	glBegin(GL_POLYGON);
	glColor3f(186.0f / 255.0f, 74.0f / 255.0f, 0);
	circle(0.06f, 0.05f, 0.0f, 0.03f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.06f, 0.05f, 0.0f, 0.03f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(186.0f / 255.0f, 74.0f / 255.0f, 0);
	circle(0.06f, 0.025f, 0.0f, 0.03f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.06f, 0.025f, 0.0f, 0.03f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(110.0f / 255.0f, 44.0f / 255.0f, 0);
	circle(0.05f, 0.013f, 0.0f, 0.03f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.05f, 0.013f, 0.0f, 0.03f, 0.0f, 360.0f);
	glEnd();

	for (int i = 0; i < 10; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(1.0f, lerp(0.5f, 1.0f, (GLfloat)i / 10.0f), 0.0f);
		circle(lerp(0.05f, 0.0f, (GLfloat)i / 10.0f), lerp(0.013f, 0.0f, (GLfloat)i / 10.0f), 0.0f, 0.03f, 0.0f, 360.0f);
		glEnd();
	}

	// Flame

	GLfloat xFlameTop;
	// GLfloat kn = -0.01f;
	if (iFlameMovement == 0)
	{
		xFlameTop = lerp(-0.01f, 0.01f, fFlameMove / 100.0f);
	}
	else
	{
		xFlameTop = lerp(0.01f, -0.01f, fFlameMove / 100.0f);
	}
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 10; i++)
	{
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex2f(-0.013f, 0.05f);
		glVertex2f(0.013f, 0.05f);
		glColor3f(1.0f, lerp(0.0f, 1.0f, (GLfloat)i / 10.0f), 0.0f);
		glVertex2f(xFlameTop, lerp(0.1, 0.05, (GLfloat)i / 10.0f));
	}

	glEnd();

	for (int i = 0; i < 10; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(1.0f, lerp(0.5f, 1.0f, (GLfloat)i / 10.0f), 0.0f);
		circle(lerp(0.013f, 0.0f, (GLfloat)i / 10.0f), lerp(0.013f, 0.0f, (GLfloat)i / 10.0f), 0.0f, 0.05f, 0.0f, 360.0f);
		glEnd();
	}

	//  Vat
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.03f);
	glVertex2f(0.0f, 0.05f);
	glEnd();
}

void ChainedLamp(void)
{
	GLfloat fGoldenColor[3] = {1, 223.0 / 255.0, 0};
	int num = 20;
	GLfloat x = -0.9f;

	for (int i = 0; i < 22; i++)
	{
		glBegin(GL_LINE_LOOP);
		glColor3fv(fGoldenColor);
		circle(0.01f, 0.01f, lerp(x, x + fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num), 0.0f, 360.0f);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(lerp(x, x + fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num) - 0.01f);
		glVertex2f(lerp(x, x + fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)(i + 1) / (GLfloat)num) + 0.01f);

		glEnd();
	}

	glPushMatrix();
	glTranslatef(x + fChainedLampMov, -0.1f, 0.0f);
	Panati();
	glPopMatrix();

	// num = 23;
	x = -0.7f;
	for (int i = 0; i < 22; i++)
	{
		glBegin(GL_LINE_LOOP);
		glColor3fv(fGoldenColor);
		circle(0.01f, 0.01f, lerp(x, x + fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num), 0.0f, 360.0f);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(lerp(x, x + fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num) - 0.01f);
		glVertex2f(lerp(x, x + fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)(i + 1) / (GLfloat)num) + 0.01f);

		glEnd();
	}
	glPushMatrix();
	glTranslatef(x + fChainedLampMov, -0.1f, 0.0f);
	Panati();
	glPopMatrix();

	x = -0.8f;
	for (int i = 0; i < 20; i++)
	{
		glBegin(GL_LINE_LOOP);
		glColor3fv(fGoldenColor);
		circle(0.01f, 0.01f, lerp(x, x - fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num), 0.0f, 360.0f);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(lerp(x, x - fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num) - 0.01f);
		glVertex2f(lerp(x, x - fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)(i + 1) / (GLfloat)num) + 0.01f);

		glEnd();
	}
	glPushMatrix();
	glTranslatef(x - fChainedLampMov, 0.0f, 0.0f);
	Panati();
	glPopMatrix();

	// right Side
	x = 0.9f;
	for (int i = 0; i < 22; i++)
	{
		glBegin(GL_LINE_LOOP);
		glColor3fv(fGoldenColor);
		circle(0.01f, 0.01f, lerp(x, x - fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num), 0.0f, 360.0f);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(lerp(x, x - fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num) - 0.01f);
		glVertex2f(lerp(x, x - fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)(i + 1) / (GLfloat)num) + 0.01f);

		glEnd();
	}
	glPushMatrix();
	glTranslatef(x - fChainedLampMov, -0.1f, 0.0f);
	Panati();
	glPopMatrix();

	// num = 23;
	x = 0.7f;
	for (int i = 0; i < 22; i++)
	{
		glBegin(GL_LINE_LOOP);
		glColor3fv(fGoldenColor);
		circle(0.01f, 0.01f, lerp(x, x - fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num), 0.0f, 360.0f);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(lerp(x, x - fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num) - 0.01f);
		glVertex2f(lerp(x, x - fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)(i + 1) / (GLfloat)num) + 0.01f);

		glEnd();
	}
	glPushMatrix();
	glTranslatef(x - fChainedLampMov, -0.1f, 0.0f);
	Panati();
	glPopMatrix();

	x = 0.8f;
	for (int i = 0; i < 20; i++)
	{
		glBegin(GL_LINE_LOOP);
		glColor3fv(fGoldenColor);
		circle(0.01f, 0.01f, lerp(x, x + fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num), 0.0f, 360.0f);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(lerp(x, x + fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)i / (GLfloat)num) - 0.01f);
		glVertex2f(lerp(x, x + fChainedLampMov, (GLfloat)i / (GLfloat)num), lerp(1.0f, 0.0f, (GLfloat)(i + 1) / (GLfloat)num) + 0.01f);

		glEnd();
	}
	glPushMatrix();
	glTranslatef(x + fChainedLampMov, 0.0f, 0.0f);
	Panati();
	glPopMatrix();
}

void AartiThali(void)
{

	// Base

	glBegin(GL_QUADS);
	glColor3f(245.0f / 255.0f, 176.0f / 255.0f, 65.0f / 255.0f);
	glVertex2f(0.2f, 0.0f);
	glVertex2f(-0.2f, 0.0f);
	glVertex2f(-0.13f, -0.11f);
	glVertex2f(0.13f, -0.11f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.2f, 0.0f);
	glVertex2f(-0.13f, -0.11f);
	glVertex2f(0.13f, -0.11f);
	glVertex2f(0.2f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(245.0f / 255.0f, 176.0f / 255.0f, 65.0f / 255.0f);
	circle(0.13f, 0.02f, 0.0f, -0.11f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.13f, 0.02f, 0.0f, -0.11f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(244.0f / 255.0f, 208.0f / 255.0f, 63.0f / 255.0f);
	circle(0.2f, 0.1f, 0.0f, 0.0f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.2f, 0.1f, 0.0f, 0.0f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(243.0f / 255.0f, 156.0f / 255.0f, 18.0f / 255.0f);
	circle(0.18f, 0.09f, 0.0f, 0.01f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.18f, 0.09f, 0.0f, 0.01f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(214.0f / 255.0f, 137.0f / 255.0f, 16.0f / 255.0f);
	circle(0.16f, 0.065f, 0.0f, -0.01f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.16f, 0.065f, 0.0f, -0.01f, 0.0f, 360.0f);
	glEnd();

	// Panati
	glBegin(GL_POLYGON);
	glColor3f(186.0f / 255.0f, 74.0f / 255.0f, 0);
	circle(0.06f, 0.05f, 0.0f, 0.03f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.06f, 0.05f, 0.0f, 0.03f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(186.0f / 255.0f, 74.0f / 255.0f, 0);
	circle(0.06f, 0.025f, 0.0f, 0.03f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.06f, 0.025f, 0.0f, 0.03f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(110.0f / 255.0f, 44.0f / 255.0f, 0);
	circle(0.05f, 0.013f, 0.0f, 0.03f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.05f, 0.013f, 0.0f, 0.03f, 0.0f, 360.0f);
	glEnd();

	for (int i = 0; i < 10; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(1.0f, lerp(0.5f, 1.0f, (GLfloat)i / 10.0f), 0.0f);
		circle(lerp(0.05f, 0.0f, (GLfloat)i / 10.0f), lerp(0.013f, 0.0f, (GLfloat)i / 10.0f), 0.0f, 0.03f, 0.0f, 360.0f);
		glEnd();
	}

	// Flame

	GLfloat xFlameTop;
	// GLfloat kn = -0.01f;
	if (iFlameMovement == 0)
	{
		xFlameTop = lerp(-0.01f, 0.01f, fFlameMove / 100.0f);
	}
	else
	{
		xFlameTop = lerp(0.01f, -0.01f, fFlameMove / 100.0f);
	}
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 10; i++)
	{
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex2f(-0.013f, 0.05f);
		glVertex2f(0.013f, 0.05f);
		glColor3f(1.0f, lerp(0.0f, 1.0f, (GLfloat)i / 10.0f), 0.0f);
		glVertex2f(xFlameTop, lerp(0.1, 0.05, (GLfloat)i / 10.0f));
	}

	glEnd();

	for (int i = 0; i < 10; i++)
	{
		glBegin(GL_POLYGON);
		glColor3f(1.0f, lerp(0.5f, 1.0f, (GLfloat)i / 10.0f), 0.0f);
		circle(lerp(0.013f, 0.0f, (GLfloat)i / 10.0f), lerp(0.013f, 0.0f, (GLfloat)i / 10.0f), 0.0f, 0.05f, 0.0f, 360.0f);
		glEnd();
	}

	//  Vat
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.03f);
	glVertex2f(0.0f, 0.05f);
	glEnd();

	// Agarbatti
	// stand
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 1.0f);
	glVertex2f(0.12f, 0.06f);
	glVertex2f(0.08f, 0.06f);
	glVertex2f(0.07f, 0.01f);
	glVertex2f(0.13f, 0.01f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.08f, 0.06f);
	glVertex2f(0.07f, 0.01f);
	glVertex2f(0.13f, 0.01f);
	glVertex2f(0.12f, 0.06f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 1.0f);
	circle(0.03f, 0.01f, 0.10f, 0.01f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.03f, 0.01f, 0.10f, 0.01f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 1.0f);
	circle(0.02f, 0.01f, 0.10f, 0.06f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.02f, 0.01f, 0.10f, 0.06f, 0.0f, 360.0f);
	glEnd();

	static GLfloat fyAgarbattiReduce = 0.0f;
	static GLfloat fxAgarbattiReduce = 0.0f;

	// Holes for Agarbatti
	glEnable(GL_POINT_SMOOTH);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(0.105f, 0.06f);
	glVertex2f(0.09f, 0.06f);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glPointSize(1.0f);

	// Stick
	glBegin(GL_LINES);
	glColor3f(160.0f / 255.0f, 64.0f / 255.0f, 0);
	glVertex2f(0.1075f, 0.08f);
	glVertex2f(0.105f, 0.06f);
	glEnd();

	glBegin(GL_LINES);
	// Brown Color
	glColor3f(160.0f / 255.0f, 64.0f / 255.0f, 0);
	glVertex2f(0.0875f, 0.08f);
	glVertex2f(0.09f, 0.06f);
	glEnd();

	// Main agarbatti
	if ((0.25f - fyAgarbattiReduce) >= 0.08)
	{
		fyAgarbattiReduce += 0.000004f;
		fxAgarbattiReduce = (0.13f - 0.11f) / (0.25f - 0.08f) * fyAgarbattiReduce;

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(0.13f - fxAgarbattiReduce, 0.25f - fyAgarbattiReduce);
		glVertex2f(0.125f - fxAgarbattiReduce, 0.25f - fyAgarbattiReduce);
		glVertex2f(0.105f, 0.08f);
		glVertex2f(0.11f, 0.08f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(0.07f + fxAgarbattiReduce, 0.25f - fyAgarbattiReduce);
		glVertex2f(0.065f + fxAgarbattiReduce, 0.25f - fyAgarbattiReduce);
		glVertex2f(0.085f, 0.08f);
		glVertex2f(0.09f, 0.08f);
		glEnd();

		glPointSize(4.0f);
		glBegin(GL_POINTS);
		glColor3f(lerp(0.5f, 1.0f, zRot / 180.0f), lerp(0.5f, 0.0f, zRot / 180.0f), lerp(0.5f, 0.0f, zRot / 180.0f));
		glVertex2f(0.1275f - fxAgarbattiReduce, 0.25f - fyAgarbattiReduce);
		glVertex2f(0.0675f + fxAgarbattiReduce, 0.25f - fyAgarbattiReduce);
		glEnd();
		glPointSize(1.0f);

		// Agarbatti smoke

		glBegin(GL_LINE_STRIP);
		glColor3f(0.5f, 0.5f, 0.5f);
		for (int i = 0; i < fSmokeMove; i++)
		{
			glVertex2f(0.1275f - fxAgarbattiReduce + 0.01f * sin(2 * M_PI * (GLfloat)i / 100.0f), lerp(0.26f - fyAgarbattiReduce, 0.35f - fyAgarbattiReduce, (GLfloat)i / 100.0f));
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(0.5f, 0.5f, 0.5f);
		for (int i = 0; i < fSmokeMove; i++)
		{
			glVertex2f(0.0675f + fxAgarbattiReduce + 0.01f * sin(2 * M_PI * (GLfloat)i / 100.0f), lerp(0.26f - fyAgarbattiReduce, 0.35f - fyAgarbattiReduce, (GLfloat)i / 100.0f));
		}
		glEnd();
	}
	// Haldi-Cunko
	// Haldi
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 1.0f);
	circle(0.04f, 0.03f, 0.03f, -0.02f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.03f, 0.03f, -0.02f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 0.0f);
	circle(0.04f, 0.015f, 0.03f, -0.02f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.015f, 0.03f, -0.02f, 0.0f, 360.0f);
	glEnd();

	// Cunko
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 1.0f);
	circle(0.04f, 0.03f, -0.07f, -0.02f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.03f, -0.07f, -0.02f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	circle(0.04f, 0.015f, -0.07f, -0.02f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.015f, -0.07f, -0.02f, 0.0f, 360.0f);
	glEnd();
}

void Ganapati(void)
{
	GLfloat fSkinColor[3] = {0.98f, 0.592f, 0.129f};
	GLfloat fDhotiColor[3] = {1.0f, 0.29f, 0.0f};
	GLfloat fGoldenColor[3] = {1, 223.0 / 255.0, 0};
	GLfloat fRedishPink[3] = {1, 0, 0.2};
	GLfloat fAsanColor[3] = {0.388f, 0.204f, 0.012f};
	GLfloat fSkinColorDark[3] = {1.00f, 0.592f, 0.129f};

	int num = 0.0f;

	glLineWidth(2.0f);
	// Mukut

	// Upper Triangle
	glBegin(GL_TRIANGLES);
	glColor3fv(fGoldenColor);
	glVertex2f(0.0f, 0.84f);
	glVertex2f(-0.02f, 0.81f);
	glVertex2f(0.02f, 0.81f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.84f);
	glVertex2f(-0.02f, 0.81f);
	glVertex2f(0.02f, 0.81f);
	glEnd();

	// Upper circle
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.02f, 0.02f, 0.0f, 0.81f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.02f, 0.02f, 0.0f, 0.81f, 0.0f, 360.0f);
	glEnd();

	// Middle Circle
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.06f, 0.05f, 0.0f, 0.75f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.06f, 0.05f, 0.0f, 0.75f, 0.0f, 360.0f);
	glEnd();

	// Lower Circle
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.14f, 0.14f, 0.0f, 0.62f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.14f, 0.14f, 0.0f, 0.62f, 0.0f, 360.0f);
	glEnd();

	// Design on Mukut
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.14f, 0.14f, 0.0f, 0.55f, 13.0f, 165.0f);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	circle(0.13f, 0.13f, 0.0f, 0.55f, 0.0f, 360.0f);
	glEnd();

	glDisable(GL_POINT_SMOOTH);
	glPointSize(1.0f);

	// Circular Portion
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.04f, 0.04f, 0.0f, 0.69f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.04f, 0.0f, 0.69f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fRedishPink);
	circle(0.03f, 0.03f, 0.0f, 0.69f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.03f, 0.03f, 0.0f, 0.69f, 0.0f, 360.0f);
	glEnd();

	// Upper Hands
	// Left Hands
	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(fSkinColor);
	for (int i = 0; i < 100; i++)
	{
		glVertex2f(-0.20f + 0.18f * cos(M_PI + (GLfloat)i / 100.0f * M_PI / 2.0f), 0.35f + 0.2f * sin(M_PI + (GLfloat)i / 100.0f * M_PI / 2.0f));
		glVertex2f(-0.20f + 0.1f * cos(M_PI + (GLfloat)i / 100.0f * M_PI / 2.0f), 0.35f + 0.1f * sin(M_PI + (GLfloat)i / 100.0f * M_PI / 2.0f));
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.18f, 0.2f, -0.20f, 0.35f, 180.0f, 270.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.1f, 0.1f, -0.20f, 0.35f, 180.0f, 270.0f);
	glEnd();

	// Palm
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(-0.28f, 0.37f);
	glVertex2f(-0.40f, 0.37f);
	glVertex2f(-0.40f, 0.44f);
	glVertex2f(-0.28f, 0.44f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.40f, 0.37f);
	glVertex2f(-0.40f, 0.44f);
	glVertex2f(-0.28f, 0.44f);
	glVertex2f(-0.28f, 0.37f);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.06f, 0.02f, -0.34f, 0.37f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.06f, 0.02f, -0.34f, 0.37f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.08f, 0.08f, -0.30f, 0.35f, 90.0f, 180.0f);
	glEnd();

	// Thumb
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(-0.28f, 0.48f);
	glVertex2f(-0.30f, 0.48f);
	glVertex2f(-0.30f, 0.44f);
	glVertex2f(-0.28f, 0.44f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.30f, 0.48f);
	glVertex2f(-0.30f, 0.44f);
	glVertex2f(-0.28f, 0.44f);
	glVertex2f(-0.28f, 0.48f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	glVertex2f(-0.28f, 0.48f);
	circle(0.02f, 0.02f, -0.28f, 0.48f, 90.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.28f, 0.48f);
	circle(0.02f, 0.02f, -0.28f, 0.48f, 90.0f, 180.0f);
	glEnd();

	// Index Finger
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(-0.30f, 0.48f);
	glVertex2f(-0.325f, 0.48f);
	glVertex2f(-0.325f, 0.44f);
	glVertex2f(-0.30f, 0.44f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.325f, 0.48f);
	glVertex2f(-0.325f, 0.44f);
	glVertex2f(-0.30f, 0.44f);
	glVertex2f(-0.30f, 0.48f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, -0.3125f, 0.48f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.3125f, 0.48f, 0.0f, 180.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, -0.3125f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.3125f, 0.44f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.3125f, 0.44f, 0.0f, 180.0f);
	glEnd();

	// Middle Finger
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(-0.325f, 0.50f);
	glVertex2f(-0.35f, 0.50f);
	glVertex2f(-0.35f, 0.44f);
	glVertex2f(-0.325f, 0.44f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.35f, 0.50f);
	glVertex2f(-0.35f, 0.44f);
	glVertex2f(-0.325f, 0.44f);
	glVertex2f(-0.325f, 0.50f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, -0.337f, 0.50f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.337f, 0.50f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, -0.337f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.337f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.337f, 0.44f, 0.0f, 180.0f);
	glEnd();

	// Ring Finger
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(-0.35f, 0.50f);
	glVertex2f(-0.375f, 0.50f);
	glVertex2f(-0.375f, 0.44f);
	glVertex2f(-0.35f, 0.44f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.375f, 0.50f);
	glVertex2f(-0.375f, 0.44f);
	glVertex2f(-0.35f, 0.44f);
	glVertex2f(-0.35f, 0.50f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, -0.3625f, 0.50f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.3625f, 0.50f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, -0.3625f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.3625f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.3625f, 0.44f, 0.0f, 180.0f);
	glEnd();

	// Little Finger
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(-0.375f, 0.48f);
	glVertex2f(-0.4f, 0.48f);
	glVertex2f(-0.4f, 0.44f);
	glVertex2f(-0.375f, 0.44f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4f, 0.48f);
	glVertex2f(-0.4f, 0.44f);
	glVertex2f(-0.375f, 0.44f);
	glVertex2f(-0.375f, 0.48f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, -0.387f, 0.48f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.387f, 0.48f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, -0.387f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.387f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, -0.387f, 0.44f, 0.0f, 180.0f);
	glEnd();

	// Hand kada
	glBegin(GL_QUADS);
	glColor3fv(fGoldenColor);
	glVertex2f(-0.3f, 0.35f);
	glVertex2f(-0.38f, 0.35f);
	glVertex2f(-0.39f, 0.34f);
	glVertex2f(-0.29f, 0.34f);

	glVertex2f(-0.29f, 0.34f);
	glVertex2f(-0.39f, 0.34f);
	glVertex2f(-0.38f, 0.33f);
	glVertex2f(-0.3f, 0.33f);

	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.3f, 0.35f);
	glVertex2f(-0.38f, 0.35f);
	glVertex2f(-0.39f, 0.34f);
	glVertex2f(-0.29f, 0.34f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.29f, 0.34f);
	glVertex2f(-0.39f, 0.34f);
	glVertex2f(-0.38f, 0.33f);
	glVertex2f(-0.3f, 0.33f);
	glEnd();

	// Right Hands
	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(fSkinColor);
	for (int i = 0; i < 100; i++)
	{
		glVertex2f(0.20f + 0.18f * cos(3.0f * M_PI / 2.0f + (GLfloat)i / 100.0f * (M_PI / 2.0f)), 0.35f + 0.2f * sin(3.0f * M_PI / 2.0f + (GLfloat)i / 100.0f * M_PI / 2.0f));
		glVertex2f(0.20f + 0.1f * cos(3.0f * M_PI / 2.0f + (GLfloat)i / 100.0f * (M_PI / 2.0f)), 0.35f + 0.1f * sin(3.0f * M_PI / 2.0f + (GLfloat)i / 100.0f * M_PI / 2.0f));
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.18f, 0.2f, 0.20f, 0.35f, 270.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.1f, 0.1f, 0.20f, 0.35f, 270.0f, 360.0f);
	glEnd();

	// Right Hand kada
	glBegin(GL_QUADS);
	glColor3fv(fGoldenColor);
	glVertex2f(0.3f, 0.35f);
	glVertex2f(0.38f, 0.35f);
	glVertex2f(0.39f, 0.34f);
	glVertex2f(0.29f, 0.34f);

	glVertex2f(0.29f, 0.34f);
	glVertex2f(0.39f, 0.34f);
	glVertex2f(0.38f, 0.33f);
	glVertex2f(0.3f, 0.33f);

	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.3f, 0.35f);
	glVertex2f(0.38f, 0.35f);
	glVertex2f(0.39f, 0.34f);
	glVertex2f(0.29f, 0.34f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.29f, 0.34f);
	glVertex2f(0.39f, 0.34f);
	glVertex2f(0.38f, 0.33f);
	glVertex2f(0.3f, 0.33f);
	glEnd();

	// Palm
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(0.28f, 0.37f);
	glVertex2f(0.40f, 0.37f);
	glVertex2f(0.40f, 0.44f);
	glVertex2f(0.28f, 0.44f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.40f, 0.37f);
	glVertex2f(0.40f, 0.44f);
	glVertex2f(0.28f, 0.44f);
	glVertex2f(0.28f, 0.37f);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.06f, 0.02f, 0.34f, 0.37f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.06f, 0.02f, 0.34f, 0.37f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.08f, 0.08f, 0.30f, 0.35f, 90.0f, 0.0f);
	glEnd();

	// Thumb
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(0.28f, 0.48f);
	glVertex2f(0.30f, 0.48f);
	glVertex2f(0.30f, 0.44f);
	glVertex2f(0.28f, 0.44f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.30f, 0.48f);
	glVertex2f(0.30f, 0.44f);
	glVertex2f(0.28f, 0.44f);
	glVertex2f(0.28f, 0.48f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	glVertex2f(0.28f, 0.48f);
	circle(0.02f, 0.02f, 0.28f, 0.48f, 90.0f, 0.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.28f, 0.48f);
	circle(0.02f, 0.02f, 0.28f, 0.48f, 90.0f, 0.0f);
	glEnd();

	// Index Finger
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(0.30f, 0.48f);
	glVertex2f(0.325f, 0.48f);
	glVertex2f(0.325f, 0.44f);
	glVertex2f(0.30f, 0.44f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.325f, 0.48f);
	glVertex2f(0.325f, 0.44f);
	glVertex2f(0.30f, 0.44f);
	glVertex2f(0.30f, 0.48f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, 0.3125f, 0.48f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.3125f, 0.48f, 0.0f, 180.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, 0.3125f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.3125f, 0.44f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.3125f, 0.44f, 0.0f, 180.0f);
	glEnd();

	// Middle Finger
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(0.325f, 0.50f);
	glVertex2f(0.35f, 0.50f);
	glVertex2f(0.35f, 0.44f);
	glVertex2f(0.325f, 0.44f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.35f, 0.50f);
	glVertex2f(0.35f, 0.44f);
	glVertex2f(0.325f, 0.44f);
	glVertex2f(0.325f, 0.50f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, 0.337f, 0.50f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.337f, 0.50f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, 0.337f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.337f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.337f, 0.44f, 0.0f, 180.0f);
	glEnd();

	// Ring Finger
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(0.35f, 0.50f);
	glVertex2f(0.375f, 0.50f);
	glVertex2f(0.375f, 0.44f);
	glVertex2f(0.35f, 0.44f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.375f, 0.50f);
	glVertex2f(0.375f, 0.44f);
	glVertex2f(0.35f, 0.44f);
	glVertex2f(0.35f, 0.50f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, 0.3625f, 0.50f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.3625f, 0.50f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, 0.3625f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.3625f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.3625f, 0.44f, 0.0f, 180.0f);
	glEnd();

	// Little Finger
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(0.375f, 0.48f);
	glVertex2f(0.4f, 0.48f);
	glVertex2f(0.4f, 0.44f);
	glVertex2f(0.375f, 0.44f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.4f, 0.48f);
	glVertex2f(0.4f, 0.44f);
	glVertex2f(0.375f, 0.44f);
	glVertex2f(0.375f, 0.48f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, 0.387f, 0.48f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.387f, 0.48f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.0125f, 0.015f, 0.387f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.387f, 0.44f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.0125f, 0.015f, 0.387f, 0.44f, 0.0f, 180.0f);
	glEnd();

	// Shaul
	// Right Side
	glBegin(GL_QUADS);
	glColor3fv(fRedishPink);

	glVertex2f(0.40f, 0.25f);
	glVertex2f(0.30f, 0.15f);
	glVertex2f(0.10f, 0.05f);
	glVertex2f(0.43f, -0.1f);

	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.40f, 0.25f);
	glVertex2f(0.30f, 0.15f);
	glVertex2f(0.10f, 0.05f);
	glVertex2f(0.43f, -0.1f);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fRedishPink);
	circle(0.04f, 0.2f, 0.40f, 0.05f, 310.0f, 450.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.2f, 0.40f, 0.05f, 310.0f, 450.0f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(fGoldenColor);
	for (int i = 0; i < 100; i++)
	{
		glVertex2f(0.36f + 0.04f * cos(310.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * (140.0f * M_PI / 180.0f)), 0.05f + 0.165f * sin(310.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * (140.0f * M_PI / 180.0f)));
		glVertex2f(0.38f + 0.04f * cos(310.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * (140.0f * M_PI / 180.0f)), 0.05f + 0.18f * sin(310.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * (140.0f * M_PI / 180.0f)));
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.165f, 0.36f, 0.05f, 310.0f, 450.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	circle(0.04f, 0.18f, 0.38f, 0.05f, 310.0f, 450.0f);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3fv(fRedishPink);
	num = 20;
	for (int i = 0; i < num; i++)
	{
		glVertex2f(0.41f + 0.04 * cos(310.0f * M_PI / 180.0f + (GLfloat)i / (GLfloat)num * (140.0f * M_PI / 180.0f)), 0.05f + 0.21f * sin(310.0f * M_PI / 180.0f + (GLfloat)i / (GLfloat)num * (140.0f * M_PI / 180.0f)));
	}
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glPointSize(1.0f);

	// Left Side shaul
	glBegin(GL_QUADS);
	glColor3fv(fRedishPink);

	glVertex2f(-0.40f, 0.25f);
	glVertex2f(-0.30f, 0.15f);
	glVertex2f(-0.10f, 0.05f);
	glVertex2f(-0.43f, -0.1f);

	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.40f, 0.25f);
	glVertex2f(-0.30f, 0.15f);
	glVertex2f(-0.10f, 0.05f);
	glVertex2f(-0.43f, -0.1f);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fRedishPink);
	circle(0.04f, 0.2f, -0.40f, 0.05f, 90.0f, 230.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.2f, -0.40f, 0.05f, 90.0f, 230.0f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(fGoldenColor);
	for (int i = 0; i < 100; i++)
	{
		glVertex2f(-0.36f + 0.04f * cos(90.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * (140.0f * M_PI / 180.0f)), 0.05f + 0.165f * sin(90.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * (140.0f * M_PI / 180.0f)));
		glVertex2f(-0.38f + 0.04f * cos(90.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * (140.0f * M_PI / 180.0f)), 0.05f + 0.18f * sin(90.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * (140.0f * M_PI / 180.0f)));
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.165f, -0.36f, 0.05f, 90.0f, 230.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	circle(0.04f, 0.18f, -0.38f, 0.05f, 90.0f, 230.0f);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3fv(fRedishPink);
	num = 20;
	for (int i = 0; i < num; i++)
	{
		glVertex2f(-0.41f + 0.04 * cos(90.0f * M_PI / 180.0f + (GLfloat)i / (GLfloat)num * (140.0f * M_PI / 180.0f)), 0.05f + 0.21f * sin(90.0f * M_PI / 180.0f + (GLfloat)i / (GLfloat)num * (140.0f * M_PI / 180.0f)));
	}
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glPointSize(1.0f);

	// Main body
	// Lower Rectangle
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(0.25f, 0.25f);
	glVertex2f(-0.25f, 0.25f);
	glVertex2f(-0.25f, -0.25f);
	glVertex2f(0.25f, -0.25f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.25f, 0.25f);
	glVertex2f(-0.25f, -0.25f);
	glVertex2f(0.25f, -0.25f);
	glVertex2f(0.25f, 0.25f);

	glEnd();

	// Body ornaments
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.18f, 0.27f, 0.0f, 0.35f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.18f, 0.27f, 0.0f, 0.35f, 180.0f, 360.0f);
	glEnd();

	// White Points outside ornament
	glEnable(GL_POINT_SMOOTH);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	num = 70;
	for (int i = 0; i < num; i++)
	{
		glVertex2f(0.0f + 0.19 * cos((GLfloat)i / (GLfloat)num * 2 * M_PI), 0.35f + 0.28f * sin((GLfloat)i / (GLfloat)num * 2 * M_PI));
	}
	// circle(0.19f, 0.28f, 0.0f, 0.35f, 180.0f, 360.0f);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glPointSize(1.0f);

	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.15f, 0.23f, 0.0f, 0.35f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.23f, 0.0f, 0.35f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.07f, 0.09f, 0.0f, 0.02f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.07f, 0.09f, 0.0f, 0.02f, 0.0f, 360.0f);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	num = 25;
	for (int i = 0; i < num; i++)
	{
		glVertex2f(0.0f + 0.08 * cos((GLfloat)i / (GLfloat)num * 2 * M_PI), 0.02f + 0.1f * sin((GLfloat)i / (GLfloat)num * 2 * M_PI));
	}
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glPointSize(1.0f);

	// Upper shoulder Rounded Area
	// pink
	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(fRedishPink);
	for (int i = 0; i < 100; i++)
	{
		glVertex2f(0.0f + 0.3f * cos((GLfloat)i / 100.0f * M_PI), 0.1f + 0.3f * sin((GLfloat)i / 100.0f * M_PI));
		glVertex2f(0.0f + 0.2f * cos((GLfloat)i / 100.0f * M_PI), 0.1f + 0.3f * sin((GLfloat)i / 100.0f * M_PI));
	}

	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.3f, 0.3f, 0.0f, 0.1f, 0.0f, 180.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.2f, 0.3f, 0.0f, 0.1f, 0.0f, 180.0f);
	glEnd();

	// Ears
	// Right Ear
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.15f, 0.20f, 0.22f, 0.50f, 90.0f, 270.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.20f, 0.22f, 0.50f, 90.0f, 270.0f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(fSkinColorDark);
	for (int i = 0; i <= 100; i++)
	{
		glVertex2f(0.22f + 0.15f * cos(M_PI / 2.0f + M_PI / 2.0f * (GLfloat)i / 100.0f), 0.50f + 0.20f * sin(M_PI / 2.0f + M_PI / 2.0f * (GLfloat)i / 100.0f));
		glVertex2f(0.22f + 0.15f * cos(M_PI / 2.0f + M_PI / 2.0f * (GLfloat)i / 100.0f), 0.50f + 0.17f * sin(M_PI / 2.0f + M_PI / 2.0f * (GLfloat)i / 100.0f));
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.20f, 0.22f, 0.50f, 90.0f, 180.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.17f, 0.22f, 0.50f, 90.0f, 180.0f);
	glEnd();
	// Hands
	// Left Hand Lower

	// Golden Circle
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.07f, 0.07f, -0.255f, -0.03f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.07f, 0.07f, -0.255f, -0.03f, 0.0f, 360.0f);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	num = 25;
	for (int i = 0; i < num; i++)
	{
		glVertex2f(-0.255f + 0.077 * cos((GLfloat)i / (GLfloat)num * 2 * M_PI), -0.03f + 0.077f * sin((GLfloat)i / (GLfloat)num * 2 * M_PI));
	}
	// circle(0.19f, 0.28f, 0.0f, 0.35f, 180.0f, 360.0f);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glPointSize(1.0f);

	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(-0.20f, 0.10f);
	glVertex2f(-0.30f, 0.10f);
	glVertex2f(-0.30f, 00.00f);
	glVertex2f(-0.20f, 0.00f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.30f, 0.10f);
	glVertex2f(-0.30f, 0.00f);
	glVertex2f(-0.20f, 0.00f);
	glVertex2f(-0.20f, 0.10f);
	glEnd();

	// Upper half circle
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.05f, 0.05f, -0.25f, 0.10f, 0.0f, 180.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.05f, 0.05f, -0.25f, 0.10f, 0.0f, 180.0f);
	glEnd();

	// Lower half circle
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.06f, 0.06f, -0.24f, 0.00f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.06f, 0.06f, -0.24f, 0.00f, 180.0f, 360.0f);
	glEnd();

	// Lines For fingers
	glBegin(GL_LINES);
	glVertex2f(-0.25, 0.15);
	glVertex2f(-0.25, 0.05);

	glVertex2f(-0.28, 0.10);
	glVertex2f(-0.28, 0.05);

	glVertex2f(-0.22, 0.10);
	glVertex2f(-0.22, 0.05);

	glVertex2f(-0.20, 0.05);
	glVertex2f(-0.30, 0.05);

	glEnd();

	// thumb
	//  Lower half circle
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	glVertex2f(-0.18, 0.00f);
	circle(0.06f, 0.06f, -0.18f, 0.00f, 90.0f, 180.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.18, 0.00f);
	circle(0.06f, 0.06f, -0.18f, 0.00f, 90.0f, 180.0f);
	glEnd();

	// Left Ear
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.15f, 0.20f, -0.22f, 0.50f, 270.0f, 450.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.20f, -0.22f, 0.50f, 270.0f, 450.0f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(fSkinColorDark);
	for (int i = 0; i <= 100; i++)
	{
		glVertex2f(-0.22f + 0.15f * cos(2 * M_PI + M_PI / 2.0f * (GLfloat)i / 100.0f), 0.50f + 0.20f * sin(2 * M_PI + M_PI / 2.0f * (GLfloat)i / 100.0f));
		glVertex2f(-0.22f + 0.15f * cos(2 * M_PI + M_PI / 2.0f * (GLfloat)i / 100.0f), 0.50f + 0.17f * sin(2 * M_PI + M_PI / 2.0f * (GLfloat)i / 100.0f));
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.20f, -0.22f, 0.50f, 360.0f, 450.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.17f, -0.22f, 0.50f, 360.0f, 450.0f);
	glEnd();

	// Right Hand
	// Golden Circle
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.07f, 0.07f, 0.255f, -0.03f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.07f, 0.07f, 0.255f, -0.03f, 0.0f, 360.0f);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	num = 25;
	for (int i = 0; i < num; i++)
	{
		glVertex2f(0.255f + 0.077 * cos((GLfloat)i / (GLfloat)num * 2 * M_PI), -0.03f + 0.077f * sin((GLfloat)i / (GLfloat)num * 2 * M_PI));
	}
	// circle(0.19f, 0.28f, 0.0f, 0.35f, 180.0f, 360.0f);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glPointSize(1.0f);

	// Modak
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.06f, 0.07f, 0.25f, 0.06f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.06f, 0.07f, 0.25f, 0.06f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3fv(fGoldenColor);

	glVertex2f(0.19f, 0.08f);
	glVertex2f(0.31f, 0.08f);
	glVertex2f(0.25f, 0.17f);

	glEnd();

	// Lines on Moduk
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.19f, 0.08f);
	glVertex2f(0.25f, 0.17f);
	glVertex2f(0.31f, 0.08f);

	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0.25f, 0.17f);
	glVertex2f(0.23f, 0.08f);

	glVertex2f(0.25f, 0.17f);
	glVertex2f(0.27f, 0.08f);

	glEnd();

	// Lower half circle
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.06f, 0.06f, 0.26f, 0.00f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.06f, 0.06f, 0.26f, 0.00f, 180.0f, 360.0f);
	glEnd();

	// thumb
	//  Lower half circle
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	glVertex2f(0.32f, 0.00f);
	circle(0.05f, 0.06f, 0.32f, 0.00f, 90.0f, 180.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.32f, 0.00f);
	circle(0.05f, 0.06f, 0.32f, 0.00f, 90.0f, 180.0f);
	glEnd();

	// Fingers
	//   Lower half circle
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	glVertex2f(0.32f, 0.00f);
	circle(0.04f, 0.06f, 0.24f, 0.00f, 0.0f, 180.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	// glVertex2f(0.32f, 0.00f);
	circle(0.04f, 0.06f, 0.24f, 0.00f, 0.0f, 180.0f);
	glEnd();

	// Ear Rings
	// Right Side
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.04f, 0.04f, 0.12f, 0.33f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.04f, 0.12f, 0.33f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fRedishPink);
	circle(0.022f, 0.022f, 0.12f, 0.33f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.022f, 0.022f, 0.12f, 0.33f, 0.0f, 360.0f);
	glEnd();

	// Left Side
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.04f, 0.04f, -0.12f, 0.33f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.04f, -0.12f, 0.33f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fRedishPink);
	circle(0.022f, 0.022f, -0.12f, 0.33f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.022f, 0.022f, -0.12f, 0.33f, 0.0f, 360.0f);
	glEnd();

	// Face
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(0.12f, 0.50f);
	glVertex2f(-0.12f, 0.50f);
	glVertex2f(-0.12f, 0.40f);
	glVertex2f(0.12f, 0.40f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.12f, 0.50f);
	glVertex2f(-0.12f, 0.40f);
	glVertex2f(0.12f, 0.40f);
	glVertex2f(0.12f, 0.50f);

	glEnd();

	// Upper circle
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.12f, 0.15f, 0.0f, 0.50f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.12f, 0.15f, 0.0f, 0.50f, 0.0f, 180.0f);
	glEnd();

	// lower circle
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.12f, 0.15f, 0.0f, 0.40f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.12f, 0.15f, 0.0f, 0.40f, 180.0f, 360.0f);
	glEnd();

	// Eyes

	// EyeLines
	// Right Side
	// Eyelines
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.05f, 0.06f, 0.1f, 0.50f, 75.0f, 180.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.05f, 0.05f, 0.1f, 0.48f, 80.0f, 180.0f);
	glEnd();

	// White Part
	glPushMatrix();
	glTranslatef(0.08f, 0.48f, 0.0f);
	glRotatef(50.0f, 0.0f, 0.0, 1.0f);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	circle(0.04f, 0.025f, 0.0f, 0.00f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.025f, 0.0f, 0.00f, 0.0f, 360.0f);
	glEnd();
	glPopMatrix();

	// Black Part
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.025f, 0.025f, 0.075f, 0.49f, 180.0f, 430.0f);
	glEnd();

	// White spot Inside Black
	glEnable(GL_POINT_SMOOTH);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex2f(0.09f, 0.49f);
	glEnd();
	glPointSize(1.0f);
	glDisable(GL_POINT_SMOOTH);

	// Left Side
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.05f, 0.06f, -0.1f, 0.50f, 360.0f, 465.0f);
	glEnd();
	// Eyelines

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.05f, 0.05f, -0.1f, 0.48f, 360.0f, 460.0f);
	glEnd();

	// White Part
	glPushMatrix();
	glTranslatef(-0.08f, 0.48f, 0.0f);
	glRotatef(130.0f, 0.0f, 0.0, 1.0f);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	circle(0.04f, 0.025f, 0.0f, 0.00f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.025f, 0.0f, 0.00f, 0.0f, 360.0f);
	glEnd();
	glPopMatrix();

	// Black Part
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.025f, 0.025f, -0.075f, 0.49f, 110.0f, 360.0f);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex2f(-0.09f, 0.49f);
	glEnd();
	glPointSize(1.0f);
	glDisable(GL_POINT_SMOOTH);

	// Teeths

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.05f, 0.3f);
	glVertex2f(-0.1f, 0.26f);
	glVertex2f(-0.05f, 0.27f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.05f, 0.3f);
	glVertex2f(-0.1f, 0.26f);
	glVertex2f(-0.05f, 0.27f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.05f, 0.3f);
	glVertex2f(0.07f, 0.28f);
	glVertex2f(0.07f, 0.26f);
	glVertex2f(0.05f, 0.26f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);

	glVertex2f(0.05f, 0.3f);
	glVertex2f(0.07f, 0.28f);
	glVertex2f(0.07f, 0.26f);
	glVertex2f(0.05f, 0.26f);
	glEnd();

	// Trunk
	// Big Part
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(0.05f, 0.50f);
	glVertex2f(-0.05f, 0.50f);
	glVertex2f(-0.05f, 0.00f);
	glVertex2f(0.05f, 0.00f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.05f, 0.50f);
	glVertex2f(-0.05f, 0.00f);
	glVertex2f(0.05f, 0.00f);
	glVertex2f(0.05f, 0.50f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.05f, 0.05f, 0.0f, 0.0f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.05f, 0.05f, 0.0f, 0.0f, 180.0f, 360.0f);
	glEnd();

	glPointSize(4.0f);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 15; i++)
	{
		glVertex2f(0.0f, lerp(0.50, -0.05, (GLfloat)i / 15.0f));
	}
	glEnd();
	glPointSize(1.0f);
	glDisable(GL_POINT_SMOOTH);

	// Small Part
	glBegin(GL_QUADS);
	glColor3fv(fSkinColor);
	glVertex2f(0.15f, 0.10f);
	glVertex2f(0.05f, 0.10f);
	glVertex2f(0.05f, 0.00f);
	glVertex2f(0.15f, 0.00f);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.05f, 0.10f);
	glVertex2f(0.05f, 00.00f);
	glVertex2f(0.15f, 0.00f);
	glVertex2f(0.15f, 0.10f);

	glEnd();

	// Lower Half Circle
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.05f, 0.05f, 0.1f, 0.00f, 180.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.05f, 0.05f, 0.1f, 0.00f, 180.0f, 360.0f);
	glEnd();

	// Upper Half Circle
	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.05f, 0.05f, 0.1f, 0.10f, 0.0f, 180.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.05f, 0.05f, 0.1f, 0.10f, 0.0f, 180.0f);
	glEnd();

	glPointSize(4.0f);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 5; i++)
	{
		glVertex2f(0.1f, lerp(0.10f, -0.05f, (GLfloat)i / 5.0f));
	}
	glEnd();
	glPointSize(1.0f);
	glDisable(GL_POINT_SMOOTH);

	// Tilak
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	circle(0.05f, 0.05f, 0.0f, 0.55f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fSkinColor);
	circle(0.035f, 0.035f, 0.0f, 0.57f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fDhotiColor);
	circle(0.015f, 0.015f, 0.0f, 0.50f, 0.0f, 360.0f);
	glEnd();

	// Naval Triangle
	glBegin(GL_TRIANGLES);
	glColor3fv(fGoldenColor);
	glVertex2f(0.0f, -0.15f);
	glVertex2f(-0.01f, -0.17f);
	glVertex2f(0.01f, -0.17f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, -0.15f);
	glVertex2f(-0.01f, -0.17f);
	glVertex2f(0.01f, -0.17f);
	glEnd();

	//
	glBegin(GL_QUADS);
	glColor3fv(fGoldenColor);
	glVertex2f(0.1f, -0.18f);
	glVertex2f(-0.1f, -0.18f);
	glVertex2f(-0.1f, -0.25f);
	glVertex2f(0.1f, -0.25f);

	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.14f, -0.18f);
	glVertex2f(-0.14f, -0.18f);
	glVertex2f(-0.14f, -0.25f);
	glVertex2f(0.14f, -0.25f);
	glEnd();

	// Leg-Middle Triangles
	glBegin(GL_TRIANGLES);
	glColor3fv(fDhotiColor);
	glVertex2f(0.25f, -0.1f);
	glVertex2f(0.25f, -0.40f);
	glVertex2f(-0.28f, -0.40f);

	glVertex2f(-0.25f, -0.1f);
	glVertex2f(-0.25f, -0.40f);
	glVertex2f(0.28f, -0.40f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.25f, -0.1f);
	glVertex2f(0.25f, -0.40f);
	glVertex2f(-0.28f, -0.40f);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.25f, -0.1f);
	glVertex2f(-0.25f, -0.40f);
	glVertex2f(0.28f, -0.40f);
	glEnd();

	// Right Leg Circle
	glBegin(GL_POLYGON);
	glColor3fv(fDhotiColor);
	circle(0.15f, 0.15f, 0.25f, -0.25f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.15f, 0.25f, -0.25f, 270.0f, 510.0f);
	glEnd();

	// Left Leg Circle
	glBegin(GL_POLYGON);
	glColor3fv(fDhotiColor);
	circle(0.15f, 0.15f, -0.25f, -0.25f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.15f, -0.25f, -0.25f, 30.0f, 270.0f);
	glEnd();

	// Assan
	glBegin(GL_QUADS);
	glColor3fv(fAsanColor);
	glVertex2f(0.40f, -0.40f);
	glVertex2f(-0.40f, -0.40f);
	glVertex2f(-0.40f, -0.47f);
	glVertex2f(0.40f, -0.47f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.40f, -0.40f);
	glVertex2f(-0.40f, -0.40f);
	glVertex2f(-0.40f, -0.47f);
	glVertex2f(0.40f, -0.47f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fAsanColor);
	glVertex2f(0.40f, -0.47f);
	circle(0.07f, 0.07f, 0.40f, -0.47f, 90.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.07f, 0.07f, 0.40f, -0.47f, 90.0f, 0.0f);
	glVertex2f(0.40f, -0.47f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fAsanColor);
	glVertex2f(-0.40f, -0.47f);
	circle(0.07f, 0.07f, -0.40f, -0.47f, 90.0f, 180.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.07f, 0.07f, -0.40f, -0.47f, 90.0f, 180.0f);
	glVertex2f(-0.40f, -0.47f);
	glEnd();

	// Second Asan
	glBegin(GL_QUADS);
	glColor3fv(fAsanColor);
	glVertex2f(0.70f, -0.47f);
	glVertex2f(-0.70f, -0.47f);
	glVertex2f(-0.70f, -0.50f);
	glVertex2f(0.70f, -0.50f);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.70f, -0.47f);
	glVertex2f(-0.70f, -0.47f);
	glVertex2f(-0.70f, -0.50f);
	glVertex2f(0.70f, -0.50f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fAsanColor);
	glVertex2f(0.70f, -0.50f);
	circle(0.03f, 0.03f, 0.70f, -0.50f, 90.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.03f, 0.03f, 0.70f, -0.50f, 90.0f, 0.0f);
	glVertex2f(0.70f, -0.50f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fAsanColor);
	glVertex2f(-0.70f, -0.50f);
	circle(0.03f, 0.03f, -0.70f, -0.50f, 90.0f, 180.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.03f, 0.03f, -0.70f, -0.50f, 90.0f, 180.0f);
	glVertex2f(-0.70f, -0.50f);
	glEnd();

	// Loads
	// Left Side
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.15f, 0.15f, -0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.15f, -0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.13f, 0.13f, -0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.03f, 0.03f, -0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fRedishPink);
	circle(0.015f, 0.015f, -0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.015f, 0.015f, -0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();

	glPointSize(4.0f);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 5; i++)
		glVertex2f(-0.58f, lerp(-0.32f, -0.45f, (GLfloat)i / 5.0f));
	glEnd();
	glPointSize(1.0f);
	glDisable(GL_POINT_SMOOTH);

	// Right Side
	glBegin(GL_POLYGON);
	glColor3fv(fGoldenColor);
	circle(0.15f, 0.15f, 0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.15f, 0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.13f, 0.13f, 0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.13f, 0.13f, 0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.03f, 0.03f, 0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fRedishPink);
	circle(0.015f, 0.015f, 0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.015f, 0.015f, 0.58f, -0.32f, 0.0f, 360.0f);
	glEnd();

	// Load Right Side
	glPointSize(4.0f);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 5; i++)
		glVertex2f(0.58f, lerp(-0.32f, -0.45f, (GLfloat)i / 5.0f));
	glEnd();
	glPointSize(1.0f);
	glDisable(GL_POINT_SMOOTH);

	// Dhoti Front Side
	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(fDhotiColor);
	for (int i = 0; i < 100; i++)
	{
		glVertex2f(-0.15f + 0.10f * cos(270.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * M_PI / 2.0f), -0.18f + 0.2f * sin(270.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * M_PI / 2.0f));
		glVertex2f(0.15f + 0.10f * cos(270.0f * M_PI / 180.0f - (GLfloat)i / 100.0f * M_PI / 2.0f), -0.18f + 0.2f * sin(270.0f * M_PI / 180.0f - (GLfloat)i / 100.0f * M_PI / 2.0f));
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.10f, 0.2f, -0.15f, -0.18f, 270.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.10f, 0.2f, 0.15f, -0.18f, 270.0f, 180.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3fv(fDhotiColor);
	circle(0.15f, 0.1f, 0.0f, -0.38f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.15f, 0.1f, 0.0f, -0.38f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(fGoldenColor);
	for (int i = 0; i < 100; i++)
	{
		glVertex2f(0.0f + 0.14f * cos(180.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * M_PI), -0.38f + 0.08f * sin(180.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * M_PI));
		glVertex2f(0.0f + 0.12f * cos(180.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * M_PI), -0.37f + 0.06f * sin(180.0f * M_PI / 180.0f + (GLfloat)i / 100.0f * M_PI));
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.14f, 0.08f, 0.0f, -0.38f, 180.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.12f, 0.06f, 0.0f, -0.37f, 180.0f, 360.0f);
	glEnd();

	glEnable(GL_POINT_SMOOTH);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	num = 25;
	for (int i = 0; i < num; i++)
	{
		glVertex2f(0.0f + 0.16f * cos(M_PI + (GLfloat)i / (GLfloat)num * M_PI), -0.38f + 0.11f * sin(M_PI + (GLfloat)i / (GLfloat)num * M_PI));
	}
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glPointSize(1.0f);

	// Mouse

	// Ears
	glBegin(GL_POLYGON);
	glColor3f(0.3f, 0.3f, 0.3f);
	circle(0.01f, 0.01f, 0.19f, -0.43f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.01f, 0.01f, 0.19f, -0.43f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 0.5f);
	circle(0.01f, 0.01f, 0.20f, -0.42f, 0.0f, 360.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.01f, 0.01f, 0.20f, -0.42f, 0.0f, 360.0f);
	glEnd();

	// Body

	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(0.25f, -0.39f);
	glVertex2f(0.15f, -0.47f);
	glVertex2f(0.25f, -0.47f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.25f, -0.39f);
	glVertex2f(0.15f, -0.47f);
	glVertex2f(0.25f, -0.47f);
	glEnd();

	/// Eye
	glEnable(GL_POINT_SMOOTH);
	glPointSize(4.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.20f, -0.45f);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glPointSize(1.0f);

	// Back Part
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.5f, 0.5f);
	circle(0.04f, 0.04f, 0.25f, -0.43f, 270.0f, 450.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.04f, 0.25f, -0.43f, 270.0f, 450.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.03f, 0.03f, 0.265f, -0.47f, 90.0f, 180.0f);
	glEnd();

	// Tail
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.04f, 0.275f, -0.455f, 360.0f, 450.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.04f, 0.03f, 0.355f, -0.455f, 180.0f, 270.0f);
	glEnd();

	// Lotus
	glPushMatrix();
	glTranslatef(0.3f, 0.6f, 0.0f);
	lotus();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3f, 0.6f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	lotus();
	glPopMatrix();
}

void circle(GLfloat fxRadius, GLfloat fyRadius, GLfloat xCenter, GLfloat yCenter, GLfloat fAngleFrom, GLfloat fAngleTo)
{
	int i;
	GLfloat fAngle;
	fAngleFrom = fAngleFrom * M_PI / 180.0f;
	fAngleTo = fAngleTo * M_PI / 180.0f;

	for (i = 0; i <= 100; i++)
	{
		fAngle = lerp(fAngleFrom, fAngleTo, (GLfloat)i / 100.0f);

		glVertex2f(xCenter + fxRadius * cos(fAngle), yCenter + fyRadius * sin(fAngle));
	}
}

void petals(void)
{
	GLfloat fAngle;

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 100; i++)
	{
		fAngle = 225.0f * M_PI / 180.0f + 90.0f * M_PI / 180.0f * (GLfloat)i / 100.0f;
		glVertex2f(0.08f + 0.11f * cos(fAngle), 0.08 + 0.11f * sin(fAngle));
		fAngle = 45.0f * M_PI / 180.0f + 90.0f * M_PI / 180.0f * (GLfloat)i / 100.0f;
		glVertex2f(0.08f + 0.11f * cos(fAngle), -0.08 + 0.11f * sin(fAngle));
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.11f, 0.11f, 0.08f, 0.08f, 225.0f, 315.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	circle(0.11f, 0.11f, 0.08f, -0.08f, 45.0f, 135.0f);
	glEnd();
}

void lotus(void)
{
	glPushMatrix();
	glColor3f(255.0f / 255.0f, 61.0f / 255.0f, 99.0f / 255.0f);
	glRotatef(25.0f, 0.0f, 0.0f, 1.0f);
	petals();
	glPopMatrix();

	glPushMatrix();
	glColor3f(255.0f / 255.0f, 61.0f / 255.0f, 99.0f / 255.0f);
	glRotatef(75.0f, 0.0f, 0.0f, 1.0f);
	petals();
	glPopMatrix();

	glPushMatrix();
	glColor3f(249.0f / 255.0f, 123.0f / 255.0f, 148.0f / 255.0f);
	glRotatef(50.0f, 0.0f, 0.0f, 1.0f);
	petals();
	glPopMatrix();

	glPushMatrix();
	glColor3f(254.0f / 255.0f, 97.0f / 255.0f, 128.0f / 255.0f);
	glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
	petals();
	glPopMatrix();

	glPushMatrix();
	glColor3f(254.0f / 255.0f, 97.0f / 255.0f, 128.0f / 255.0f);
	glRotatef(100.0f, 0.0f, 0.0f, 1.0f);
	petals();
	glPopMatrix();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.001, 0.01f);
	glVertex2f(0.001, -0.15f);
	glEnd();
}


