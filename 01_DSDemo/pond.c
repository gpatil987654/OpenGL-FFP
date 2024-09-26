#include "common.h"
#include "pond.h"

GLuint waterTexture;
extern GLuint mangoTreePitTexture;

void initPond()
{
    waterTexture = createTexture2D("pondTexture/water2.png");
    // wallTexture = createTexture2D("pondTexture/wall.png");
}
void drawPond()
{
    static GLfloat t = 0.0f;
    static int flag = 0;

    if (flag == 0)
    {
        t -= 0.01f * d_time;
        if (t < -0.01f)
            flag = 1;
    }
    else
    {
        t += 0.01f * d_time;
        if (t >= 0.01f)
            flag = 0;
    }
    glDisable(GL_LIGHTING);
    glColor3f(0.7f, 0.7f, 0.7f);

    glBindTexture(GL_TEXTURE_2D, waterTexture);
    glPushMatrix();
    glScalef(550, 100, 400);
    glTranslatef(-0.8f, -0.1f + t, -2.2f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
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

    glBindTexture(GL_TEXTURE_2D, mangoTreePitTexture);
    glPushMatrix();
    glScalef(600, 20, 100);
    glTranslatef(-0.6f, -1.0f, -4.8f);
    // glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(15.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);

    glTexCoord2f(15.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void uninitPond()
{
    if (waterTexture)
        glDeleteTextures(1, &waterTexture);

    // if (wallTexture)
    //   glDeleteTextures(1, &wallTexture);
}
