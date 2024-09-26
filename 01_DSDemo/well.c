#include "common.h"
#include "well.h"

GLuint wellTexture;
GLuint pullyTexture, metalTexture, waterTexture, ropeTexture;
extern GLUquadric *quadric;

GLuint wellDisplayList;

void initWell()
{
    wellTexture = createTexture2D("wellTexture/well.png");
    pullyTexture = createTexture2D("wellTexture/pully.png");
    metalTexture = createTexture2D("wellTexture/metal.png");
    waterTexture = createTexture2D("wellTexture/water2.png");
    ropeTexture = createTexture2D("wellTexture/rope.png");

    void drawWellDisplayList();

    wellDisplayList = glGenLists(1);

    glNewList(wellDisplayList, GL_COMPILE);
    drawWellDisplayList();
    glEndList();
}
void drawWellDisplayList()
{
    void wellStructure(GLuint texture);
    void woodenBlocks2(void);
    void pully(void);

    glDisable(GL_LIGHTING);
    glColor3f(0.7f, 0.7f, 0.7f);

    glPushMatrix();
    glTranslatef(130.0f, -32.0f, 0.0f);
    glScalef(15.0f, 15.0f, 15.0f);
    wellStructure(wellTexture);

    // Left Woodden block
    glPushMatrix();
    glTranslatef(-1.3f, 1.0f, 0.0f);
    glScalef(0.1f, 1.0f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // right wooden block
    glPushMatrix();
    glTranslatef(1.3f, 1.0f, 0.0f);
    glScalef(0.1f, 1.0f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Top Wooden block
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);
    glScalef(1.4f, 0.1f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Pully
    glPushMatrix();
    glTranslatef(0.0f, 1.8f, 0.0f);
    glScalef(0.3f, 0.3f, 0.3f);
    pully();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Water
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, waterTexture);
    // glColor3f(15.0f / 255.0f, 94.0f / 255.0f, 156.0f / 255.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(quadric, 0.0f, 1.47f, 10, 10);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();

    // rope
    void rope(void);

    glPushMatrix();
    rope();
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_LIGHTING);
}

void drawWell(void)
{
    glCallList(wellDisplayList);
}

void uninitWell()
{
}

void wellStructure(GLuint texture)
{
    GLfloat fAngle1 = 0.0f, fAngle2 = 0.0f;
    GLfloat height = 0.5f;
    GLfloat r1 = 1.5f, r2 = 1.2f;
    GLfloat N = 15;

    glBindTexture(GL_TEXTURE_2D, wellTexture);
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    for (int i = 1; i <= N; i++)
    {
        fAngle1 = 2 * M_PI * (float)i / N;
        fAngle2 = 2 * M_PI * (float)(i - 1) / N;
        float d = 1.0f / N;

        glTexCoord2f(d * i, 1.0f);
        glVertex3f(r1 * cos(fAngle1), r1 * sin(fAngle1), -height);
        glTexCoord2f(d * (i - 1), 1.0f);
        glVertex3f(r1 * cos(fAngle2), r1 * sin(fAngle2), -height);
        glTexCoord2f(d * (i - 1), 0.0f);
        glVertex3f(r1 * cos(fAngle2), r1 * sin(fAngle2), height);
        glTexCoord2f(d * i, 0.0f);
        glVertex3f(r1 * cos(fAngle1), r1 * sin(fAngle1), height);
    }

    glEnd();

    glScalef(0.8f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    for (int i = 1; i <= N; i++)
    {
        fAngle1 = 2 * M_PI * (float)i / N;
        fAngle2 = 2 * M_PI * (float)(i - 1) / N;
        float d = 1.0f / N;

        glTexCoord2f(d * i, 1.0f);
        glVertex3f(r1 * cos(fAngle1), r1 * sin(fAngle1), -height);
        glTexCoord2f(d * (i - 1), 1.0f);
        glVertex3f(r1 * cos(fAngle2), r1 * sin(fAngle2), -height);
        glTexCoord2f(d * (i - 1), 0.0f);
        glVertex3f(r1 * cos(fAngle2), r1 * sin(fAngle2), height);
        glTexCoord2f(d * i, 0.0f);
        glVertex3f(r1 * cos(fAngle1), r1 * sin(fAngle1), height);
    }

    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, height - 0.05f, 0.0f);
    glRotatef(90.0f, 1, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    for (int i = 1; i <= N; i++)
    {
        fAngle1 = 2 * M_PI * (float)i / N;
        fAngle2 = 2 * M_PI * (float)(i - 1) / N;
        glTexCoord2f(0.5f, 0.5f);
        glVertex3f(r2 * cos(fAngle1), r2 * sin(fAngle1), 0);
        glTexCoord2f(0.3f, 0.5f);
        glVertex3f(r2 * cos(fAngle2), r2 * sin(fAngle2), 0);
        glTexCoord2f(0.3f, 0.3f);
        glVertex3f(r1 * cos(fAngle2), r1 * sin(fAngle2), 0);
        glTexCoord2f(0.5f, 0.3f);
        glVertex3f(r1 * cos(fAngle1), r1 * sin(fAngle1), 0);
    }

    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void pully(void)
{

    glBindTexture(GL_TEXTURE_2D, pullyTexture);

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.2f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2f, -0.3f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, metalTexture);
    gluCylinder(quadric, 0.1f, 0.1f, 0.2f, 5, 5);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void rope(void)
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ropeTexture);
    glTranslatef(129.5f, -3.0f, -0.4f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadric, 0.1f, 0.1f, 30.0f, 10, 10);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, ropeTexture);
    glTranslatef(129.5f, -3.0f, 0.4f);
    glRotatef(-40.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadric, 0.1f, 0.1f, 30.0f, 10, 10);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}
