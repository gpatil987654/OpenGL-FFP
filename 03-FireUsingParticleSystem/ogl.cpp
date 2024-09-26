#include <windows.h>
#include "ogl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#define _USE_MATH_DEFINES 23
#include <math.h>

#include "ParticleSystem.hpp"

#define WND_WIDTH 800
#define WND_HEIGHT 600

#pragma comment(lib, "OpengL32.lib")
#pragma comment(lib, "glu32.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// FullScreen
HWND ghwnd = NULL;
BOOL gbFullScreen = FALSE;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};

// OpneGL Inteoperability
BOOL gbActive = FALSE;
HDC ghdc = NULL;
PIXELFORMATDESCRIPTOR pfd;
int indexPfd = 0;
HGLRC ghrc = NULL;

typedef struct particle_t particle;

float lerp(float start, float end, float t)
{
    return (start + (end - start) * t);
}

PVector emission_location(0, -1, 0);
ParticleSystem ps(emission_location);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // function declaration
    int initialise(void);
    void update(void);
    void display(void);
    void uninitialise(void);

    WNDCLASSEX wndclass;
    TCHAR szAppName[] = TEXT("MyWindow");
    HWND hwnd;
    MSG msg;

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon));

    RegisterClassEx(&wndclass);

    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szAppName,
        TEXT("Pratice"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        GetSystemMetrics(SM_CXSCREEN) / 2 - WND_WIDTH / 2,
        GetSystemMetrics(SM_CYSCREEN) / 2 - WND_HEIGHT / 2,
        WND_WIDTH, WND_HEIGHT,
        NULL, NULL, hInstance, NULL);
    ghwnd = hwnd;

    if (initialise() != 0)
    {
        uninitialise();
        DestroyWindow(hwnd);
        exit(EXIT_FAILURE);
    }

    ShowWindow(hwnd, iCmdShow);
    SetFocus(hwnd);
    SetForegroundWindow(hwnd);

    // Game Loop
    BOOL bDone = FALSE;

    while (bDone == FALSE)
    {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bDone = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if (gbActive)
            {
                display();

                update();
            }
        }
    }

    /*
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
*/
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    void ToggleFullScreen(void);
    void resize(int width, int height);
    static int width, height;

    switch (iMsg)
    {
    case WM_SIZE:
        resize(LOWORD(lParam), HIWORD(lParam));
        width = LOWORD(lParam);
        height = HIWORD(lParam);

        break;

    case WM_SETFOCUS:
        gbActive = TRUE;
        break;

    case WM_KILLFOCUS:
        gbActive = FALSE;
        break;

    case WM_LBUTTONDOWN:

        break;

    case WM_CHAR:
        switch (wParam)
        {
        case 'f':
        case 'F':
            ToggleFullScreen();
            break;
        }
        break;

    case WM_KEYDOWN:
        switch (LOWORD(wParam))
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
        break;
    case WM_DESTROY:

        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void ToggleFullScreen(void)
{
    MONITORINFO mi = {sizeof(MONITORINFO)};

    if (gbFullScreen == FALSE)
    {
        dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

        if (dwStyle & WS_OVERLAPPEDWINDOW)
        {
            if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
            {
                SetWindowLong(ghwnd, GWL_STYLE, dwStyle & (~WS_OVERLAPPEDWINDOW));
                SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
                ShowCursor(FALSE);
                gbFullScreen = TRUE;
            }
        }
    }
    else
    {
        SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPlacement(ghwnd, &wpPrev);
        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOOWNERZORDER);
        ShowCursor(TRUE);
        gbFullScreen = FALSE;
    }
}

int initialise(void)
{
    // Variables

    void resize(int width, int height);

    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cDepthBits = 32;

    ghdc = GetDC(ghwnd);

    if (ghdc == NULL)
        return -1;

    indexPfd = ChoosePixelFormat(ghdc, &pfd);

    if (indexPfd == 0)
        return -2;

    if (SetPixelFormat(ghdc, indexPfd, &pfd) == FALSE)
        return -3;

    ghrc = wglCreateContext(ghdc);

    if (ghrc == NULL)
        return -4;

    if (wglMakeCurrent(ghdc, ghrc) == FALSE)
        return -5;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    resize(WND_WIDTH, WND_HEIGHT);
    return 0;
}

void resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 100.0f);
    // gluOrtho2D(0.0f, 100.0f, 0.0f, 100.0f);
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -3.0f);

    ps.addParticel();
    ps.run();
    if (ps.isEmpty())
        exit(1);

    SwapBuffers(ghdc);
}

void update(void)
{
}

void uninitialise(void)
{

    if (wglGetCurrentContext() == ghrc)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(ghrc);
        ghrc = NULL;
    }

    if (ghdc)
    {
        ReleaseDC(ghwnd, ghdc);
        ghdc = NULL;
    }

    if (ghwnd)
    {
        DestroyWindow(ghwnd);
        ghwnd = NULL;
    }
}
