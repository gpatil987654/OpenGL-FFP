#include "common.h"
#include "path.h"

GLuint pathTexture;

void initPath(void)
{
    pathTexture = createTexture2D("pathTexture/path.png");
}

void path(void)
{
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 10.0f);
    glVertex2f(1.0f, 1.0f);

    glTexCoord2f(0.0f, 10.0f);
    glVertex2f(-1.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
}
void drawPath(void)
{

    glDisable(GL_LIGHTING);
    glColor3f(0.7f, 0.7f, 0.7f);
    glBindTexture(GL_TEXTURE_2D, pathTexture);

    // Path on X-Axis
    glPushMatrix();
    glTranslatef(0.0f, -39.7f, 125.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(10.0f, 500.0f, 1.0f);
    path();
    glPopMatrix();
    // Path Towards the house on Z-Axis
    glPushMatrix();
    glTranslatef(0.0f, -39.0f, 350.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(10.0f, 250.0f, 1.0f);
    path();
    glPopMatrix();

    // Extending the path towards forest
    glPushMatrix();
    glTranslatef(0.0f, -39.0f, 850.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(10.0f, 250.0f, 1.0f);
    path();
    glPopMatrix();
    /*
        glPushMatrix();
        glTranslatef(0.0f, -30.0f, 1070.0f);
        glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);
        glRotatef(-100.0f, 1.0f, 0.0f, 0.0f);
        glScalef(10.0f, 50.0f, 1.0f);
        path();
        glPopMatrix();
    */
    /*
        // Left side path parallele to z-Axis
        glPushMatrix();
        glTranslatef(500.0f, -39.0f, 360.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(10.0f, 240.0f, 1.0f);
        path();
        glPopMatrix();
    */
    // parallel to z-axis right of the central path
    glPushMatrix();
    glTranslatef(170.0f, -39.0f, 360.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(10.0f, 240.0f, 1.0f);
    path();
    glPopMatrix();

    // Parallel to z-Axis left of the centerla path
    glPushMatrix();
    glTranslatef(-175.0f, -37.0f, 365.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(10.0f, 240.0f, 1.0f);
    path();
    glPopMatrix();

    // Path Parallel to X-Axis
    glPushMatrix();
    glTranslatef(0.0f, -39.0f, 600.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(10.0f, 500.0f, 1.0f);
    path();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_LIGHTING);
}

void uninitPath(void)
{
    if (pathTexture)
    {
        glDeleteTextures(1, &pathTexture);
    }
}
