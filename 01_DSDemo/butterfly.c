#include "common.h"
#include "butterfly.h"

GLuint butterflyTexture;
GLuint leftFeatherList, rightFeatherList, middlePortionList;
extern GLfloat eyeX, eyeY, eyeZ, centerX, centerY, centerZ;

GLfloat butX, butY, butZ;
GLfloat cenButX, cenButY, cenButZ;

void initButterfly()
{
    int i, j;
    int vi, ni, ti;

    butterflyTexture = createTexture2D("butterflyTexture/butterfly5.png");

    // Left Feather
    leftFeatherList = glGenLists(1);
    glNewList(leftFeatherList, GL_COMPILE);
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, butterflyTexture);

    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(-1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.5f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(0.5f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_LIGHTING);
    glEndList();

    // Right Feather List
    rightFeatherList = glGenLists(1);
    glNewList(rightFeatherList, GL_COMPILE);
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, butterflyTexture);

    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.5f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(0.5f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_LIGHTING);
    glEndList();
}

void butterfly(void)
{
    int i, j;
    int vi, ni, ti;
    static GLfloat fAngle = 0.0f;
    static int flag = 0;

    static GLfloat stop = 0;
    static int t_elpased = 0.0f;

    if (flag == 0)
    {
        fAngle += 300.0f * d_time;
        if (fAngle >= 20.0f)
        {
            flag = 1;
            t_elpased++;
        }
    }
    else
    {
        if (t_elpased == 4)
        {
            stop += d_time;

            if (stop >= 0.3f)
            {
                stop = 0;
                t_elpased = 0;
            }
        }
        else
        {
            fAngle -= 300.0f * d_time;
            if (fAngle <= -40.0f)
                flag = 0;
        }
    }

    glPushMatrix();
    glRotatef(fAngle, 0.0f, 0.0f, 1.0f);
    glCallList(leftFeatherList);
    glPopMatrix();

    glCallList(middlePortionList);

    glPushMatrix();
    glRotatef(fAngle, 0.0f, 0.0f, -1.0f);
    glCallList(rightFeatherList);
    glPopMatrix();

    // glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
}

float calangle()
{
    float cx = cenButX - butX;
    float cy = cenButY - butY;
    float cz = cenButZ - butZ;

    float rad = sqrt(cx * cx + cy * cy + cz * cz);
    cx /= rad;
    cy /= rad;
    cz /= rad;

    float ex = 0;
    float ey = 0;
    float ez = 0.0f - butZ;

    rad = sqrt(ex * ex + ey * ey + ez * ez);

    ex /= rad;
    ey /= rad;
    ez /= rad;

    float fAngle = acos(ex * cx + ez * cz) * 180.0f / M_PI;

    if (cenButX < butX)
        return fAngle;
    else
        return -fAngle;
}

void drawButterfLy()
{

    // butX = eyeX;
    // butY = eyeY - 1.0f;
    // butZ = eyeZ - 10;

    // cenButX = centerX;
    // cenButY = centerY;
    // cenButZ = centerZ;

    glDisable(GL_BLEND);

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    butterfly();
    glPopMatrix();

    glEnable(GL_BLEND);
}

void uninitButterfly()
{
    if (leftFeatherList)
        glDeleteLists(leftFeatherList, 1);

    if (rightFeatherList)
        glDeleteLists(rightFeatherList, 1);

    if (middlePortionList)
        glDeleteLists(middlePortionList, 1);

    if (butterflyTexture)
        glDeleteTextures(1, &butterflyTexture);
}
