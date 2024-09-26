#include "common.h"
#include "intro.h"

#define SATURN_DEBRI_COUNT 5000
GLfloat debriRadius[SATURN_DEBRI_COUNT], debriDistFromSat[SATURN_DEBRI_COUNT], debriYCoord[SATURN_DEBRI_COUNT];
GLuint createTexture2DIntro(const char *filepath);

GLuint textureSaturn, textureSaturnRing, debrisTexture, fontTexture, rasterTexture;
GLuint bkgndTexture;
extern GLUquadric *quadric;
GLfloat fEarthRadius = 2.0f;
GLfloat fRotationAngle = 0.0f;
GLfloat fTiltAngle = -26.7f;
GLuint introFont, rasterFont;

extern GLfloat eyeX, eyeY, eyeZ, centerZ, centerX;

void in(void)
{
    static GLfloat t = 0.0f;
    static GLfloat alpha = 1.0f;
}

void out(void)
{
}

void saturn(GLfloat Alpha)
{

    glPushMatrix();
    glRotatef(10.0f, 1.0f, 0.0f, 0.0f);

    glColor4f(1.0f, 1.0f, 1.0f, Alpha);

    // Saturn Sphere
    glBindTexture(GL_TEXTURE_2D, textureSaturn);
    glPushMatrix();
    glRotatef(fTiltAngle, 0.0, 0.0, 1.0f);
    glRotatef(fRotationAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(quadric, fEarthRadius * 4.0f, 100, 100);
    glPopMatrix();

    // Saturn Ring
    // glDisable(GL_LIGHTING);
    // glColor3f(0.3f, 0.3f, 0.3f);
    GLfloat fAngle = 0.0f, radInn = 4.5f * fEarthRadius, radOuter = 7.0f * fEarthRadius;

    glBindTexture(GL_TEXTURE_2D, textureSaturnRing);

    glPushMatrix();
    // glScalef(17.0f, 17.0f, 17.0f);
    glRotatef(fTiltAngle, 0.0f, 0.0f, 1.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(17.0f, 17.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-17.0f, 17.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-17.0f, -17.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(17.0f, -17.0f);
    glEnd();
    glPopMatrix();

    // glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    // Shadow On the ring of saturn
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(0.0f, 0.04f, 0.0f);
    glRotatef(fTiltAngle, 0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    // glRotatef(fTiltAngle, 0.0, 0.0, 1.0f);
    //  glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    glColor4f(0.0f, 0.0f, 0.0f, Alpha - 0.5f);

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < 100; i++)
    {
        fAngle = (-45.0f + 90.0f * (float)i / 100.0f) * M_PI / 180.0f;
        glVertex2f(8.0f * cos(fAngle) * 2.0f, 4.0f * sin(fAngle) * 2.0f);
        glVertex2f(5.0f * cos(fAngle) * 2.0f, 5.5f * sin(fAngle) * 2.0f);
    }
    glEnd();
    glPopMatrix();

    // debris along the saturn
    glEnable(GL_LIGHTING);
    unsigned int n;
    GLfloat radius = 0.0f;
    GLfloat deb_rad = 0.0f;
    fAngle = 0.0f;

    glBindTexture(GL_TEXTURE_2D, debrisTexture);
    //   glColor3f(0.5f, 0.5f, 0.5f);
    for (int i = 0; i < SATURN_DEBRI_COUNT; i++)
    {
        fAngle = 2 * M_PI * (float)i / (float)SATURN_DEBRI_COUNT;
        radius = debriRadius[i];
        deb_rad = debriDistFromSat[i];

        glPushMatrix();
        glTranslatef(0.0f, debriYCoord[i], 0.0f);
        glRotatef(fTiltAngle, 0.0, 0.0, 1.0f);
        glRotatef(fRotationAngle, 0.0f, 1.0f, 0.0f);
        glTranslatef(deb_rad * cos(fAngle), 0.0f, deb_rad * sin(fAngle));
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluSphere(quadric, radius, 4, 4);
        glPopMatrix();
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    /*
        // Letters Along the Ring
        char str[] = "S\0'\0P\0M\0O\0C\0I\0D\0E\0M\0O\0R\0T\0S\0A\0";
        int lenStr = 32;
        radius = 12.0f;

        glDisable(GL_LIGHTING);
        glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
        glPushMatrix();
        glRotatef(fTiltAngle, 0.0, 0.0, 1.0f);
        // glRotatef(fRotationAngle, 0.0f, 1.0f, 0.0f);
        for (int i = 0; i < lenStr; i += 2)
        {
            fAngle = M_PI / 2.0f * (float)i / lenStr + M_PI / 3;
            glPushMatrix();
            glScalef(0.8f, 1.0f, 1.0f);
            glTranslatef(radius * cos(fAngle), 0.0f, radius * sin(fAngle));
            glRotatef(fAngle, 0.0f, 1.0, 0.0f);
            glPrint(introFont, str + i);
            glPopMatrix();
        }
        glPopMatrix();
        glEnable(GL_LIGHTING);
    */

    glPopMatrix();
}

void initIntro()
{
    unsigned int n;

    // saturn debris initialisation
    for (int i = 0; i < SATURN_DEBRI_COUNT; i++)
    {
        // fAngle = 2 * M_PI * (float)i / 200.0f;
        rand_s(&n);
        debriRadius[i] = (float)(n % 10) / 200.0f;
        rand_s(&n);
        debriDistFromSat[i] = (float)(n % 700) / 100.0f + 9.5f;
        rand_s(&n);
        debriYCoord[i] = ((float)(n % 100) - 20.0f) / 200.0f;
    }

    textureSaturn = createTexture2D("introTextures/saturn.jpg");
    textureSaturnRing = createTexture2D("introTextures/saturnRing.png");
    debrisTexture = createTexture2D("introTextures/debrisTexture.jpg");
    bkgndTexture = createTexture2D("introTextures/universe2.jpg");
    fontTexture = createTexture2DIntro("introTextures/intro4.png");
    rasterTexture = createTexture2DIntro("introTextures/raster5.png");

    introFont = BuildFont("Georgia", 100, 0.1f);
    rasterFont = BuildFont("Digital-7 Mono Italic", 50.0f, 0.01f);
}

void drawIntro()
{
    static int flag = 0;
    static GLfloat t = 0.0f;
    GLfloat fAngle;
    static GLfloat Alpha = 0.0f;
    void raster_intro(double delta_time);

    if (flag == 0)
    {
        /*
        glBindTexture(GL_TEXTURE_2D, bkgndTexture);
        glDisable(GL_LIGHTING);

        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(300.0f, 200.0f, -250.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-300.0f, 200.0f, -250.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-300.0f, -200.0f, -250.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(300.0f, -200.0f, -250.0f);
        glEnd();
        */
        glEnable(GL_LIGHTING);
        glBindTexture(GL_TEXTURE_2D, 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        saturn(Alpha);
        glEnable(GL_TEXTURE_GEN_S); // Auto Texture Generation
        glEnable(GL_TEXTURE_GEN_T);

        glBindTexture(GL_TEXTURE_2D, fontTexture);
        glColor4f(192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f, 1.0);
        glTranslatef(-25.0f, -15.0f, 0.0f);
        glScalef(10.0f, 10.0f, 10.0f);
        glPrint(introFont, "ASTROMEDICOMP'S");
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_GEN_S); // Auto Texture Generation
        glDisable(GL_TEXTURE_GEN_T);

        fRotationAngle += 0.1f;

        if (t <= 1.0f)
        {
            eyeZ = lerp(10.0f, 80.0f, t);
            eyeX = lerp(-1.25f, 0.0f, t);
            eyeY = lerp(-1.25f, 0.0f, t);
        }
    }
    else if (flag == 1)
    {
        if (t >= 0.05f)
        {

            //  eyeZ = 2.0f;

            glDisable(GL_LIGHTING);
            glColor4f(1.0f, 1.0f, 1.0f, Alpha);

            glBindTexture(GL_TEXTURE_2D, rasterTexture);
            glEnable(GL_TEXTURE_GEN_S); // Auto Texture Generation
            glEnable(GL_TEXTURE_GEN_T);

            glPushMatrix();
            glTranslatef(-2.0f, 0.0f, -8.0f);
            glPrint(introFont, "RASTER GROUP");
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-1.0f, -1.0f, -8.0f);
            glPrint(introFont, "PRESENTS");
            glPopMatrix();

            glDisable(GL_TEXTURE_GEN_S); // Auto Texture Generation
            glDisable(GL_TEXTURE_GEN_T);

            //  raster_intro(d_time * 3);
            glBindTexture(GL_TEXTURE_2D, 0);
            glEnable(GL_LIGHTING);

            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }

    if (t < 1.3f)
    {
        if (flag == 0)
            t += 0.15f * d_time;

        if (flag == 1)
        {
            t += 0.3f * d_time;

            if (t < 0.2f)
            {
                Alpha = lerp(0.0f, 1.0f, t * 5.0f);
            }
            else if (t > 1.1f)
            {
                Alpha = lerp(1.0f, 0.0f, (t - 1.1f) * 5.0f);
            }
        }
    }
    else
    {
        flag++;
        t = 0;
        eyeZ = 2.0f;

        if (flag == 2)
        {
            eyeZ = 1550.0f;
            eyeY = 100.0f;
            eyeX = -550.0f;
        }
    }
}

void uninitIntro()
{
    if (introFont)
    {
        glDeleteLists(introFont, 256);
    }

    if (textureSaturn)
        glDeleteTextures(1, &textureSaturn);

    if (textureSaturnRing)
        glDeleteTextures(1, &textureSaturnRing);

    if (debrisTexture)
        glDeleteTextures(1, &debrisTexture);

    if (bkgndTexture)
        glDeleteTextures(1, &bkgndTexture);

    if (fontTexture)
        glDeleteTextures(1, &fontTexture);

    if (rasterTexture)
        glDeleteTextures(1, &rasterTexture);
}

GLuint createTexture2DIntro(const char *filepath)
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

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    // Texturing Contour Anchored To The Object
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    // glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return texture;
}
