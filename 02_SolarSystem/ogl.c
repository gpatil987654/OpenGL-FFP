#include <windows.h>
#include "ogl.h"
#define CRT_RAND_S
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gl/GL.h>
#include <gl/GLU.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#define WND_WIDTH 800
#define WND_HEIGHT 600

BOOL bActive = FALSE;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

FILE *gpFile = NULL;

// FullScreen
HWND ghwnd = NULL;
BOOL gbFullScreen = FALSE;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};

// OpenGL
PIXELFORMATDESCRIPTOR pfd;
int iPixelFormat = 0;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

GLUquadric *quadric = NULL;
//
GLfloat starField[3000];
GLfloat starFieldUpdate[3000];

// Textures
GLuint textureSun, textureMercury, textureVenus,
    textureEarth, textureMars, textureJupiter,
    textureSaturn, textureUranus, textureNeptune, textureSaturnRing;

// Solar System Parameters
const GLfloat distFact = 0.5f;

// Camera Variables
GLfloat eyeX, eyeY, eyeZ = 100.0f;
GLfloat centerX, centerY, centerZ;
GLfloat fRad = 100.0f;
GLfloat fAngle = 0.0f;
GLfloat fAngleInc = 0.001f;

#define SATURN_DEBRI_COUNT 500
GLfloat debriRadius[SATURN_DEBRI_COUNT],
    debriDistFromSat[SATURN_DEBRI_COUNT];

GLfloat fRevolutionAngle = 0.0f;
GLfloat fRotationAngle = 0.0f;
GLfloat fEarthRadius = 1.0f;

int iCameraFlag = 0;
GLfloat t = 0.0f;
GLfloat rad = 1000.0f;

clock_t start_time, end_time, delta_time;
GLfloat delta;

float lerp(float start, float end, float t)
{
    return start + (end - start) * t;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // Function Declaration OpenGL
    int initialise(void);
    void update(void);
    void display(void);
    void uninitialise(void);

    HWND hwnd;
    MSG msg;
    WNDCLASSEX wndclass;
    TCHAR szAppName[] = TEXT("MyWinodw");

    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MyIcon));

    gpFile = fopen("log.txt", "w");

    if (gpFile == NULL)
    {
        MessageBox(NULL, TEXT("asdasd"), TEXT("asdas"), MB_OK);
        exit(EXIT_FAILURE);
    }

    fprintf(gpFile, "Programme Started Successfully\n");

    RegisterClassEx(&wndclass);

    hwnd = CreateWindowEx(
        WS_EX_APPWINDOW,
        szAppName,
        TEXT("GRP"),
        WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE,
        GetSystemMetrics(SM_CXSCREEN) / 2 - WND_WIDTH / 2,
        GetSystemMetrics(SM_CYSCREEN) / 2 - WND_HEIGHT / 2,
        WND_WIDTH,
        WND_HEIGHT,
        NULL,
        NULL, hInstance, NULL);
    ghwnd = hwnd;

    if (initialise() != 0)
    {
        DestroyWindow(hwnd);
        exit(EXIT_FAILURE);
    }

    ShowWindow(hwnd, iCmdShow);
    SetFocus(hwnd);
    SetForegroundWindow(hwnd);

    // GameLoop
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
            // REndering
            if (bActive == TRUE)
            {
                end_time = clock();
                delta_time = end_time - start_time;
                delta = (float)delta_time / (float)CLOCKS_PER_SEC;
                display();
                update();
                start_time = end_time;
            }
        }
    }

    uninitialise();

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    void ToggleFullScreen(void);
    void resize(int width, int height);
    static float xCameraAngle = 0.0f, yCameraAngle = 0.0f;

    static int xMousePrev = 0, yMousePrev = 0;

    switch (iMsg)
    {
    case WM_SIZE:
        resize(LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_SETFOCUS:
        bActive = TRUE;
        break;

    case WM_KILLFOCUS:
        bActive = FALSE;
        break;

    case WM_KEYDOWN:

        break;
        /*
            case WM_MOUSEMOVE:
                GLfloat x, y;
                x = LOWORD(lParam);
                y = HIWORD(lParam);
                RECT rc;
                GetWindowRect(hwnd, &rc);

                if (eyeZ > 0)
                {
                    centerX += (x - xMousePrev) / 10.0f;
                    if (x == xMousePrev)
                    {
                        if (x == 0)
                            centerX -= 1.1f;
                        else
                            centerX += 1.1f;
                    }
                }
                else
                {
                    centerX -= (x - xMousePrev) / 10.0f;
                    if (x == xMousePrev)
                    {
                        if (x == 0)
                            centerX += 1.1f;
                        else
                            centerX -= 1.1f;
                    }
                }

                centerY -= (y - yMousePrev) / 10.0f;
                if (y == yMousePrev)
                {
                    if (y == 0)
                        centerY += 1.1f;
                    else
                        centerY -= 1.1f;
                }

                xMousePrev = x;
                yMousePrev = y;

                break;
        */
    case WM_CHAR:
        switch (LOWORD(wParam))
        {
        case 'f':
        case 'F':
            ToggleFullScreen();

            break;

        case 'w':
            yCameraAngle += 0.01f;
            eyeY = 100 * sin(yCameraAngle);
            eyeZ = 100 * cos(yCameraAngle);

            break;

        case 's':
            yCameraAngle -= 0.01f;
            eyeY = 100 * sin(yCameraAngle);
            eyeZ = 100 * cos(yCameraAngle);
            break;

        case 'a':
            xCameraAngle -= 0.01f;
            eyeX = 150 * sin(xCameraAngle);
            eyeZ = 150 * cos(xCameraAngle);

            break;

        case 'd':
            xCameraAngle += 0.01f;
            eyeX = 150 * sin(xCameraAngle);
            eyeZ = 150 * cos(xCameraAngle);

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
                SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);

                SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }
        ShowCursor(FALSE);
        gbFullScreen = TRUE;
    }
    else
    {

        SetWindowPlacement(ghwnd, &wpPrev);

        SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);

        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_NOOWNERZORDER);
        ShowCursor(TRUE);
        gbFullScreen = FALSE;
    }
}

int initialise(void)
{
    void resize(int width, int height);
    BOOL loadGLTexture(GLuint * texture, TCHAR imageResourceID[]);
    GLuint createTexture2D(const char *filepath);

    void InitTerrain();

    ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 32;

    ghdc = GetDC(ghwnd);
    if (ghdc == NULL)
    {
        fprintf(gpFile, "GetDC() Failed\n");

        return -1;
    }

    iPixelFormat = ChoosePixelFormat(ghdc, &pfd);
    if (iPixelFormat == 0)
    {
        fprintf(gpFile, "ChoosePixelFormat() Failed\n");

        return -2;
    }

    if (SetPixelFormat(ghdc, iPixelFormat, &pfd) == FALSE)
    {
        fprintf(gpFile, "SetPixelFormat() Failed\n");
        return -3;
    }

    ghrc = wglCreateContext(ghdc);
    if (ghrc == NULL)
    {
        fprintf(gpFile, "wglCreateContext() Failed\n");
        return -4;
    }

    if (wglMakeCurrent(ghdc, ghrc) == FALSE)
    {
        fprintf(gpFile, "wglMakeCurrent() Failed\n");
        return -5;
    }

    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    quadric = gluNewQuadric();

    // Texture Loading
    textureSun = createTexture2D("sun.jpg");
    textureMercury = createTexture2D("mercury.jpg");
    textureVenus = createTexture2D("venus.jpg");
    textureEarth = createTexture2D("earth.jpg");
    textureMars = createTexture2D("mars.jpg");
    textureJupiter = createTexture2D("jupiter.jpg");
    textureSaturn = createTexture2D("saturn.jpg");
    textureUranus = createTexture2D("uranus.jpg");
    textureNeptune = createTexture2D("neptune.jpg");
    textureSaturnRing = createTexture2D("saturn_ring.png");

    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(quadric, GL_TRUE);

    unsigned int n;
    // Initialise start field vertices
    for (int i = 0; i < 3000; i += 3)
    {
        rand_s(&n);
        starField[i] = (float)(n % 600) - 300.0f;
        rand_s(&n);
        starField[i + 1] = (float)(n % 400) - 200.0f;
        rand_s(&n);
        starField[i + 2] = (float)(n % 1000) - 500.0f;

        int j = (i % 2 == 0) ? -1 : 1;
        int k = (i % 3 == 0) ? -1 : 1;
        int l = (i % 4 == 0) ? -1 : 1;

        starFieldUpdate[i] = j * (rand() % 10) / 10000.0f;
        starFieldUpdate[i + 1] = k * (rand() % 10) / 10000.0f;
        starFieldUpdate[i + 2] = l * (rand() % 10) / 10000.0f;
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, starField);

    // saturn debris initialisation
    for (int i = 0; i < SATURN_DEBRI_COUNT; i++)
    {
        // fAngle = 2 * M_PI * (float)i / 200.0f;
        rand_s(&n);
        debriRadius[i] = (float)(n % 20) / 200.0f;
        rand_s(&n);
        debriDistFromSat[i] = (float)(n % 200) / 100.0f + 5.0f;
    }
    //  Light Initialisation
    GLfloat light0_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light0_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light0_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightModelAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    //  glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light0_ambient);
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT)

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    // Material Properties
    GLfloat mat_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_specualr[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat mat_ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat mat_shininess[] = {10.0f};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specualr);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    start_time = clock();

    resize(WND_WIDTH, WND_HEIGHT);
    return 0;
}

BOOL loadGLTexture(GLuint *texture, TCHAR imageResourceID[])
{
    // Local Variable Declarations
    HBITMAP hBitmap;
    BITMAP bmp;

    hBitmap = LoadImage(GetModuleHandle(NULL), imageResourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBitmap == NULL)
    {
        fprintf(gpFile, "LoadImage Failed\n");
        return FALSE;
    }

    if (GetObject(hBitmap, sizeof(BITMAP), &bmp) == 0)
    {
        fprintf(gpFile, "GetObject Failed\n");
        return FALSE;
    }

    glGenTextures(1, texture);

    glBindTexture(GL_TEXTURE_2D, *texture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, (void *)bmp.bmBits);

    glBindTexture(GL_TEXTURE_2D, 0);

    DeleteObject(hBitmap);

    return TRUE;
}

GLuint createTexture2D(const char *filepath)
{
    stbi_set_flip_vertically_on_load(1);
    int width, height, channel;

    unsigned char *data = stbi_load(filepath, &width, &height, &channel, 0);
    if (data == NULL)
    {
        return -1;
    }

    GLenum format = GL_RGBA;
    if (channel == STBI_grey)
    {
        format = GL_RED;
    }
    else if (channel == STBI_rgb)
    {
        format = GL_RGB;
    }
    else if (channel == STBI_rgb_alpha)
    {
        format = GL_RGBA;
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void resize(int width, int height)
{

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 10000.0f);
}

int fShowOneByOne = 0;
void display(void)
{
    void star_field(void);
    void sun(void);
    void mercury(void);
    void earth(void);
    void venus(void);
    void mars(void);
    void jupiter(void);
    void saturn(void);
    void uranus(void);
    void neptune(void);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, 0.0f, 0.0f, 1.0f, 0.0f);

    if (iCameraFlag < 6)
    {

        star_field();

        sun();
        earth();
        mercury();
        venus();
        mars();
        jupiter();
        saturn();
        uranus();
        neptune();
    }

    if (fShowOneByOne == 1)
    {
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 1.0f);
        GLfloat globalAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
        iCameraFlag = 6;
        glScalef(20.0f, 20.0f, 20.0f);
        glRotatef(fRotationAngle / 58.0f, 0.0f, 1.0f, 0.0f);
        mercury();
    }
    else if (fShowOneByOne == 2)
    {
        glScalef(20.0f, 20.0f, 20.0f);
        glRotatef(fRotationAngle / 58.0f, 0.0f, 1.0f, 0.0f);
        venus();
    }
    else if (fShowOneByOne == 3)
    {
        glScalef(20.0f, 20.0f, 20.0f);
        glRotatef(fRotationAngle / 58.0f, 0.0f, 1.0f, 0.0f);
        earth();
    }
    else if (fShowOneByOne == 4)
    {
        glScalef(20.0f, 20.0f, 20.0f);
        glRotatef(fRotationAngle / 58.0f, 0.0f, 1.0f, 0.0f);
        mars();
    }
    else if (fShowOneByOne == 5)
    {
        glScalef(5.0f, 5.0f, 5.0f);
        glRotatef(fRotationAngle / 58.0f, 0.0f, 1.0f, 0.0f);
        jupiter();
    }
    else if (fShowOneByOne == 6)
    {
        glScalef(5.0f, 5.0f, 5.0f);
        glRotatef(fRotationAngle / 58.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        saturn();
    }
    else if (fShowOneByOne == 7)
    {
        glScalef(5.0f, 5.0f, 5.0f);
        glRotatef(fRotationAngle / 58.0f, 0.0f, 1.0f, 0.0f);
        uranus();
    }
    else if (fShowOneByOne == 8)
    {
        glScalef(5.0f, 5.0f, 5.0f);
        glRotatef(fRotationAngle / 58.0f, 0.0f, 1.0f, 0.0f);
        neptune();
    }

    SwapBuffers(ghdc);
}

BOOL fRevolution = GL_TRUE;

void update(void)
{
    for (int i = 0; i < 3000; i += 3)
    {
        starField[i] += starFieldUpdate[i];
        starField[i + 1] += starFieldUpdate[i + 1];
        starField[i + 2] += starFieldUpdate[i + 2];
    }

    if (iCameraFlag == 0)
    {
        rad = lerp(500.0f, 200.0f, t);
        eyeX = rad * cos(fAngle);
        eyeZ = rad * sin(fAngle);
        fAngle = lerp(0.0f, 4 * M_PI, t);
        t += 0.1f * delta;
    }
    else if (iCameraFlag == 1)
    {
        eyeX = rad * cos(fAngle);
        eyeZ = rad * sin(fAngle);
        fAngle = lerp(0.0f, 2 * M_PI + M_PI / 4.0f, t);
        t += 0.1f * delta;
    }
    else if (iCameraFlag == 2)
    {
        rad = 200 * (1 / sqrt(2));
        eyeY = rad * sin(fAngle);
        eyeX = rad * cos(fAngle);
        fAngle = lerp(0.0f, 2 * M_PI + M_PI / 2.0f, t);
        t += 0.1f * delta;
    }
    else if (iCameraFlag == 3)
    {
        // eyeX = lerp(200 * (1 / sqrt(2)), 0.0f, t);
        eyeY = lerp(200 * (1 / sqrt(2)), 0.0f, t);
        eyeZ = lerp(200 * (1 / sqrt(2)), 50.0f, t);
        t += 0.1f * delta;
    }
    else if (iCameraFlag == 4)
    {
        rad = 50.0f;

        fAngle = lerp(0.0f, 2 * M_PI, t);
        eyeX = rad * sin(fAngle);
        eyeZ = rad * cos(fAngle);
        t += 0.1f * delta;
    }
    else if (iCameraFlag == 5)
    {
        fAngle = lerp(0.0f, 5 * M_PI, t);
        rad = lerp(50.0f, 200.0f, t);
        eyeX = rad * cos(fAngle);
        eyeZ = rad * sin(fAngle);

        t += 0.1f * delta;
    }
    else if (iCameraFlag >= 6)
    {
        t += 0.25f * delta;
    }

    if (t >= 1.0f)
    {
        t = 0.0f;
        iCameraFlag++;

        if (iCameraFlag >= 6)
            fShowOneByOne++;
    }

    fRevolutionAngle += 0.002f;

    fRotationAngle += 0.002 * 365.0f;
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
    if (gpFile)
    {
        fprintf(gpFile, "Programme Ended Successfully\n");
        fclose(gpFile);
        gpFile = NULL;
    }

    if (textureSun)
    {
        glDeleteTextures(1, &textureSun);
        textureSun = 0;
    }

    if (textureMercury)
    {
        glDeleteTextures(1, &textureMercury);
        textureMercury = 0;
    }

    if (textureVenus)
    {
        glDeleteTextures(1, &textureVenus);
        textureVenus = 0;
    }

    if (textureEarth)
    {
        glDeleteTextures(1, &textureEarth);
        textureEarth = 0;
    }

    if (textureMars)
    {
        glDeleteTextures(1, &textureMars);
        textureMars = 0;
    }

    if (textureJupiter)
    {
        glDeleteTextures(1, &textureJupiter);
        textureJupiter = 0;
    }

    if (textureSaturn)
    {
        glDeleteTextures(1, &textureSaturn);
        textureSaturn = 0;
    }

    if (textureUranus)
    {
        glDeleteTextures(1, &textureUranus);
        textureUranus = 0;
    }

    if (textureNeptune)
    {
        glDeleteTextures(1, &textureNeptune);
        textureNeptune = 0;
    }
}

void star_field(void)
{
    glDisable(GL_LIGHTING);
    int number_of_stars = 1000;

    glEnable(GL_POINT_SMOOTH);
    glPointSize(1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawArrays(GL_POINTS, 0, 1000);

    glDisable(GL_POINT_SMOOTH);
    glEnable(GL_LIGHTING);
}

void sun(void)
{
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, textureSun);
    glPushMatrix();
    //  glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(quadric, 11.0f, 50, 50);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_LIGHTING);
    GLfloat light0_pos[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Positional light source
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
}

void earth(void)
{

    glBindTexture(GL_TEXTURE_2D, textureEarth);

    glPushMatrix();
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle, 0.0f, 1.0f, 0.0f);
        glTranslatef(80.0f * distFact, 0.0f, 0.0f);
        glRotatef(fRotationAngle, 0.0f, 1.0f, 0.0f);
    }
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(quadric, fEarthRadius, 50, 50);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void mercury(void)
{

    glBindTexture(GL_TEXTURE_2D, textureMercury);

    glPushMatrix();
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle * 4.0f - 90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(40.0f * distFact, 0.0f, 0.0f);
        glRotatef(fRotationAngle / 58.0f, 0.0f, 1.0f, 0.0f);
    }
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(quadric, fEarthRadius * 0.5f, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void venus(void)
{

    glBindTexture(GL_TEXTURE_2D, textureVenus);

    glPushMatrix();
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle * 1.5f + 90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(60.0f * distFact, 0.0f, 0.0f);
        glRotatef(fRotationAngle / 243.0f, 0.0f, 1.0f, 0.0f);
    }
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(quadric, fEarthRadius * 0.9f, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void mars(void)
{

    glBindTexture(GL_TEXTURE_2D, textureMars);

    glPushMatrix();
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle / 1.88f + 180.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(100.0f * distFact, 0.0f, 0.0f);
        glRotatef(fRotationAngle / 1.03f, 0.0f, 1.0f, 0.0f);
    }
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(quadric, fEarthRadius * 0.5f, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void jupiter(void)
{

    glBindTexture(GL_TEXTURE_2D, textureJupiter);

    glPushMatrix();
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle / 2.0f - 20.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(120.0f * distFact, 0.0f, 0.0f);
        glRotatef(fRotationAngle / 0.41f, 0.0f, 1.0f, 0.0f);
    }
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(quadric, fEarthRadius * 5.0f, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void saturn(void)
{

    glBindTexture(GL_TEXTURE_2D, textureSaturn);

    glPushMatrix();
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle / 4.0f - 90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(180.0f * distFact, 0.0f, 0.0f);
    }
    glRotatef(26.7f, 0.0, 0.0, 1.0f);
    glRotatef(fRotationAngle * 0.045f, 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(quadric, fEarthRadius * 4.0f, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    // glDisable(GL_LIGHTING);
    // Saturn Ring
    glBindTexture(GL_TEXTURE_2D, textureSaturnRing);

    glPushMatrix();
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle / 4.0f - 90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(180.0f * distFact, 0.0f, 0.0f);
    }
    glRotatef(26.7f, 0.0, 0.0, 1.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    GLfloat fAngle = 0.0f, radInn = 4.5f, radOuter = 7.0f;

    //  glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glBegin(GL_QUADS);
    for (int i = 0; i < 100; i++)
    {

        glNormal3f(-2.0f, 1.0f, -1.0f);
        fAngle = 2 * M_PI * (float)i / 100.0f;

        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(radInn * cos(fAngle), radInn * sin(fAngle));

        fAngle = 2 * M_PI * (float)(i - 1) / 100.0f;
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(radInn * cos(fAngle), radInn * sin(fAngle));

        fAngle = 2 * M_PI * (float)(i - 1) / 100.0f;
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(radOuter * cos(fAngle), radOuter * sin(fAngle));

        fAngle = 2 * M_PI * (float)i / 100.0f;
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(radOuter * cos(fAngle), radOuter * sin(fAngle));
    }
    glEnd();
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

    /*
        glCullFace(GL_FRONT);
        glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        for (int i = 0; i < 100; i++)
        {

            glNormal3f(0.0f, 1.0f, 0.0f);
            fAngle = 2 * M_PI * (float)i / 100.0f;
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(radInn * cos(fAngle), radInn * sin(fAngle));

            fAngle = 2 * M_PI * (float)(i - 1) / 100.0f;
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(radInn * cos(fAngle), radInn * sin(fAngle));

            fAngle = 2 * M_PI * (float)(i - 1) / 100.0f;
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(radOuter * cos(fAngle), radOuter * sin(fAngle));

            fAngle = 2 * M_PI * (float)i / 100.0f;
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(radOuter * cos(fAngle), radOuter * sin(fAngle));
        }
        glEnd();

        glDisable(GL_CULL_FACE);
    */

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    // Shadow On the ring of saturn
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(0.0f, 0.04f, 0.0f);
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle / 4.0f - 90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(180.0f * distFact, 0.0f, 0.0f);
    }
    glRotatef(26.7f, 0.0, 0.0, 1.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < 100; i++)
    {
        fAngle = (-45.0f + 90.0f * (float)i / 100.0f) * M_PI / 180.0f;
        glVertex2f(7.0f * cos(fAngle), 3.5f * sin(fAngle));
        glVertex2f(4.7f * cos(fAngle), 4.5f * sin(fAngle));
    }
    glEnd();
    glPopMatrix();

    // debris along the saturn
    glEnable(GL_LIGHTING);
    unsigned int n;
    GLfloat radius = 0.0f;
    GLfloat deb_rad = 0.0f;
    fAngle = 0.0f;
    glPushMatrix();
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle / 4.0f - 90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(180.0f * distFact, 0.0f, 0.0f);
    }
    for (int i = 0; i < SATURN_DEBRI_COUNT; i++)
    {
        fAngle = 2 * M_PI * (float)i / (float)SATURN_DEBRI_COUNT;
        radius = debriRadius[i];
        deb_rad = debriDistFromSat[i];

        glPushMatrix();
        glRotatef(26.7f, 0.0, 0.0, 1.0f);
        glRotatef(fRotationAngle * 0.045, 0.0f, 1.0f, 0.0f);
        glTranslatef(deb_rad * cos(fAngle), 0.0f, deb_rad * sin(fAngle));
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

        gluSphere(quadric, radius, 4, 5);
        glPopMatrix();
    }
    glPopMatrix();
}

void uranus(void)
{

    glBindTexture(GL_TEXTURE_2D, textureUranus);

    glPushMatrix();
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle / 6.0f - 20.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(220.0f * distFact, 0.0f, 0.0f);
        glRotatef(fRotationAngle / 0.72f, 0.0f, 1.0f, 0.0f);
    }
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(quadric, fEarthRadius * 3.0f, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void neptune(void)
{

    glBindTexture(GL_TEXTURE_2D, textureNeptune);

    glPushMatrix();
    if (fShowOneByOne == 0)
    {
        glRotatef(fRevolutionAngle / 8.0f - 70.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(250.0f * distFact, 0.0f, 0.0f);
        glRotatef(fRotationAngle / 0.67f, 0.0f, 1.0f, 0.0f);
    }
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(quadric, fEarthRadius * 3.0f, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}
