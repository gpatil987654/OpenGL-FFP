// Standard Headers
#include <windows.h> //Win 32 API
#include <stdio.h>	 //FileIO
#include <stdlib.h>	 //exit()
#include "ogl.h"	 //For Icon resource

// OpenGL Header Files
#include <gl/GL.h>
#include <gl/glu.h> //OpenGL Utility Functions

// For Image Loading(Texturing)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "common.h"

#include "terrain.h"
#include "house.h"
#include "crops.h"
#include "environmentMap.h"
#include "trees.h"
#include "path.h"
#include "butterfly.h"
#include "pond.h"

#include "intro.h"
#include "credits.h"

// Extra
#include "house2.h"
#include "flowerPlants.h"
#include "camera.h"
#include "wall.h"
#include "fractalMangoTree.h"
#include "well.h"

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// Link with OpenGl Library
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib") // For Perspective Projection

// Global Function Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

// Camera
GLfloat eyeX = -1.25f, eyeY = -1.25f, eyeZ = 10.0f, centerX, centerY, centerZ = -1000.0f;
GLfloat fAngleX = 0.0f, fAngleY = 0.0f, fAngleZ = 0.0f;

// Quadric
GLUquadric *quadric = NULL;

// Lights
GLfloat lightAmbient[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
//
GLfloat lightPosition[] = {100.0f, 100.0f, 0.0f, 1.0f};
GLfloat lightPosition2[] = {100.0f, 500.0f, 100.0f, 1.0f};
BOOL bStartAnimation = GL_FALSE;

// Update variables
int open_door = 0;
int close_door = 1;
int jhopala_move = 0;
int mirror_show = 0;
int start_mirror = 0;
int coconut_tree_order = 0;
GLfloat Alpha = 0.0f;

int showButterfly = 1;
GLfloat fogDensity = 0.01f;

vec3_cam_t b;

GLfloat butX, butY, butZ;

vec3_cam_t butterfly1[] =
	{
		{-200.0f, -20.0f, 450.0f},
		{-200.0f, -20.0f, 400.0f},
		{-100.0f, 0.0f, 300.0f},
		{-50.0f, 20.0f, 250.0f},
		{0.0f, 70.0f, 200.0f},
		{0.0f, 100.0f, 150.0f}};

vec3_cam_t butterfly2[] =
	{
		{-50.0f, 20.0f, 250.0f},
		{0.0f, 70.0f, 200.0f},
		{0.0f, 100.0f, 150.0f},
		{0.0f, 50.0f, 140.0f},
		{-22.0f, -31.0f, 100.0f},
		{-40.0f, 0.0f, 80.0f}};

vec3_cam_t butterfly3[] =
	{
		{0.0f, 50.0f, 140.0f},
		{-22.0f, -31.0f, 100.0f},
		{-40.0f, 0.0f, 80.0f},
		{-70.0f, 10.0f, 50.0f},
		{-70.0f, 30.0f, 0.0f},
		{-70.0f, 50.0f, -50.0f},
		{-100.0f, 70.0f, -100.0f},
		{-150.0f, 100.0f, -150.0f}};

vec3_cam_t cameraPosition1[] = {
	{-540.0f, 100.0f, 1650.0f},
	{-550.0f, 100.0f, 1550.0f},
	{-580.0f, 100.0f, 850.0f},
	{-580.0f, 100.0f, 470.0f},
	{-360.0f, 100.0f, 390.0f},
	{-100.0f, 100.0f, 390.0f},
	{0.0f, 100.0f, 390.0f},
	{240.0f, 100.0f, 340.0f}};

vec3_cam_t cameraPosition2[] = {
	{-100.0f, 100.0f, 390.0f},
	{0.0f, 100.0f, 390.0f},
	{240.0f, 100.0f, 340.0f},
	{350.0f, 100.0f, 190.0f},
	{390.0f, 100.0f, -20.0f},
	{280.0f, 100.0f, -300.0f},
	{0.0f, 100.0f, -390.0f},
	{-280.0f, 100.0f, -300.0f},
	{-390.0f, 100.0f, -20.0f},
	{-300.0f, 100.0f, 200.0f},
	{-100.0f, 100.0f, 300.0f},
	{0.0f, 100.0f, 320.0f},
	{150.0f, 100.0f, 340.0f}};

vec3_cam_t cameraPosition3[] = {
	{-100.0f, 100.0f, 300.0f},
	{0.0f, 100.0f, 320.0f},
	{150.0f, 100.0f, 340.0f},
	{220.0f, 80.0f, 420.0f},
	{210.0f, 60.0f, 580.0f},
	{80.0f, 40.0f, 650.0f},
	{-50.0f, 20.0f, 610.0f},
	{-100.0f, -10.0f, 520.0f},
	{-110.0f, -30.0f, 410.0f},

	{-100.0f, -25.0f, 210.0f},
	{-30.0f, -25.0f, 150.0f},
	{0.0f, -25.0f, 140.0f}};

vec3_cam_t cameraPosition4[] = {
	{-100.0f, -25.0f, 210.0f},
	{-30.0f, -25.0f, 150.0f},
	{0.0f, -25.0f, 140.0f},

	{100.0f, -20.0f, 140.0f},
	{150.0f, -10.0f, 130.0f},
	{200.0f, 0.0f, 90.0f},
	//{150.0f, 0.0f, 20.0f},
	{150.0f, 0.0f, 40.0f},
	{85.0f, -20.0f, 80.0f},
	{0.0f, -35.0f, 90.0f},
	{-70.0f, -30.0f, 85.0f},

	{-30.0f, -30.0f, 70.0f},
	{0.0f, -30.0f, 70.0f},
	{40.0f, -30.0f, 90.0f},
	{0.0f, -35.0f, 90.0f},
	{-70.0f, -20.0f, 85.0f},

	{-150.0f, -10.0f, 20.0f},
	{-180.0f, 0.0f, -30.0f},
	{-180.f, 0.0f, -90.0f}};

vec3_cam_t cameraPosition5[] =
	{
		//{-20.0f, -30.0f, 95.0f},
		//	{-90.0f, -20.0f, 95.0f},
		//	{-170.0f, 0.0f, 40.0f},
		{-150.0f, -10.0f, 20.0f},
		{-180.0f, 0.0f, -30.0f},
		{-180.f, 0.0f, -90.0f},

		//	{-190.0f, 0.0f, -10.0f},
		//	{-180.0f, 0.0f, -100.0f},
		{-120.0f, 0.0f, -160.0f},
		{-40.0f, 15.0f, -140.0f},
		{-25.0f, 15.0f, -80.0f},
		{-25.0f, 15.0f, 10.0f},
		{-25.0f, 15.0f, 120.0f},
		{-10.0f, 20.0f, 200.0f},
		{110.0f, 40.0f, 360.0f},
		{310.0f, 50.0f, 490.0f},
		{400.0f, 50.0f, 620.0f},
		{280.0f, 50.0f, 730.0f},
		{0.0f, 50.0f, 800.0f},
		{-100.0f, 50.0f, 670.0f},

		{-50.0f, -5.0f, 400.0f},
		{-5.0f, -15.0f, 80.0f},
		{-5.0f, -20.0f, 0.0f}
		//{0.0f, -20.0f, -10.0f}

};

/*
vec3_cam_t cameraPosition6[] = {

	//	{-10.0f, -15.0f, 100.0f},
	//	{-10.0f, -15.0f, 80.0f},
	//	{0.0f, -20.0f, 40.0f},
	//{0.0f, -20.0f, 30.0f},

	//{0.0f, -20.0f, 20.0f},

	{0.0f, -15.0f, 80.0f},
	{0.0f, -20.0f, 0.0f},
	{0.0f, -20.0f, -10.0f},

	{0.0f, -20.0f, 10.0f},
	{0.0f, -20.0f, -15.0f},
	{50.0f, -20.0f, 15.0f},
	{0.0f, -20.0f, 40.0f},

	{-50.0f, -20.0f, 15.0f},

	{40.0f, -20.0f, -10.0f},
	{0.0f, -20.0f, -10.0f},
	{40.0f, -20.0f, -10.0f},
	{40.0f, -20.0f, 15.0f},
	{60.0f, -20.0f, 20.0f},
	{100.0f, -10.0f, 80.0f}


};
*/

vec3_cam_t cameraPosition6[] = {

	{-50.0f, -5.0f, 400.0f},
	{-5.0f, -15.0f, 80.0f},
	{-5.0f, -20.0f, 0.0f},

	{-20.0f, -20.0f, -10.0f},
	{-40.0f, -20.0f, 20.0f},
	{-20.0f, -20.0f, 40.0f},

	{0.0f, -20.0f, 10.0f},
	//{40.0f, -20.0f, 0.0f},
	{40.0f, -20.0f, -10.0f},
	{0.0f, -20.0f, -10.0f},

	//{40.0f, -20.0f, 15.0f},
	{60.0f, -20.0f, 20.0f},
	{100.0f, -10.0f, 80.0f}};

/*
vec3_cam_t cameraPosition7[] =
	{
		{40.0f, -20.0f, 15.0f},
		{60.0f, -20.0f, 20.0f},
		{100.0f, -10.0f, 80.0f},
		{200.0f, 0.0f, 100.0f},
		{0.0f, 10.0f, 300.0f},

		{-300.0f, 50.0f, 250.0f}, //

		{-400.0f, 100.0f, 0.0f},

		{-300.0f, 120.0f, -300.0f}, //

		{0.0f, 150.0f, -400.0f},

		{400.0f, 170.0f, -300.0f}, //

		{500.0f, 200.0f, 0.0f},

		{400.0f, 230.0f, 300.0f}, //

		{0.0f, 250.0f, 500.0f},

		{-450.0f, 270.0f, 400.0f}, //

		{-550.0f, 300.0f, 0.0f},

		{-400.0f, 330.0f, -400.0f}, //

		{0.0f, 350.0f, -550.0f},

		{500.0f, 370.0f, -400.0f}, //

		{600.0f, 400.0f, 0.0f},
		{0.0f, 400.0f, 700.0f}

};
*/
vec3_cam_t cameraPosition7[] = {
	//	{40.0f, -20.0f, 15.0f},
	{0.0f, -20.0f, -10.0f},
	{60.0f, -20.0f, 20.0f},
	{100.0f, -10.0f, 80.0f},

	{200.0f, 0.0f, 110.0f},
	{200.0f, 0.0f, 200.0f},
	{-50.0f, 0.0f, 400.0f},

	//{-100.0f, 0.0f, 500.0f},
	//{-150.0f, 0.0f, 600.0f},
	//{-200.0f, 0.0f, 700.0f},
	//{-250.0f, 0.0f, 900.0f},
	{-300.0f, 0.0f, 1000.0f},
	{-300.0f, 0.0f, 1200.0f}
	/*
	{300.0f, 0.0f, 600.0f},
	{-300.0f, 0.0f, 800.0f},
	{0.0f, 0.0f, 900.0f},
	{300.0f, 0.0f, 1000.0f},
	{-100.0, 0.0f, 1100.0f},
	{-300.0f, 0.0f, 1100.0f}
	*/
};

// LookAt Cantrol Points
vec3_cam_t cameraLookAt1[] = {{-700.0f, 100.0f, 0.0f}, {-600.0f, 100.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {10.0f, 0.0f, 0.0f}

};

vec3_cam_t cameraLookAt2[] = {
	{-15.0f, 0.0f, 0.0f},
	{-10.0f, 0.0f, 0.0f},
	{10.0f, 0.0f, 0.0f},
	{15.0f, 0.0f, 0.0f}};

vec3_cam_t cameraLookAt3[] = {
	{-10.0f, 0.0f, 0.0f},
	{10.0f, 0.0f, 0.0f},
	{15.0f, 0.0f, 0.0f},
	{0.0f, -25.0f, 100.0f},
	{0.0f, -25.0f, 90.0f}};

vec3_cam_t cameraLookAt4[] = {
	{15.0f, 0.0f, 0.0f},
	{0.0f, -25.0f, 100.0f},
	{0.0f, -30.0f, 100.0f},
	//{0.0f, -35.0f, 90.0f},
	{0.0f, -35.0f, 110.0f},

	{-50.0f, -35.0f, 90.0f},
	{-130.0f, 0.0f, 0.0f},
	//{-110.0f, 0.0f, -50.0f},
	{-90.0f, 0.0f, -90.0f} // new
};

vec3_cam_t cameraLookAt5[] = {
	//	{200.0f, 0.0f, 50.0f},
	//	{-50.0f, -30.0f, 90.0f},
	//	{-150.0f, 0.0f, 0.0f},

	{-50.0f, -35.0f, 90.0f},
	{-130.0f, 0.0f, 0.0f},
	//{-110.0f, 0.0f, -50.0f},
	{-90.0f, 0.0f, -90.0f}, // new

	//{-120.0f, 0.0f, -160.0f},
	{-40.0f, 15.0f, -140.0f},
	{-25.0f, 15.0f, -80.0f},
	{-25.0f, 15.0f, 10.0f},
	{-25.0f, 15.0f, 120.0f},
	{-10.0f, 20.0f, 200.0f},
	{110.0f, 40.0f, 360.0f},
	{310.0f, 50.0f, 490.0f},
	{400.0f, 50.0f, 620.0f},
	{280.0f, 50.0f, 730.0f},
	{0.0f, 50.0f, 800.0f},
	{-100.0f, 50.0f, 670.0f},
	/*
		{-350.0f, 50.0f, 520.0f},
		{-370.0, 50.0f, 240.0f},
		{-330.0f, 20.0f, 130.0f},
		{-200.0f, 10.0f, 130.0f},
		{-80.0f, 0.0f, 130.0f},
		*/
	//{-10.0f, -15.0f, 100.0f},
	{-50.0f, -5.0f, 400.0f},
	{-5.0f, -15.0f, 79.0f},
	{-5.0f, -20.0f, 0.0f}};
/*
vec3_cam_t cameraLookAt6[] = {

	//	{-10.0f, -15.0f, 100.0f},
	//{-10.0f, -15.0f, 80.0f},
	//{0.0f, -20.0f, 40.0f},
	//{0.0f, -20.0f, 10.0f},

	{0.0f, -15.0f, 80.0f},
	{0.0f, -20.0f, 0.0f},
	{0.0f, -20.0f, -10.0f},

	{0.0f, -25.0f, 10.0f},
	{5.0f, -25.0f, 10.0f},
	{0.0f, -25.0f, 10.0f},
	{50.0f, -25.0f, -10.0f},
	{60.0f, -25.0f, 15.0f},
	{80.0f, -20.0f, 30.0f},
	{100.0f, -10.0f, 60.0f}

};
*/

vec3_cam_t cameraLookAt6[] = {

	{-50.0f, -5.0f, 400.0f},
	{-5.0f, -15.0f, 79.0f},
	{-5.0f, -20.0f, 0.0f},

	{-20.0f, -22.0f, -10.0f},

	{-20.0f, -22.0f, 20.0f},
	{0.0f, -20.0f, 20.0f},
	{0.0f, -20.0f, 20.0f},

	{40.0f, -20.0f, 0.0f},
	{40.0f, -20.0f, 0.0f},
	{40.0f, -20.0f, 0.0f},

	{60.0f, -25.0f, 15.0f},
	{80.0f, -20.0f, 30.0f},
	{100.0f, -10.0f, 60.0f}

};

vec3_cam_t cameraLookAt7[] = {
	{60.0f, -25.0f, 15.0f},
	{80.0f, -20.0f, 30.0f},
	{100.0f, -10.0f, 60.0f},
	{50.0f, 0.0f, 100.0f},
	{0.0f, 0.0f, 50.0f},
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, -20.0f},
	//	{1.0f, 0.0f, -20.0f}
	//{0.0f, 0.0f, -20.0f}
};
/*
{0.0f, 0.0f, 0.0f},
{1.0f, 0.0f, 0.0f},
{0.0f, 0.0f, 0.0f},
{1.0f, 0.0f, 0.0f},
{0.0f, 0.0f, 0.0f},
{1.0f, 0.0f, 0.0f},
{0.0f, 0.0f, 0.0f}};
*/
// Entry Point Function
int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
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
		TEXT("Ganesh Patil : DS_DEMO(Khedyamdhle Ghar Kaularu)"),
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

			// if (gbActive == TRUE)
			{
				end_time = clock();
				delta_time = end_time - start_time;
				d_time = (float)delta_time / (float)CLOCKS_PER_SEC;
				total_time += d_time;
				// Render
				display();
				// Update
				update();
				start_time = end_time;
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
			if (bStartAnimation == GL_FALSE)
			{
				total_time = 0;
				bStartAnimation = GL_TRUE;
				PlaySound("Audio/sound8.wav", NULL, SND_ASYNC | SND_FILENAME);
			}

			break;
		}

		break;

	case WM_CHAR:
		float n = 10.0f;
		switch (LOWORD(wParam))
		{
		case 'f':
		case 'F':

			ToggleFullScreen();
			break;

		case 'a':
			eyeX -= n;
			break;

		case 'd':
			eyeX += n;
			break;

		case 'w':
			eyeZ -= n;
			break;

		case 's':
			eyeZ += n;
			break;

		case 'r':
			eyeY += n;
			break;

		case 't':
			eyeY -= n;
			break;

		case 'x':
			fAngleX++;
			break;

		case 'y':
			fAngleY++;
			break;

		case 'z':
			fAngleZ++;
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

GLuint sphereTexture;

int initialise(void)
{
	// Function Declarations

	GLuint createTexture2D(const char *filepath);
	void resize(int width, int height);

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
	pfd.cDepthBits = 32;
	pfd.cStencilBits = 32;

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

	// Enabling Depth
	glShadeModel(GL_SMOOTH);						   // Beautification Line (optional)
	glClearDepth(1.0f);								   // Compulsory
	glEnable(GL_DEPTH_TEST);						   // Compulsory
	glDepthFunc(GL_LEQUAL);							   // Compulsory
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Beuatification (optional)

	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Enable Texture
	glEnable(GL_TEXTURE_2D);

	// Enable Lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	glEnable(GL_NORMALIZE);

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Alapha Test
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL, 0.1f);

	// Stencil clear Buffer
	glClearStencil(0x0);

	// initTorus();

	initTerrain();		// No Light
	initHouse();		// No Light
	initCrops();		// No Light
	initEnvMap();		// No Light
	initTrees();		// No Light
	initPath();			// No Light
	initButterfly();	// No Light
	initPond();			// No Light
	initFlowerPlants(); // No Light
	initIntro();

	initFractalMangoTree();
	initWell();

	initHouse2();  // No Light
	initCredits(); // No Light

	initWall();

	// fog
	GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1.0f};

	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, fogDensity);
	glHint(GL_FOG_HINT, GL_DONT_CARE);

	start_time = clock();
	resize(WIN_WIDTH, WIN_HEIGHT);

	return 0;
}

void resize(int width, int height)
{
	// code
	if (height <= 0)
		height = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 8000.0f);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void drawCoordinates()
{
	// For x
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0f, 0.0f);

	glPointSize(6);
	glBegin(GL_POINTS);
	for (int x = -2000; x < 2000; x += 100)
	{
		glVertex3f(x, 100.0f, 0.0f);
	}
	//	glColor3f(0.0f, 1.0f, 0.0f);
	for (int z = -2000; z < 2000; z += 100)
	{
		glVertex3f(0.0f, 100.0f, z);
	}

	glEnd();
	glEnable(GL_LIGHTING);
}

int iCredits = 0;

void display(void)
{

	void drawScene(void);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);

	glRotatef(fAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef(fAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef(fAngleZ, 0.0f, 0.0f, 1.0f);

	gluQuadricTexture(quadric, GL_TRUE);

	void drawFractalMangoTree(void);

	// drawScene();
	//   drawCredits();

	if (bStartAnimation)
	{

		if (total_time < 14.0f)
		{
			drawIntro();
		}
		else if (total_time <= 155.0f)
		{
			glEnable(GL_FOG);
			glFogf(GL_FOG_DENSITY, fogDensity);
			drawScene();
		}
		else if (total_time <= 230.0f)
		{

			glDisable(GL_FOG);

			// glMatrixMode(GL_PROJECTION);
			// glLoadIdentity();

			// glMatrixMode(GL_MODELVIEW);
			// glLoadIdentity();

			// drawCredits();
			eyeX = 0.0f;
			eyeY = 0.0f;
			eyeZ = 20.0f;

			centerX = 0.0f;
			centerY = 0.0f;
			centerZ = 0.0f;

			lightPosition[0] = 200.0f;
			lightPosition[1] = 0.0f;
			lightPosition[2] = 100.0f;

			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
			glLoadIdentity();
			gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);

			drawCredits();
		}
	}
	/*

	eyeX = 0.0f;
	eyeY = 0.0f;
	eyeZ = 20.0f;

	centerX = 0.0f;
	centerY = 0.0f;
	centerZ = 0.0f;

	lightPosition[0] = 200.0f;
	lightPosition[1] = 0.0f;
	lightPosition[2] = 100.0f;

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);

	drawCredits();
*/
	SwapBuffers(ghdc);
}

void drawBazier(vec3_cam_t *cantrolPoints, int n, int flag)
{
	int numCantrolPoints = n;

	// CantrolPoints
	glDisable(GL_LIGHTING);

	if (flag == 0)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 1.0f);

	glPointSize(10.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < numCantrolPoints; i++)
	{
		glVertex3f(cantrolPoints[i].x, cantrolPoints[i].y, cantrolPoints[i].z);
	}
	glEnd();

	//  Cantrol Lines
	glColor3f(1.0f, 1.0f, 0.0f);
	glLineWidth(5.0f);

	if (flag == 0)
		glColor3f(0.0f, 1.0f, 0.0f);
	else
		glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_LINE_STRIP);

	for (int j = 0; j <= 100.0f; j++)
	{
		// b = b_spline(cantrolPoints, sizeof(cantrolPoints) / sizeof(cantrolPoints[0]), j / 100.0f);
		b = catMull(cantrolPoints, n, j / 100.0f);

		glVertex3f(b.x, b.y, b.z);
	}

	glEnd();

	glEnable(GL_LIGHTING);
}

void update(void)
{

	static GLfloat t = 0.0f;
	GLfloat fAngle = 0.0f, fAngle2;

	vec3_cam_t b;

	static int i = 0;
	static float t_lerp = 0.0f;
	static int flag = -1;

	static double t_vel = 0.05f;

	if (t > 1.0f)
	{
		if (flag == 6)
		{
			// Credits Init
			// iCredits = 1;
			eyeX = 0.0f;
			eyeY = 0.0f;
			eyeZ = 20.0f;

			centerX = 0.0f;
			centerY = 0.0f;
			centerZ = 0.0f;

			lightPosition[0] = 200.0f;
			lightPosition[1] = 0.0f;
			lightPosition[2] = 100.0f;

			glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		}

		flag++;
		t = 0.0f;
	}

	if (bStartAnimation)
	{
		if (total_time >= 13.0f && flag == -1)
		{
			flag = 0;
			//	PlaySound("Audio/sound3.wav", NULL, SND_ASYNC | SND_FILENAME);
		}

		if (flag == 0)
		{
			t += 0.06f * d_time;

			if (t <= 0.3f)
			{
				fogDensity = lerp(0.002f, 0.00f, t * 3.333f);
			}

			b = catMull(cameraPosition1, sizeof(cameraPosition1) / sizeof(cameraPosition1[0]), t);
			eyeX = b.x;
			eyeY = b.y;
			eyeZ = b.z;

			b = catMull(cameraLookAt1, sizeof(cameraLookAt1) / sizeof(cameraLookAt1[0]), t);
			centerX = b.x;
			centerY = b.y;
			centerZ = b.z;

			b = catMull(butterfly1, sizeof(butterfly1) / sizeof(butterfly1[0]), t);
			butX = b.x;
			butY = b.y;
			butZ = b.z;
		}

		else if (flag == 1)
		{

			t += 0.06f * d_time;
			b = catMull(cameraPosition2, sizeof(cameraPosition2) / sizeof(cameraPosition2[0]), t);
			eyeX = b.x;
			eyeY = b.y;
			eyeZ = b.z;

			b = catMull(cameraLookAt2, sizeof(cameraLookAt2) / sizeof(cameraLookAt2[0]), t);
			centerX = b.x;
			centerY = b.y;
			centerZ = b.z;

			b = catMull(butterfly2, sizeof(butterfly2) / sizeof(butterfly2[0]), t);
			butX = b.x;
			butY = b.y;
			butZ = b.z;
		}
		else if (flag == 2)
		{

			t += 0.06f * d_time;
			b = catMull(cameraPosition3, sizeof(cameraPosition3) / sizeof(cameraPosition3[0]), t);
			eyeX = b.x;
			eyeY = b.y;
			eyeZ = b.z;

			b = catMull(cameraLookAt3, sizeof(cameraLookAt3) / sizeof(cameraLookAt3[0]), t);
			centerX = b.x;
			centerY = b.y;
			centerZ = b.z;
		}
		else if (flag == 3)
		{

			t += 0.04f * d_time;
			b = catMull(cameraPosition4, sizeof(cameraPosition4) / sizeof(cameraPosition4[0]), t);
			eyeX = b.x;
			eyeY = b.y;
			eyeZ = b.z;

			b = catMull(cameraLookAt4, sizeof(cameraLookAt4) / sizeof(cameraLookAt4[0]), t);
			centerX = b.x;
			centerY = b.y;
			centerZ = b.z;

			if (t >= 0.5f)
			{
				b = catMull(butterfly3, sizeof(butterfly3) / sizeof(butterfly3[0]), t - 0.5f);
				butX = b.x;
				butY = b.y;
				butZ = b.z;
			}
		}
		else if (flag == 4)
		{
			if (t < 0.6f)
				coconut_tree_order = 1;
			else
				coconut_tree_order = 0;

			if (t >= 0.85)
			{
				showButterfly = 0;
				open_door = 1;
				jhopala_move = 1;
				close_door = 0;

				t_vel = lerp(0.05f, 0.002f, (t - 0.85f) * 6.666f);
				t += t_vel * d_time;
				//	if (t_vel >= 0.002f)
				//		t_vel -= 0.00001f;
			}
			else
				t += 0.05f * d_time;

			b = catMull(cameraPosition5, sizeof(cameraPosition5) / sizeof(cameraPosition5[0]), t);
			eyeX = b.x;
			eyeY = b.y;
			eyeZ = b.z;

			// if (t > 0.1f && t < 1.0f)
			//	b = catMull(cameraLookAt5, sizeof(cameraLookAt5) / sizeof(cameraLookAt5[0]), t + 0.00001f);
			// else
			b = catMull(cameraLookAt5, sizeof(cameraLookAt5) / sizeof(cameraLookAt5[0]), t);

			centerX = b.x;
			centerY = b.y;
			centerZ = b.z;

			if (t <= 0.5f)
			{
				b = catMull(butterfly3, sizeof(butterfly3) / sizeof(butterfly3[0]), t + 0.5f);
				butX = b.x;
				butY = b.y;
				butZ = b.z;
			}
		}
		else if (flag == 5)
		{
			coconut_tree_order = 0;

			if (t > 0.1f && t < 0.5f)
			{
				close_door = 1;
				mirror_show = 1;
			}
			else
				mirror_show = 0;

			if (t <= 0.1f)
				t_vel = lerp(0.002f, 0.05f, t * 10.0f);

			t += t_vel * d_time;

			if (t >= 0.2f)
				start_mirror = 1;

			b = catMull(cameraPosition6, sizeof(cameraPosition6) / sizeof(cameraPosition6[0]), t);
			eyeX = b.x;
			eyeY = b.y;
			eyeZ = b.z;

			b = catMull(cameraLookAt6, sizeof(cameraLookAt6) / sizeof(cameraLookAt6[0]), t);
			centerX = b.x;
			centerY = b.y;
			centerZ = b.z;
		}
		else if (flag == 6)
		{
			mirror_show = 0;
			close_door = 0;

			// t += 0.042f * d_time;
			t_vel = lerp(0.06f, 0.07f, t);
			//	t += 0.06 * d_time;
			t += t_vel * d_time;

			if (t >= 0.7f)
			{
				fogDensity = lerp(0.00f, 0.002f, (t - 0.7f) * 3.333f);
			}

			b = catMull(cameraPosition7, sizeof(cameraPosition7) / sizeof(cameraPosition7[0]), t);
			eyeX = b.x;
			eyeY = b.y;
			eyeZ = b.z;

			b = catMull(cameraLookAt7, sizeof(cameraLookAt7) / sizeof(cameraLookAt7[0]), t);
			centerX = b.x;
			centerY = b.y;
			centerZ = b.z;
		}
		else if (flag == 7)
		{
			// credits init
		}
	}
}

void uninitialise(void)
{
	// Function Declaration
	void ToggleFullScreen(void);

	// code
	uninitTerrain();
	uninitHouse();
	uninitCrops();
	uninitEnvMap();
	uninitTrees();
	uninitPath();
	uninitButterfly();
	uninitPond();
	uninitFlowerPlants();
	uninitIntro();
	uninitCredits();

	uninitHouse2();
	uninitFractalMangoTree();

	// If Application is Exiting in fullScreen
	if (gbFullScreen == TRUE)
		ToggleFullScreen();

	if (quadric)
	{
		gluDeleteQuadric(quadric);
		quadric = NULL;
	}

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

void drawScene(void)
{
	void drawBazier(vec3_cam_t * cantrolPoints, int n, int flag);

	// drawCoordinates();

	// drawBazier(cameraPosition1, sizeof(cameraPosition1) / sizeof(cameraPosition1[0]), 0);
	// drawBazier(cameraPosition2, sizeof(cameraPosition2) / sizeof(cameraPosition2[0]), 0);
	/// drawBazier(cameraPosition3, sizeof(cameraPosition3) / sizeof(cameraPosition3[0]), 0);
	// drawBazier(cameraPosition4, sizeof(cameraPosition4) / sizeof(cameraPosition4[0]), 0);
	//  drawBazier(cameraPosition5, sizeof(cameraPosition5) / sizeof(cameraPosition5[0]), 0);
	//   drawBazier(cameraPosition6, sizeof(cameraPosition6) / sizeof(cameraPosition6[0]), 0);
	// drawBazier(cameraPosition7, sizeof(cameraPosition7) / sizeof(cameraPosition7[0]), 0);

	// ButterFly
	//	drawBazier(butterfly1, sizeof(butterfly1) / sizeof(butterfly1[0]), 0);
	//	drawBazier(butterfly2, sizeof(butterfly2) / sizeof(butterfly2[0]), 0);
	//	drawBazier(butterfly3, sizeof(butterfly3) / sizeof(butterfly3[0]), 0);

	//	drawBazier(cameraLookAt1, sizeof(cameraLookAt1) / sizeof(cameraLookAt1[0]), 1);
	//	drawBazier(cameraLookAt2, sizeof(cameraLookAt2) / sizeof(cameraLookAt2[0]), 1);
	//	drawBazier(cameraLookAt3, sizeof(cameraLookAt3) / sizeof(cameraLookAt3[0]), 1);
	// drawBazier(cameraLookAt4, sizeof(cameraLookAt4) / sizeof(cameraLookAt4[0]), 1);
	//	drawBazier(cameraLookAt5, sizeof(cameraLookAt5) / sizeof(cameraLookAt5[0]), 1);
	//	drawBazier(cameraLookAt6, sizeof(cameraLookAt6) / sizeof(cameraLookAt6[0]), 1);
	// drawBazier(cameraLookAt7, sizeof(cameraLookAt7) / sizeof(cameraLookAt7[0]), 1);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition2);

	drawTerrain();

	glPushMatrix();
	drawCrops();
	glPopMatrix();

	// glDisable(GL_FOG);
	drawEnvMap();
	// glEnable(GL_FOG);

	drawHouse();

	glPushMatrix();
	glTranslatef(0.0f, 30.0f, -35.0f);
	glScalef(10.0f, 10.0f, 15.0f);
	drawHouse2();
	glPopMatrix();

	if (showButterfly == 1)
	{
		glPushMatrix();
		glTranslatef(butX, butY, butZ);
		drawButterfLy();
		glPopMatrix();
	}
	drawPath();

	drawFractalMangoTree();

	drawWell();

	drawTrees();

	drawPond();

	drawFlowerPlants();
}
