#include "common.h"
#include "house.h"

GLuint roofTexture, groundTexture, wallTexture1;
GLuint windowTexture, windowTexture2, patraTexture, doorTexture;
GLfloat materialAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat materialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat materialSpecular[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat materialShininess[] = {80.0f};
GLuint houseDisplayList1, houseDisplayList2;

void house1(int flag);

void house_widnow1(void)
{
    glBindTexture(GL_TEXTURE_2D, windowTexture);
    //  glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glScalef(0.5f, 0.04f, 0.03f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.9f, 0.0f);
    glScalef(0.5f, 0.04f, 0.03f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, -0.45f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.03f, 0.03f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, -0.45f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.03f, 0.03f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.65f, -0.425f, 0.1f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.25f, 0.5f, 0.03f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.65f, -0.425f, 0.1f);
    glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.25f, 0.5f, 0.03f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.45f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.03f, 0.03f);
    cube();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0.0f, -0.41f, 0.01f);
    glScalef(0.5f, 0.45f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    // glColor3f(1.0f, 1.0f, 1.0f);
    glColor3f(0.7f, 0.7f, 0.7f);
}

void house_widnow2(void)
{
    glBindTexture(GL_TEXTURE_2D, windowTexture2);
    //  glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glScalef(0.8f, 0.4f, 1.0f);

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
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
    // glColor3f(1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void woodenBlocks(void)
{
    glBindTexture(GL_TEXTURE_2D, windowTexture);
    glPushMatrix();
    glScalef(2.0f, 0.1f, 0.1f);
    cube();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void upperRoof(void)
{

    // Roof
    glBindTexture(GL_TEXTURE_2D, roofTexture);
    // glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    calculateNormal(2.0f, 3.0f, 0.0f, 4.0f, 1.0f, 3.0f, -4.0f, 1.0f, 3.0f);
    glTexCoord2f(0.8f, 1.0f);
    glVertex3f(2.0f, 3.0f, 0.0f);
    glTexCoord2f(0.2f, 1.0f);
    glVertex3f(-2.0f, 3.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.0f, 1.0f, 3.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.0f, 1.0f, 3.0f);

    calculateNormal(2.0f, 3.0f, 0.0f, -2.0f, 3.0f, 0.0f, -4.0f, 1.0f, -3.0f);
    glTexCoord2f(0.8f, 1.0f);
    glVertex3f(2.0f, 3.0f, 0.0f);
    glTexCoord2f(0.2f, 1.0f);
    glVertex3f(-2.0f, 3.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.0f, 1.0f, -3.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.0f, 1.0f, -3.0f);

    glEnd();

    glBegin(GL_TRIANGLES);
    calculateNormal(-2.0f, 3.0f, 0.0f, -4.0f, 1.0f, 3.0f, -4.0f, 1.0f, -3.0f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(-2.0f, 3.0f, 0.0f);
    glTexCoord2f(-0.2f, 0.0f);
    glVertex3f(-4.0f, 1.0f, -3.0f);
    glTexCoord2f(1.2f, 0.0f);
    glVertex3f(-4.0f, 1.0f, 3.0f);

    calculateNormal(2.0f, 3.0f, 0.0f, 4.0f, 1.0f, -3.0f, 4.0f, 1.0f, 3.0f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(2.0f, 3.0f, 0.0f);
    glTexCoord2f(-0.2f, 0.0f);
    glVertex3f(4.0f, 1.0f, -3.0f);
    glTexCoord2f(1.2f, 0.0f);
    glVertex3f(4.0f, 1.0f, 3.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void upperWalls(void)
{
    glBindTexture(GL_TEXTURE_2D, wallTexture1);
    // Upper Floor Walls
    glBegin(GL_QUADS);
    // Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(6.0f, 2.0f);
    glVertex3f(3.5f, 1.2f, 2.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-3.5f, 1.2f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-3.5f, 0.0f, 2.5f);
    glTexCoord2f(6.0f, 0.0f);
    glVertex3f(3.5f, 0.0f, 2.5f);

    // Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(6.0f, 2.0f);
    glVertex3f(3.5f, 1.2f, -2.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(3.5f, 1.2f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(3.5f, 0.0f, 2.5f);
    glTexCoord2f(6.0f, 0.0f);
    glVertex3f(3.5f, 0.0f, -2.5f);

    // Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(6.0f, 2.0f);
    glVertex3f(3.5f, 1.2f, -2.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-3.5f, 1.2f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-3.5f, 0.0f, -2.5f);
    glTexCoord2f(6.0f, 0.0f);
    glVertex3f(3.5f, 0.0f, -2.5f);

    // Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(6.0f, 2.0f);
    glVertex3f(-3.5f, 1.2f, 2.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-3.5f, 1.2f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-3.5f, 0.0f, -2.5f);
    glTexCoord2f(6.0f, 0.0f);
    glVertex3f(-3.5f, 0.0f, 2.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void windowsOnUpperWalls(void)
{
    // Windows
    // FrontSide
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 2.5f);
    house_widnow1();
    glPopMatrix();

    // Back Side
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, -2.5f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    house_widnow1();
    glPopMatrix();

    // Left Side
    glPushMatrix();
    glTranslatef(3.51f, 0.5f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    house_widnow2();
    glPopMatrix();

    // Right Side
    glPushMatrix();
    glTranslatef(-3.51f, 0.5f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    house_widnow2();
    glPopMatrix();
}

void upperBlocksStructure(void)
{
    // Lower Area Of House
    // Front
    for (int i = -3; i < 4; i++)
    {
        glPushMatrix();
        glTranslatef(i, -0.5f, 3.0f);
        glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        woodenBlocks();
        glPopMatrix();
    }
    // Back
    for (int i = -3; i < 4; i++)
    {
        glPushMatrix();
        glTranslatef(i, -0.5f, -3.0f);
        glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        woodenBlocks();
        glPopMatrix();
    }

    // Right
    for (int i = -2; i < 3; i++)
    {
        glPushMatrix();
        glTranslatef(4.0f, -0.5f, i);
        glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
        // glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        woodenBlocks();
        glPopMatrix();
    }

    // Left
    for (int i = -2; i < 3; i++)
    {
        glPushMatrix();
        glTranslatef(-4.0f, -0.5f, i);
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        woodenBlocks();
        glPopMatrix();
    }

    // Corner blocks
    glPushMatrix();
    glTranslatef(3.8f, -0.5f, 2.8f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    woodenBlocks();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.8f, -0.5f, 2.8f);
    glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    woodenBlocks();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.8f, -0.5f, -2.8f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    woodenBlocks();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.8f, -0.5f, -2.8f);
    glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    woodenBlocks();
    glPopMatrix();
}

void lowerWalls(void)
{
    // glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, wallTexture1);
    // Upper Floor Walls
    glBegin(GL_QUADS);
    // Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(8.0f, 6.0f);
    glVertex3f(4.5f, 1.2f, 3.5f);
    glTexCoord2f(0.0f, 6.0f);
    glVertex3f(-4.5f, 1.2f, 3.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.5f, -2.0f, 3.5f);
    glTexCoord2f(8.0f, 0.0f);
    glVertex3f(4.5f, -2.0f, 3.5f);

    // Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(8.0f, 6.0f);
    glVertex3f(4.5f, 1.2f, -3.5f);
    glTexCoord2f(0.0f, 6.0f);
    glVertex3f(4.5f, 1.2f, 3.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4.5f, -2.0f, 3.5f);
    glTexCoord2f(8.0f, 0.0f);
    glVertex3f(4.5f, -2.0f, -3.5f);

    // Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(8.0f, 6.0f);
    glVertex3f(4.5f, 1.2f, -3.5f);
    glTexCoord2f(0.0f, 6.0f);
    glVertex3f(-4.5f, 1.2f, -3.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.5f, -2.0f, -3.5f);
    glTexCoord2f(8.0f, 0.0f);
    glVertex3f(4.5f, -2.0f, -3.5f);

    // Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(8.0f, 6.0f);
    glVertex3f(-4.5f, 1.2f, 3.5f);
    glTexCoord2f(0.0f, 6.0f);
    glVertex3f(-4.5f, 1.2f, -3.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.5f, -2.0f, -3.5f);
    glTexCoord2f(8.0f, 0.0f);
    glVertex3f(-4.5f, -2.0f, 3.5f);
    glEnd();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    // glColor3f(1.0f, 1.0f, 1.0f);
}

void lowerRoof(void)
{
    // Lower Roof
    // Roof
    glBindTexture(GL_TEXTURE_2D, roofTexture);
    // glColor3f(0.7f, 0.7f, 0.7f);

    glPushMatrix();
    glTranslatef(0.0f, -0.5f, 3.2f);
    glRotatef(-45.0f, 1.0f, 0.0, 0.0f);
    glScalef(3.5f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.05f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.05f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.54f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.54f, -2.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.5f, -3.2f);
    glRotatef(45.0f, 1.0f, 0.0, 0.0f);
    glScalef(3.5f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.05f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.05f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.54f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.54f, -2.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.2f, -0.5f, 0.0f);
    glRotatef(45.0f, 0.0f, 0.0, 1.0f);
    glRotatef(90.0f, 0.0f, 1.0, 0.0f);
    glScalef(2.5f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.05f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.05f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.75f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.75f, -2.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.2f, -0.5f, 0.0f);
    glRotatef(-45.0f, 0.0f, 0.0, 1.0f);
    glRotatef(90.0f, 0.0f, 1.0, 0.0f);
    glScalef(2.5f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.05f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.05f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.75f, -2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.75f, -2.0f);
    glEnd();
    glPopMatrix();
}

void houseDoor(void)
{
    glPushMatrix();

    glTranslatef(0.0f, -3.0f, 3.56f);

    glBindTexture(GL_TEXTURE_2D, windowTexture);
    // glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, 0.85f, 0.0f);
    glScalef(0.6f, 0.04f, 0.04f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, -0.85f, 0.0f);
    glScalef(0.6f, 0.04f, 0.04f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.9f, 0.04f, 0.03f);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.9f, 0.04f, 0.03f);
    cube();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, doorTexture);
    // glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(0.45f, 0.8f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-0.45f, 0.8f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.45f, -0.8f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.45f, -0.8f);
    glEnd();
    //   glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5f, -2.5f, 3.56f);
    house_widnow1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5f, -2.5f, 3.56f);
    house_widnow1();
    glPopMatrix();
}

void frontPortion(void)
{
    glBindTexture(GL_TEXTURE_2D, patraTexture);
    // glColor3f(0.7f, 0.7f, 0.7f);

    glPushMatrix();
    glTranslatef(0.0f, -1.7f, 5.0f);
    glRotatef(-80.0f, 1.0f, 0.0, 0.0f);
    glScalef(5.25f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);

    glTexCoord2f(4.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, -1.5f);
    glTexCoord2f(4.0f, 0.0f);
    glVertex2f(1.0f, -1.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5.0f, -3.1f, 5.9f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.6f, 1.0f, 1.0f);
    woodenBlocks();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0f, -3.1f, 5.9f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.6f, 1.0f, 1.0f);
    woodenBlocks();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0f, -3.1f, 5.9f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.6f, 1.0f, 1.0f);
    woodenBlocks();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0f, -3.1f, 5.9f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.6f, 1.0f, 1.0f);
    woodenBlocks();
    glPopMatrix();
}

// Call in initialise()
void initHouse(void)
{
    glEnable(GL_LIGHTING);
    roofTexture = createTexture2D("houseTexture/roof.png");
    groundTexture = createTexture2D("houseTexture/ground.jpg");
    wallTexture1 = createTexture2D("houseTexture/wall.png");
    windowTexture = createTexture2D("houseTexture/wood.png");
    windowTexture2 = createTexture2D("houseTexture/window2.jpg");
    patraTexture = createTexture2D("houseTexture/patra.png");
    doorTexture = createTexture2D("houseTexture/door.png");

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    houseDisplayList1 = glGenLists(1);
    houseDisplayList2 = glGenLists(1);

    glNewList(houseDisplayList1, GL_COMPILE);
    house1(0);
    glEndList();

    glNewList(houseDisplayList2, GL_COMPILE);
    house1(1);
    glEndList();
}

extern GLfloat lightPosition[4];

// Call in display()
void house1(int flag)
{
    glDisable(GL_LIGHTING);
    // glEnable(GL_LIGHTING);
    void houseDoor(void);

    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);
    glBegin(GL_QUADS);
    glVertex3f(5.6f, -3.8f, -5.6f);
    glVertex3f(-5.6f, -3.8f, -5.6f);
    glVertex3f(-5.6f, -3.8f, 5.6f);
    glVertex3f(5.6f, -3.8f, 5.6f);
    glEnd();

    glColor4f(0.7f, 0.7f, 0.7f, 1.0f);

    if (flag == 0)
        upperRoof();
    else
    {
        glPushMatrix();
        glTranslatef(0.0f, -1.1f, 0.0f);
        glScalef(1.0f, 1.2f, 1.0f);
        upperRoof();
        glPopMatrix();
    }

    upperBlocksStructure();
    lowerRoof();
    lowerWalls();
    houseDoor();

    if (flag == 0)
    {
        frontPortion();
        upperWalls();
        windowsOnUpperWalls();
    }
    /*
        // Shadow
        GLfloat EqnPlane[4] = {0.0f, 1.0f, 0.0f, 0.39f};

        glPushMatrix();
        glTranslatef(0.0f, -3.6f, 0.0f);

        shadowMatrix(EqnPlane, lightPosition);
        // glScalef(1.0f, 0.0f, 1.0f);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        //   glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.0f, 0.0f, 0.0f, 0.25f);
        // glSclaef
        upperRoof();
        // upperWalls();
        // windowsOnUpperWalls();
        //  upperBlocksStructure();
        lowerRoof();
        // lowerWalls();
        frontPortion();
        // houseDoor();

        glPopMatrix();
    */
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    // glDisable(GL_BLEND);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void drawHouse(void)
{

    glPushMatrix();
    glTranslatef(-500.0f, 0.0f, 600.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(10.0f, 10.0f, 15.0f);
    glCallList(houseDisplayList1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(500.0f, 0.0f, 600.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(10.0f, 10.0f, 15.0f);
    glCallList(houseDisplayList2);
    glPopMatrix();
}

// Call in uninitialise()
void uninitHouse(void)
{
    if (houseDisplayList1)
    {
        glDeleteLists(houseDisplayList1, 1);
        houseDisplayList1 = 0;
    }

    if (houseDisplayList2)
    {
        glDeleteLists(houseDisplayList2, 1);
        houseDisplayList2 = 0;
    }

    if (roofTexture)
    {
        glDeleteTextures(1, &roofTexture);
    }

    if (groundTexture)
    {
        glDeleteTextures(1, &groundTexture);
    }

    if (wallTexture1)
    {
        glDeleteTextures(1, &wallTexture1);
    }

    if (windowTexture)
    {
        glDeleteTextures(1, &windowTexture);
    }

    if (windowTexture2)
    {
        glDeleteTextures(1, &windowTexture2);
    }
    if (patraTexture)
    {
        glDeleteTextures(1, &patraTexture);
    }

    if (doorTexture)
    {
        glDeleteTextures(1, &doorTexture);
    }
}
