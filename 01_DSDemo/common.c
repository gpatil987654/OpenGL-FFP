#include "common.h"

float lerp(float start, float end, float t)
{
    return (start + (end - start) * t);
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
    if (channel == 1)
    {
        format = GL_RED;
    }
    else if (channel == 3)
    {
        format = GL_RGB;
    }
    else if (channel == 4)
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

    // glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    //  if (texture == treeTexture1 || texture == treeTexture2 || texture == treeTexture3)

    GLfloat value = 0;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &value);

    //  value = (value > 8.0f) ? 8.0f : value;

    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, value);

    gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return texture;
}

GLuint createTexture2DTree(const char *filepath)
{
    stbi_set_flip_vertically_on_load(1);
    int width, height, channel;

    unsigned char *data = stbi_load(filepath, &width, &height, &channel, 0);
    if (data == NULL)
    {
        return -1;
    }

    GLenum format = GL_RGBA;
    if (channel == 1)
    {
        format = GL_RED;
    }
    else if (channel == 3)
    {
        format = GL_RGB;
    }
    else if (channel == 4)
    {
        format = GL_RGBA;
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    // if (texture == treeTexture1 || texture == treeTexture2 || texture == treeTexture3)

    GLfloat value = 0;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &value);

    value = (value > 8.0f) ? 8.0f : value;

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, value);

    gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return texture;
}

extern HDC ghdc;

GLYPHMETRICSFLOAT gmf[256];

GLuint BuildFont(char *fontName, int fontSize, float depth)
{
    HFONT font;
    GLuint base = glGenLists(256);
    font = CreateFont(fontSize,
                      0,
                      0,
                      0,
                      FW_BOLD,
                      FALSE,
                      FALSE,
                      FALSE,
                      ANSI_CHARSET,
                      OUT_TT_PRECIS,
                      CLIP_DEFAULT_PRECIS,
                      ANTIALIASED_QUALITY,
                      FF_DONTCARE | DEFAULT_PITCH,
                      fontName);

    if (!font)
        return 0;

    SelectObject(ghdc, font);
    wglUseFontOutlines(ghdc, 0, 256, base, 0.0, depth, WGL_FONT_POLYGONS, gmf);

    return base;
}

GLvoid glPrint(GLuint base, const char *str, ...)
{
    float lenght = 0;
    char text[256];
    va_list ap;

    if (str == NULL)
        return;

    va_start(ap, str);
    vsprintf(text, str, ap);
    va_end(ap);

    for (GLuint i = 0; i < strlen((text)); i++)
    {
        lenght += gmf[text[i]].gmfCellIncX;
    }

    glTranslatef(-lenght / 2, 0.0f, 0.0f);
    glPushAttrib(GL_LIST_BIT); // GL_LIST_BASE
    glListBase(base);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}

GLuint BuildFontBitmap(char *name, int fontSize, int bold)
{
    HFONT font;
    HFONT oldFont;
    GLuint base = glGenLists(128);
    GLuint cWeight;

    if (bold == 1)
        cWeight = FW_BOLD;
    else
        cWeight = FW_NORMAL;

    font = CreateFont(fontSize,
                      0,
                      0,
                      0,
                      cWeight,
                      FALSE,
                      FALSE,
                      FALSE,
                      ANSI_CHARSET,
                      OUT_TT_PRECIS,
                      CLIP_DEFAULT_PRECIS,
                      ANTIALIASED_QUALITY,
                      FF_DONTCARE | DEFAULT_PITCH,
                      (TCHAR *)name);

    oldFont = (HFONT)SelectObject(ghdc, font);

    wglUseFontBitmaps(ghdc, 32, 128, base);

    SelectObject(ghdc, oldFont);

    DeleteObject(font);
    return base;
}

void glPrintBitmap(GLuint base, const char *str, ...)
{
    char text[256];
    va_list ap;

    if (str == NULL)
        return;

    va_start(ap, str);
    vsprintf(text, str, ap);
    va_end(ap);

    glPushAttrib(GL_LIST_BIT);
    glListBase(base - 32);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}

void cube(void)
{
    glBegin(GL_QUADS);

    // Front Face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Right Face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Back Face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Top Face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Bottom Face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    glEnd();
}

void shadowMatrix(float ground[], float light[])
{
    float shadowMat[4][4] = {0};
    float dot;

    dot = ground[0] * light[0] +
          ground[1] * light[1] +
          ground[2] * light[2] +
          ground[3] * light[3];

    shadowMat[0][0] = dot - light[0] * ground[0];
    shadowMat[1][0] = 0.0 - light[0] * ground[1];
    shadowMat[2][0] = 0.0 - light[0] * ground[2];
    shadowMat[3][0] = 0.0 - light[0] * ground[3];

    shadowMat[0][1] = 0.0 - light[1] * ground[0];
    shadowMat[1][1] = dot - light[1] * ground[1];
    shadowMat[2][1] = 0.0 - light[1] * ground[2];
    shadowMat[3][1] = 0.0 - light[1] * ground[3];

    shadowMat[0][2] = 0.0 - light[2] * ground[0];
    shadowMat[1][2] = 0.0 - light[2] * ground[1];
    shadowMat[2][2] = dot - light[2] * ground[2];
    shadowMat[3][2] = 0.0 - light[2] * ground[3];

    shadowMat[0][3] = 0.0 - light[3] * ground[0];
    shadowMat[1][3] = 0.0 - light[3] * ground[1];
    shadowMat[2][3] = 0.0 - light[3] * ground[2];
    shadowMat[3][3] = dot - light[3] * ground[3];

    glMultMatrixf((const GLfloat *)shadowMat);
}

void calculateNormal(GLfloat x1, GLfloat y1, GLfloat z1,
                     GLfloat x2, GLfloat y2, GLfloat z2,
                     GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat r1, r3;
    x1 = x1 - x2;
    y1 = y1 - y2;
    z1 = z1 - z2;

    x3 -= x2;
    y3 -= y2;
    z3 -= z2;

    r1 = sqrtf(x1 * x1 + y1 * y1 + z1 * z1);
    r3 = sqrtf(x3 * x3 + y3 * y3 + z3 * z3);

    x1 /= r1;
    y1 /= r1;
    z1 /= r1;

    x3 /= r3;
    y3 /= r3;
    z3 /= r3;

    GLfloat nx, ny, nz;

    nx = y1 * z3 - z1 * y3;
    ny = z1 * x3 - x1 * z3;
    nz = x1 * y3 - y1 * x3;

    glNormal3f(nx, ny, nz);
}

// Torus Geometry
GLfloat N = 100.0f;

GLfloat torus[101][101][3];
GLfloat torusNormal[101][101][3];
GLuint torusDisplayList;

void normal(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{
    GLfloat x = x1 * (y1 * z2 - y2 * z1);
    GLfloat y = y1 * (x2 * z1 - x1 * z2);
    GLfloat z = z1 * (x1 * y2 - x2 * y1);

    GLfloat r = sqrt(x * x + y * y + z * z);
    x = x / r;
    y = y / r;
    z = z / r;

    glNormal3f(x, y, z);
}

void initTorus(void)
{

    GLfloat fAngle1, fAngle2, innerRadius, outerRadius;

    innerRadius = 2.0f;
    outerRadius = 5.0f;
    GLfloat centerX, centerZ;
    GLfloat centerXnext, centerZnext;

    for (int j = 0; j <= N; j++)
    {
        fAngle1 = 2 * M_PI * (float)j / N;

        for (int i = 0; i <= N; i++)
        {
            fAngle2 = 2 * M_PI * (float)i / N;
            //	glVertex3f(centerX + innerRadius * cos(fAngle2), innerRadius * sin(fAngle2), centerZ);
            torus[j][i][0] = (outerRadius + innerRadius * cos(fAngle2)) * cos(fAngle1); // centerX + innerRadius * cos(fAngle2) * cos(fAngle1);
            torus[j][i][1] = (outerRadius + innerRadius * cos(fAngle2)) * sin(fAngle1); // innerRadius * sin(fAngle2);
            torus[j][i][2] = innerRadius * sin(fAngle2);                                // centerZ + innerRadius * cos(fAngle2);

            torusNormal[j][i][0] = (outerRadius + (innerRadius + 1) * cos(fAngle2)) * cos(fAngle1) - torus[j][i][0];
            torusNormal[j][i][1] = (outerRadius + (innerRadius + 1) * cos(fAngle2)) * sin(fAngle1) - torus[j][i][1];
            torusNormal[j][i][2] = ((innerRadius + 1) * sin(fAngle2)) - torus[j][i][2];

            GLfloat r = sqrt(torusNormal[j][i][0] * torusNormal[j][i][0] + torusNormal[j][i][1] * torusNormal[j][i][1] + torusNormal[j][i][2] * torusNormal[j][i][2]);
            torusNormal[j][i][0] /= r;
            torusNormal[j][i][1] /= r;
            torusNormal[j][i][2] /= r;
        }
    }

    torusDisplayList = glGenLists(1);
    glNewList(torusDisplayList, GL_COMPILE);
    drawTorus();
    glEndList();
}

void drawTorus(void)
{

    // glBindTexture(GL_TEXTURE_2D, donutTexture);
    glBegin(GL_QUADS);
    GLfloat inc = 1.0f / (GLfloat)N;

    GLfloat xInc = 1.0f / 5.0f;

    GLfloat half = 0.5f;

    for (int j = 0; j < N; j++)
    {

        for (int i = 0; i < N; i++)
        {

            glNormal3f(torusNormal[j + 1][i][0], torusNormal[j + 1][i][1], torusNormal[j + 1][i][2]);
            glTexCoord2f(xInc * (j - 1), inc * i + half);
            glVertex3f(torus[j + 1][i][0], torus[j + 1][i][1], torus[j + 1][i][2]);

            glNormal3f(torusNormal[j + 1][i + 1][0], torusNormal[j + 1][i + 1][1], torusNormal[j + 1][i + 1][2]);
            glTexCoord2f(xInc * (j - 1), inc * (i - 1) + half);
            glVertex3f(torus[j + 1][i + 1][0], torus[j + 1][i + 1][1], torus[j + 1][i + 1][2]);

            glNormal3f(torusNormal[j][i + 1][0], torusNormal[j][i + 1][1], torusNormal[j][i + 1][2]);
            glTexCoord2f(xInc * j, inc * (i - 1) + half);
            glVertex3f(torus[j][i + 1][0], torus[j][i + 1][1], torus[j][i + 1][2]);

            glNormal3f(torusNormal[j][i][0], torusNormal[j][i][1], torusNormal[j][i][2]);
            glTexCoord2f(xInc * j, inc * i + half);
            glVertex3f(torus[j][i][0], torus[j][i][1], torus[j][i][2]);
        }
    }

    glEnd();

    // glBindTexture(GL_TEXTURE_2D, 0);
}
