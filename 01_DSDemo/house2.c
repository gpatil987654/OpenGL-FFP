#include "common.h"
#include "house2.h"

extern GLuint roofTexture, groundTexture;
extern GLuint windowTexture, windowTexture2, patraTexture, doorTexture;
extern GLUquadric *quadric;

GLuint window2Texture;
GLuint windowTexture3, ganapatiTexture, sideWallTexture, innerWindowDesignTexture, chainTexture, wallTexture;
GLuint insideRoofTexture;
GLuint rangoliTexture;

GLuint house2DisplayList;
extern int open_door, close_door;
extern int jhopala_move;
extern int start_mirror;
extern float eyeX, eyeY, eyeZ;

GLfloat mirrorDiffuse[] = {1.0f, 1.0f, 1.0f, 0.1f};
GLfloat mirrorAmbient[] = {1.0f, 1.0f, 1.0f, 0.1f};
GLfloat mirrorSpecular[] = {1.0f, 1.0f, 1.0f, 0.3f};
GLfloat mirrorShininess[] = {180.0f};

void house2(void);
void sideWall(void);
void jhopala(void);
void house2_widnow1(void);
void house2_widnow2(void);
void woodenBlocks2(void);
void house2_Door(void);

void initHouse2(void)
{

    window2Texture = createTexture2D("house2Textures/window.png");
    windowTexture3 = createTexture2D("house2Textures/window5.png");
    ganapatiTexture = createTexture2D("house2Textures/ganesh.png");
    sideWallTexture = createTexture2D("houseTexture/wall.png");
    innerWindowDesignTexture = createTexture2D("house2Textures/windowDesign.png");
    chainTexture = createTexture2D("house2Textures/chain.png");
    wallTexture = createTexture2D("house2Textures/wallnew.png");
    insideRoofTexture = createTexture2D("house2Textures/wood.png");
    rangoliTexture = createTexture2D("house2Textures/rangoli3.png");

    house2DisplayList = glGenLists(1);

    glNewList(house2DisplayList, GL_COMPILE);
    house2();
    glEndList();
}

extern int mirror_show;

void chair(void)
{
    // Front Side Legs
    glPushMatrix();
    glTranslatef(1.0f, 0.0f, 1.0f);
    glScalef(0.1f, 1.0f, 0.2f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, 1.0f);
    glScalef(0.1f, 1.0f, 0.2f);
    woodenBlocks2();
    glPopMatrix();

    // Back Side Legs
    glPushMatrix();
    glTranslatef(1.0f, 0.0f, -1.0f);
    glScalef(0.1f, 1.0f, 0.2f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, -1.0f);
    glScalef(0.1f, 1.0f, 0.2f);
    woodenBlocks2();
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glScalef(1.2f, 0.1f, 1.2f);
    woodenBlocks2();
    glPopMatrix();

    // back side resting
    glPushMatrix();
    glTranslatef(1.0f, 2.5f, -1.0f);
    glScalef(0.1f, 1.5f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, 2.5f, -1.0f);
    glScalef(0.1f, 1.5f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 3.8f, -1.0f);
    glScalef(1.0f, 0.2f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 1.8f, -1.0f);
    glScalef(1.0f, 0.2f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5f, 3.0f, -1.0f);
    glScalef(0.1f, 1.0f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5f, 3.0f, -1.0f);
    glScalef(0.1f, 1.0f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Hands Of chair
    glPushMatrix();
    glTranslatef(1.0f, 1.5f, 1.0f);
    glScalef(0.1f, 0.5f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, 1.5f, 1.0f);
    glScalef(0.1f, 0.5f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(1.0f, 2.0f, 0.3f);
    glScalef(0.1f, 0.1f, 1.2f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0f, 2.0f, 0.3f);
    glScalef(0.1f, 0.1f, 1.2f);
    woodenBlocks2();
    glPopMatrix();
}

void table(void)
{
    // Front Side Legs
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 1.0f);
    glScalef(0.1f, 1.0f, 0.2f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 1.0f);
    glScalef(0.1f, 1.0f, 0.2f);
    woodenBlocks2();
    glPopMatrix();

    // Back Side Legs
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, -1.0f);
    glScalef(0.1f, 1.0f, 0.2f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, -1.0f);
    glScalef(0.1f, 1.0f, 0.2f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glScalef(2.2f, 0.1f, 1.2f);
    woodenBlocks2();
    glPopMatrix();
}

void drawHouse2(void)
{
    glDisable(GL_BLEND);
    glDisable(GL_LIGHTING);

    double clipPlane[] = {0.0f, 0.0f, 1.0f, -5.5f};
    double clipPlane1[] = {1.0f, 0.0f, 0.0f, 3.4f};
    double clipPlane2[] = {-1.0f, 0.0f, 0.0f, 5.5f};

    GLfloat x1 = -2.5f * 10.0f, y1 = 0.0f, z1 = 5.4f * 15.0f - 35.0f;
    GLfloat x2 = -1.5f * 10.0f, y2 = 0.0f, z2 = 5.4f * 15.0f - 35.0f;

    if (start_mirror == -1)
    {
        /*
                x1 = (-eyeX + 0.0f) / 10.0f - x1;
                y1 = 0.0 - y1;
                z1 = (eyeZ + 35.0f) / 15.0f - z1;

                x2 = (-eyeX - 0.0f) / 10.0f - x2;
                y2 = 0.0 - y2;
                z2 = (eyeZ + 35.0f) / 15.0f - z2;
        */

        x1 = (eyeX)-x1;
        y1 = 0.0 - y1;
        z1 = (eyeZ)-z1;

        x2 = (eyeX)-x2;
        y2 = 0.0 - y2;
        z2 = (eyeZ)-z2;

        GLfloat norX, norY, norZ;

        norX = -z1;
        norY = 0.0f;
        norZ = x1;

        clipPlane1[0] = norX;
        clipPlane1[1] = norY;
        clipPlane1[2] = norZ;
        clipPlane1[3] = -(norX * -2.5f + norY * 0 + norZ * 5.4f);

        /// Second

        norX = z2;
        norY = 0.0f;
        norZ = x2;

        clipPlane2[0] = norX;
        clipPlane2[1] = norY;
        clipPlane2[2] = norZ;

        clipPlane2[3] = -(norX * -1.5f + norY * 0 + norZ * 5.4f);
    }

    // Mirror
    /*
    if (eyeX < 0)
        clipPlane1[3] = -eyeX;
    else if (eyeX > 0)
        clipPlane2[3] = eyeX;
*/

    glColor3f(1.0f, 1.0f, 1.0f);
    // Frame
    // Left
    glPushMatrix();
    glTranslatef(-0.2f, 0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(-1.5f, -5.3f, 5.4f);
    glScalef(0.03f, 0.75f, 0.03f);
    woodenBlocks2();
    glPopMatrix();

    // Right
    glPushMatrix();
    glTranslatef(-2.2f, -5.3f, 5.4f);
    glScalef(0.03f, 0.75f, 0.03f);
    woodenBlocks2();
    glPopMatrix();

    // Top
    glPushMatrix();
    glTranslatef(-1.85f, -4.6f, 5.4f);
    glScalef(0.35f, 0.03f, 0.03f);
    woodenBlocks2();
    glPopMatrix();

    // Bottom
    glPushMatrix();
    glTranslatef(-1.85f, -6.0f, 5.4f);
    glScalef(0.35f, 0.03f, 0.03f);
    woodenBlocks2();
    glPopMatrix();
    glPopMatrix();

    if (mirror_show == 1)
    {
        // Mirror
        glClear(GL_STENCIL_BUFFER_BIT);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glDepthMask(GL_FALSE);
        // glDisable(GL_DEPTH_TEST);

        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
        glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

        glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
        glPushMatrix();
        glTranslatef(-0.2f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-2.2f, -4.6f, 5.4f);
        glVertex3f(-1.5f, -4.6f, 5.4f);
        glVertex3f(-1.5f, -6.0f, 5.4f);
        glVertex3f(-2.2f, -6.0f, 5.4f);
        glEnd();
        glPopMatrix();
        //   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_TRUE);

        glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

        glEnable(GL_CLIP_PLANE0);
        glEnable(GL_CLIP_PLANE1);
        glEnable(GL_CLIP_PLANE2);

        glClipPlane(GL_CLIP_PLANE0, clipPlane);
        glClipPlane(GL_CLIP_PLANE1, clipPlane1);
        glClipPlane(GL_CLIP_PLANE2, clipPlane2);

        {

            glPushMatrix();

            //  glTranslatef(0.0f, 0.0f, 10.0f);
            // glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            glTranslatef(0.0f, 0.0f, 10.8f);
            glScalef(1.0f, 1.0f, -1.0f);
            glCallList(house2DisplayList);

            glPopMatrix();
        }
        glDisable(GL_CLIP_PLANE0);
        glDisable(GL_CLIP_PLANE1);
        glDisable(GL_CLIP_PLANE2);

        glDisable(GL_STENCIL_TEST);

        glEnable(GL_BLEND);
        glColor4f(168.0f / 255.0f, 176.0f / 255.0f, 178.0f / 255.0f, 0.5f);
        glPushMatrix();
        glTranslatef(-0.2f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex3f(-2.2f, -4.6f, 5.4f);
        glVertex3f(-1.5f, -4.6f, 5.4f);
        glVertex3f(-1.5f, -6.0f, 5.4f);
        glVertex3f(-2.2f, -6.0f, 5.4f);
        glEnd();
        glPopMatrix();
        //   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        glDisable(GL_BLEND);
    }
    // house2();
    glCallList(house2DisplayList);

    // House Door
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 1.95f);
    glScalef(1.7f, 1.52f, 1.0f);
    house2_Door();
    glPopMatrix();

    // Jhopala
    glPushMatrix();
    glTranslatef(3.25f, -6.0f, 2.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.38f, 0.8f, 1.0f);
    jhopala();
    glPopMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Shadow Square
    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);

    glBegin(GL_QUADS);
    glVertex3f(7.0f, -6.98f, -6.0f);
    glVertex3f(-7.0f, -6.98f, -6.0f);
    glVertex3f(-7.0f, -6.98f, 8.5f);
    glVertex3f(7.0f, -6.98f, 8.5f);
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
}

void uninitHouse2(void)
{
    if (house2DisplayList)
    {
        glDeleteLists(house2DisplayList, 1);
        house2DisplayList = 0;
    }

    if (window2Texture)
        glDeleteTextures(1, &window2Texture);

    if (windowTexture3)
        glDeleteTextures(1, &windowTexture3);

    if (ganapatiTexture)
        glDeleteTextures(1, &ganapatiTexture);

    if (sideWallTexture)
        glDeleteTextures(1, &sideWallTexture);

    if (innerWindowDesignTexture)
        glDeleteTextures(1, &innerWindowDesignTexture);

    if (chainTexture)
        glDeleteTextures(1, &chainTexture);

    if (wallTexture)
        glDeleteTextures(1, &wallTexture);

    if (insideRoofTexture)
        glDeleteTextures(1, &insideRoofTexture);

    if (rangoliTexture)
        glDeleteTextures(1, &rangoliTexture);
}

void house2(void)
{
    void woodenBlocks2(void);
    void jhopala(void);

    // Roof
    glBindTexture(GL_TEXTURE_2D, roofTexture);
    glColor3f(0.7f, 0.7f, 0.7f);

    glBegin(GL_QUADS);
    // Front
    glTexCoord2f(0.6f, 1.0f);
    glVertex3f(2.0f, 1.0f, 0.0f);
    glTexCoord2f(0.3f, 1.0f);
    glVertex3f(-2.0f, 1.0f, 0.0f);
    glTexCoord2f(0.1f, 0.0f);
    glVertex3f(-5.0f, -1.0f, 3.0f);
    glTexCoord2f(0.8f, 0.0f);
    glVertex3f(5.0f, -1.0f, 3.0f);

    // Back
    glTexCoord2f(0.6f, 1.0f);
    glVertex3f(-2.0f, 1.0f, 0.0f);
    glTexCoord2f(0.3f, 1.0f);
    glVertex3f(2.0f, 1.0f, 0.0f);
    glTexCoord2f(0.1f, 0.0f);
    glVertex3f(5.0f, -1.0f, -3.0f);
    glTexCoord2f(0.8f, 0.0f);
    glVertex3f(-5.0f, -1.0f, -3.0f);

    glEnd();

    glBegin(GL_TRIANGLES);
    // Left
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(-2.0f, 1.0f, 0.0f);
    glTexCoord2f(0.1f, 0.0f);
    glVertex3f(-5.0f, -1.0f, -3.0f);
    glTexCoord2f(0.9f, 0.0f);
    glVertex3f(-5.0f, -1.0f, 3.0f);

    // Right
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(2.0f, 1.0f, 0.0f);
    glTexCoord2f(0.1f, 0.0f);
    glVertex3f(5.0f, -1.0f, 3.0f);
    glTexCoord2f(0.9f, 0.0f);
    glVertex3f(5.0f, -1.0f, -3.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    ////////////////////////////////////////////////////////////////////////////////////
    // Upper Walls
    // Upper Front Side
    glClear(GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(GL_TRUE);
    glStencilFunc(GL_ALWAYS, 1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    glBegin(GL_QUADS);
    // Upper Front Area
    //  door area
    glVertex3f(0.5f, -1.0f, 2.5f);
    glVertex3f(-0.5f, -1.0f, 2.5f);
    glVertex3f(-0.5f, -2.0f, 2.5f);
    glVertex3f(0.5f, -2.0f, 2.5f);

    // Left window
    glVertex3f(3.0f, -1.2f, 2.5f);
    glVertex3f(2.0f, -1.2f, 2.5f);
    glVertex3f(2.0f, -1.8f, 2.5f);
    glVertex3f(3.0f, -1.8f, 2.5f);

    // right window
    glVertex3f(-2.0f, -1.2f, 2.5f);
    glVertex3f(-3.0f, -1.2f, 2.5f);
    glVertex3f(-3.0f, -1.8f, 2.5f);
    glVertex3f(-2.0f, -1.8f, 2.5f);
    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilFunc(GL_NOTEQUAL, 1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(5.0f, 1.f);
    glVertex3f(4.5f, -0.8f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-4.5f, -0.8f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.5f, -2.0f, 2.5f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(4.5f, -2.0f, 2.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_STENCIL_TEST);

    /////////////////////////////////////////////////////////////////////////////////
    // Window On Upper Wall Front Side

    // Right Side
    glPushMatrix();
    glTranslatef(2.5f, -1.15f, 2.5f);
    glScalef(0.85f, 0.7f, 1.0f);
    house2_widnow1();
    glPopMatrix();

    // Left Side
    glPushMatrix();
    glTranslatef(-2.5f, -1.15f, 2.5f);
    glScalef(0.85f, 0.7f, 1.0f);
    house2_widnow1();
    glPopMatrix();

    // Middle Window
    glColor3f(0.6f, 0.6f, 0.6f);
    glBindTexture(GL_TEXTURE_2D, windowTexture3);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.5f, -1.0f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f, -1.0f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -2.0f, 2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.5f, -2.0f, 2.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glColor3f(0.9f, 0.9f, 0.9f);

    //////////////////////////////////////////////////////////////////////
    // Upper Back Side
    glClear(GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(GL_TRUE);
    glStencilFunc(GL_ALWAYS, 1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    glBegin(GL_QUADS);
    // Upper Back Area
    // door area
    glVertex3f(-0.5f, -1.0f, -2.5f);
    glVertex3f(0.5f, -1.0f, -2.5f);
    glVertex3f(0.5f, -2.0f, -2.5f);
    glVertex3f(-0.5f, -2.0f, -2.5f);

    // Left window
    glVertex3f(2.0f, -1.2f, -2.5f);
    glVertex3f(3.0f, -1.2f, -2.5f);
    glVertex3f(3.0f, -1.8f, -2.5f);
    glVertex3f(2.0f, -1.8f, -2.5f);

    // right window
    glVertex3f(-3.0f, -1.2f, -2.5f);
    glVertex3f(-2.0f, -1.2f, -2.5f);
    glVertex3f(-2.0f, -1.8f, -2.5f);
    glVertex3f(-3.0f, -1.8f, -2.5f);
    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilFunc(GL_NOTEQUAL, 1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);
    // Upper Back side
    glTexCoord2f(5.0f, 1.f);
    glVertex3f(-4.5f, -0.8f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4.5f, -0.8f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4.5f, -2.0f, -2.5f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(-4.5f, -2.0f, -2.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_STENCIL_TEST);

    /////////////////////////////////////////////////////////////////////////////////
    // Window On Upper Wall Back Side

    // Right Side
    glColor3f(0.01f, 0.01f, 0.01f);
    glPushMatrix();
    glTranslatef(2.5f, -1.15f, -2.5f);
    glScalef(0.85f, 0.7f, 1.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    house2_widnow1();
    glPopMatrix();

    // Left Side
    glPushMatrix();
    glTranslatef(-2.5f, -1.15f, -2.5f);
    glScalef(0.85f, 0.7f, 1.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    house2_widnow1();
    glPopMatrix();

    // Middle Window
    glColor3f(0.6f, 0.6f, 0.6f);
    glBindTexture(GL_TEXTURE_2D, windowTexture3);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-0.5f, -1.0f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.5f, -1.0f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.5f, -2.0f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-0.5f, -2.0f, -2.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glColor3f(0.9f, 0.9f, 0.9f);

    /////////////////////////////////////////////////////////////////////////////////
    // Upper Left Side
    glClear(GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(GL_TRUE);
    glStencilFunc(GL_ALWAYS, 1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    glBegin(GL_QUADS);
    // Upper Left Side
    // Middle window
    glVertex3f(-4.5f, -1.2f, 0.5f);
    glVertex3f(-4.5f, -1.2f, -0.5f);
    glVertex3f(-4.5f, -1.8f, -0.5f);
    glVertex3f(-4.5f, -1.8f, 0.5f);

    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilFunc(GL_NOTEQUAL, 1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);
    // Upper Back side
    glTexCoord2f(5.0f, 1.f);
    glVertex3f(-4.5f, -0.8f, 2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-4.5f, -0.8f, -2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.5f, -2.0f, -2.5f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(-4.5f, -2.0f, 2.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_STENCIL_TEST);

    /////////////////////////////////////////////////////////////////
    // Upper Left side Window
    glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, window2Texture);
    glBegin(GL_QUADS);
    // Upper Left Side
    // Middle window
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-4.5f, -1.2f, 0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-4.5f, -1.2f, -0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.5f, -1.8f, -0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-4.5f, -1.8f, 0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(0.9f, 0.9f, 0.9f);

    ////////////////////////////////////////////////////////////////////
    // Upper Right Side
    glClear(GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(GL_TRUE);
    glStencilFunc(GL_ALWAYS, 1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    glBegin(GL_QUADS);
    // Middle window
    glVertex3f(4.5f, -1.2f, -0.5f);
    glVertex3f(4.5f, -1.2f, 0.5f);
    glVertex3f(4.5f, -1.8f, 0.5f);
    glVertex3f(4.5f, -1.8f, -0.5f);
    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilFunc(GL_NOTEQUAL, 1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);
    // Upper Right side
    glTexCoord2f(5.0f, 1.f);
    glVertex3f(4.5f, -0.8f, -2.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4.5f, -0.8f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4.5f, -2.0f, 2.5f);
    glTexCoord2f(5.0f, 0.0f);
    glVertex3f(4.5f, -2.0f, -2.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_STENCIL_TEST);

    ///////////////////////////////////////////////////////////////////////////
    // Upper Right Side Window
    glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, window2Texture);
    glBegin(GL_QUADS);
    // Middle window
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(4.5f, -1.2f, -0.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4.5f, -1.2f, 0.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4.5f, -1.8f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(4.5f, -1.8f, -0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(0.9f, 0.9f, 0.9f);

    ////////////////////////////////////////////////////////////////////////
    // Upper Pillars
    glColor3f(0.5f, 0.5f, 0.5f);
    // Front Side
    glPushMatrix();
    glTranslatef(4.7f, -1.5f, 2.7f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.7f, -1.5f, 2.7f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.25f, -1.5f, 2.7f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25f, -1.5f, 2.7f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Back Side
    glPushMatrix();
    glTranslatef(4.7f, -1.5f, -2.7f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.7f, -1.5f, -2.7f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.25f, -1.5f, -2.7f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25f, -1.5f, -2.7f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Left Side
    glPushMatrix();
    glTranslatef(-4.7f, -1.5f, -1.0f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.7f, -1.5f, 1.0f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Right Side
    glPushMatrix();
    glTranslatef(4.7f, -1.5f, -1.0f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.7f, -1.5f, 1.0f);
    glScalef(0.1f, 0.6f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Supporting Pillars
    // Front Side
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 2.7f);
    glScalef(4.8f, 0.1f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Back Side
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, -2.7f);
    glScalef(4.8f, 0.1f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Left Side
    glPushMatrix();
    glTranslatef(-4.7f, -2.0f, 0.0f);
    glScalef(0.1f, 0.1f, 2.6f);
    woodenBlocks2();
    glPopMatrix();

    // Right Side
    glPushMatrix();
    glTranslatef(4.7f, -2.0f, 0.0f);
    glScalef(0.1f, 0.1f, 2.6f);
    woodenBlocks2();
    glPopMatrix();

    glColor3f(0.9f, 0.9f, 0.9f);

    ///////////////////////////////////////////////////////////////////////////////
    // Upper Area FLoors
    // Lower Side
    glColor3f(0.9f, 0.9f, 0.9f);

    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glScalef(4.7f, 0.05f, 2.6f);
    woodenBlocks2();
    glPopMatrix();

    // Upper Side
    glPushMatrix();
    glTranslatef(0.0f, -0.9f, 0.0f);
    glScalef(4.7f, 0.05f, 2.6f);
    woodenBlocks2();
    glPopMatrix();
    glColor3f(0.9f, 0.9f, 0.9f);

    ///////////////////////////////////////////////////////////////////////////////////
    // Lower Roofs

    // Roof
    glBindTexture(GL_TEXTURE_2D, roofTexture);
    glColor3f(0.7f, 0.7f, 0.7f);

    glBegin(GL_QUADS);
    // Front Side
    glTexCoord2f(0.8f, 1.4f);
    glVertex3f(4.5f, -2.0f, 2.7f);
    glTexCoord2f(0.2f, 1.4f);
    glVertex3f(-4.5f, -2.0f, 2.7f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-7.0f, -4.0f, 6.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(7.0f, -4.0f, 6.0f);

    // Back Side
    glTexCoord2f(0.8f, 1.4f);
    glVertex3f(-4.5f, -2.0f, -2.7f);
    glTexCoord2f(0.2f, 1.4f);
    glVertex3f(4.5f, -2.0f, -2.7f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(7.0f, -4.0f, -6.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-7.0f, -4.0f, -6.0f);

    // Left Side
    glTexCoord2f(0.72f, 1.4f);
    glVertex3f(-4.5f, -2.0f, 2.7f);
    glTexCoord2f(0.28f, 1.4f);
    glVertex3f(-4.5f, -2.0f, -2.7f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-7.0f, -4.0f, -6.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-7.0f, -4.0f, 6.0f);

    // Right Side
    glTexCoord2f(0.72f, 1.4f);
    glVertex3f(4.5f, -2.0f, -2.7f);
    glTexCoord2f(0.28f, 1.4f);
    glVertex3f(4.5f, -2.0f, 2.7f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(7.0f, -4.0f, 6.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(7.0f, -4.0f, -6.0f);
    glEnd();

    glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, insideRoofTexture);
    glBegin(GL_QUADS);
    // Front Side
    glTexCoord2f(0.8f, 4.4f);
    glVertex3f(4.5f, -2.0f, 2.6f);
    glTexCoord2f(0.2f, 4.4f);
    glVertex3f(-4.5f, -2.0f, 2.6f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-7.0f, -4.0f, 5.9f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(7.0f, -4.0f, 5.9f);

    // Back Side
    glTexCoord2f(0.8f, 4.4f);
    glVertex3f(-4.5f, -2.0f, -2.6f);
    glTexCoord2f(0.2f, 4.4f);
    glVertex3f(4.5f, -2.0f, -2.6f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(7.0f, -4.0f, -5.9f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-7.0f, -4.0f, -5.9f);

    // Left Side
    glTexCoord2f(0.72f, 4.4f);
    glVertex3f(-4.4f, -2.0f, 2.7f);
    glTexCoord2f(0.28f, 4.4f);
    glVertex3f(-4.4f, -2.0f, -2.7f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.9f, -4.0f, -6.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-6.9f, -4.0f, 6.0f);

    // Right Side
    glTexCoord2f(0.72f, 4.4f);
    glVertex3f(4.4f, -2.0f, -2.7f);
    glTexCoord2f(0.28f, 4.4f);
    glVertex3f(4.4f, -2.0f, 2.7f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.9f, -4.0f, 6.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(6.9f, -4.0f, -6.0f);
    glEnd();
    glColor3f(0.9f, 0.9f, 0.9f);

    //////////////////////////////////////////////////////////////////////
    // Lower side Walls

    // Lower Front Side
    glClear(GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(GL_TRUE);
    glStencilFunc(GL_ALWAYS, 1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    glBegin(GL_QUADS);
    // Lower Front Area
    //  door area
    glVertex3f(0.8f, -4.25f, 5.5f);
    glVertex3f(-0.8f, -4.25f, 5.5f);
    glVertex3f(-0.8f, -6.8f, 5.5f);
    glVertex3f(0.8f, -6.8f, 5.5f);

    // Right window
    glVertex3f(5.0f, -4.5f, 5.5f);
    glVertex3f(3.0f, -4.5f, 5.5f);
    glVertex3f(3.0f, -5.5f, 5.5f);
    glVertex3f(5.0f, -5.5f, 5.5f);

    // Left window
    glVertex3f(-3.0f, -4.5f, 5.5f);
    glVertex3f(-5.0f, -4.5f, 5.5f);
    glVertex3f(-5.0f, -5.5f, 5.5f);
    glVertex3f(-3.0f, -5.5f, 5.5f);
    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilFunc(GL_NOTEQUAL, 1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(6.0f, 4.0f);
    glVertex3f(6.5f, -3.8f, 5.5f);
    glTexCoord2f(0.0f, 4.0f);
    glVertex3f(-6.5f, -3.8f, 5.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.5f, -7.0f, 5.5f);
    glTexCoord2f(6.0f, 0.0f);
    glVertex3f(6.5f, -7.0f, 5.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_STENCIL_TEST);

    // Door On Lower Front Side
    //  door area
    /*
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 1.95f);
    glScalef(1.7f, 1.52f, 1.0f);
    house2_Door();
    glPopMatrix();
*/
    //  Windows On Lower Front Side
    //  Right Side
    glColor3f(0.01f, 0.01f, 0.01f);
    glPushMatrix();
    glTranslatef(4.0f, -4.5f, 5.5f);
    glScalef(1.65f, 1.2f, 1.0f);
    house2_widnow1();
    glPopMatrix();

    // Left Side
    glPushMatrix();
    glTranslatef(-4.0f, -4.5f, 5.5f);
    glScalef(1.65f, 1.2f, 1.0f);
    house2_widnow1();
    glPopMatrix();

    glColor3f(0.9f, 0.9f, 0.9f);

    // Ganesha On Door
    glBindTexture(GL_TEXTURE_2D, ganapatiTexture);
    glPushMatrix();
    glTranslatef(0.0f, -4.1f, 5.55f);
    glScalef(0.1f, 0.1f, 1.0f);
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
    glBindTexture(GL_TEXTURE_2D, 0);

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Lower Back Side
    glClear(GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(GL_TRUE);
    glStencilFunc(GL_ALWAYS, 1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    glBegin(GL_QUADS);
    //  door area
    glVertex3f(-0.8f, -4.25f, -5.5f);
    glVertex3f(0.8f, -4.25f, -5.5f);
    glVertex3f(0.8f, -6.8f, -5.5f);
    glVertex3f(-0.8f, -6.8f, -5.5f);
    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilFunc(GL_NOTEQUAL, 1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(6.0f, 4.f);
    glVertex3f(-6.5f, -3.8f, -5.5f);
    glTexCoord2f(0.0f, 4.0f);
    glVertex3f(6.5f, -3.8f, -5.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.5f, -7.0f, -5.5f);
    glTexCoord2f(6.0f, 0.0f);
    glVertex3f(-6.5f, -7.0f, -5.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_STENCIL_TEST);

    // Door On Lower Back Side
    //  door area
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, -1.95f);
    glScalef(1.7f, 1.52f, 1.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    house2_Door();
    glPopMatrix();

    //////////////////////////////////////////////////////////////////////////////////////
    // Lower Left Side
    glClear(GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(GL_TRUE);
    glStencilFunc(GL_ALWAYS, 1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    // Window
    glBegin(GL_QUADS);
    glVertex3f(-6.5f, -4.5f, 5.0f);
    glVertex3f(-6.5f, -4.5f, 3.0f);
    glVertex3f(-6.5f, -5.5f, 3.0f);
    glVertex3f(-6.5f, -5.5f, 5.0f);

    glVertex3f(-6.5f, -4.5f, -4.0f);
    glVertex3f(-6.5f, -4.5f, -3.0f);
    glVertex3f(-6.5f, -5.5f, -3.0f);
    glVertex3f(-6.5f, -5.5f, -4.0f);

    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilFunc(GL_NOTEQUAL, 1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glColor3f(0.9f, 0.9f, 0.9f);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(6.0f, 4.f);
    glVertex3f(-6.5f, -3.8f, 5.5f);
    glTexCoord2f(0.0f, 4.0f);
    glVertex3f(-6.5f, -3.8f, -5.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.5f, -7.0f, -5.5f);
    glTexCoord2f(6.0f, 0.0f);
    glVertex3f(-6.5f, -7.0f, 5.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_STENCIL_TEST);

    // Lower Left Window
    //  Window
    glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, window2Texture);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-6.5f, -4.5f, 5.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-6.5f, -4.5f, 3.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.5f, -5.5f, 3.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-6.5f, -5.5f, 5.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-6.5f, -4.5f, -4.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-6.5f, -4.5f, -3.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.5f, -5.5f, -3.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-6.5f, -5.5f, -4.0f);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(0.9f, 0.9f, 0.9f);

    //////////////////////////////////////////////////////////////////////////////////////
    // Lower Right Side
    glClear(GL_STENCIL_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(GL_TRUE);
    glStencilFunc(GL_ALWAYS, 1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    // window Lower Right Side
    glBegin(GL_QUADS);
    glVertex3f(6.5f, -4.5f, 3.0f);
    glVertex3f(6.5f, -4.5f, 5.0f);
    glVertex3f(6.5f, -5.5f, 5.0f);
    glVertex3f(6.5f, -5.5f, 3.0f);

    glVertex3f(6.5f, -4.5f, -4.0f);
    glVertex3f(6.5f, -4.5f, -3.0f);
    glVertex3f(6.5f, -5.5f, -3.0f);
    glVertex3f(6.5f, -5.5f, -4.0f);
    glEnd();

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
    glStencilFunc(GL_NOTEQUAL, 1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(6.0f, 4.0f);
    glVertex3f(6.5f, -3.8f, -5.5f);
    glTexCoord2f(0.0f, 4.0f);
    glVertex3f(6.5f, -3.8f, 5.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.5f, -7.0f, 5.5f);
    glTexCoord2f(6.0f, 0.0f);
    glVertex3f(6.5f, -7.0f, -5.5f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_STENCIL_TEST);

    // Lower Left Window
    //  Window
    glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, window2Texture);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(6.5f, -4.5f, 3.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(6.5f, -4.5f, 5.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.5f, -5.5f, 5.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(6.5f, -5.5f, 3.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(6.5f, -4.5f, -4.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(6.5f, -4.5f, -3.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(6.5f, -5.5f, -3.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(6.5f, -5.5f, -4.0f);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(0.9f, 0.9f, 0.9f);

    /*
        ////////////////////////////////////////////////////////
        // Floor on Lower Side
        // Upper side
        glPushMatrix();
        glTranslatef(0.0f, -4.0f, 0.0f);
        glScalef(6.5f, 0.05f, 5.5f);
        woodenBlocks2();
        glPopMatrix();
*/
    // Lower side
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glTranslatef(0.0f, -7.0f, 0.0f);
    glScalef(6.49f, 0.05f, 5.49f);
    woodenBlocks2();
    glPopMatrix();
    glColor3f(0.9f, 0.9f, 0.9f);

    //////////////////////////////// INNER HOUSE STRUCTURE ////////////////////////////////////////
    // Inside Wall in the middle
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.0f);
    // Wooden Blocks
    // Right Side
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(1.5f, -4.5f, 2.0f);
    glScalef(0.1f, 2.5f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Left Side
    glPushMatrix();
    glTranslatef(-1.5f, -4.5f, 2.0f);
    glScalef(0.1f, 2.5f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Upper
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 2.0f);
    glScalef(4.5f, 0.1f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Rotated Right Side
    glPushMatrix();
    glTranslatef(5.25f, -2.8f, 2.0f);
    glRotatef(51.5f, 0.0f, 0.0f, 1.0f);
    glScalef(0.1f, 1.2f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Rotated Left Side
    glPushMatrix();
    glTranslatef(-5.25f, -2.8f, 2.0f);
    glRotatef(-51.5f, 0.0f, 0.0f, 1.0f);
    glScalef(0.1f, 1.2f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Middle Wall
    glColor3f(0.9f, 0.9f, 0.9f);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);
    // right Side
    glTexCoord2f(3.0f, 2.0f);
    glVertex3f(6.49f, -5.0f, 2.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(1.5f, -5.0f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.5f, -7.0f, 2.0f);
    glTexCoord2f(3.0f, 0.0f);
    glVertex3f(6.49f, -7.0f, 2.0f);

    // Left Side
    glTexCoord2f(3.0f, 2.0f);
    glVertex3f(-1.5f, -5.0f, 2.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-6.49f, -5.0f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.49f, -7.0f, 2.0f);
    glTexCoord2f(3.0f, 0.0f);
    glVertex3f(-1.5f, -7.0f, 2.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

    // window On Walls
    glColor3f(0.5f, 0.5f, 0.5f);
    glBindTexture(GL_TEXTURE_2D, innerWindowDesignTexture);
    glBegin(GL_QUADS);
    // right Side
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(6.49f, -3.55f, 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.5f, -3.55f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.5f, -5.0f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(6.49f, -5.0f, 2.0f);

    // Left Side
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.5f, -3.55f, 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-6.49f, -3.55f, 2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.49f, -5.0f, 2.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.5f, -5.0f, 2.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(1.0f, 1.0f, 1.0f);

    glPopMatrix();

    ///////////////////////////////////////////////////////////////////////////////////////
    // Chairs in the house
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(-3.0f, -6.7f, 1.3f);
    glScalef(0.3f, 0.25f, 0.22f);
    chair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.0f, -6.7f, 1.3f);
    glScalef(0.3f, 0.25f, 0.17f);
    chair();
    glPopMatrix();

    // Table
    glPushMatrix();
    glTranslatef(-4.0f, -6.7f, 2.3f);
    glScalef(0.3f, 0.25f, 0.17f);
    table();
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);

    //////////////////////////////////////////////////////////////////////////////////////////
    // Walls At Center Of House
    glColor3f(0.9f, 0.9f, 0.9f);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);
    // right Side
    // Front
    glTexCoord2f(3.0f, 2.0f);
    glVertex3f(6.49f, -3.6f, -1.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(1.5f, -3.6f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.5f, -7.0f, -1.0f);
    glTexCoord2f(3.0f, 0.0f);
    glVertex3f(6.49f, -7.0f, -1.0f);

    glTexCoord2f(2.5f, 2.0f);
    glVertex3f(4.49f, -2.0f, -1.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(1.5f, -2.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.5f, -3.6f, -1.0f);
    glTexCoord2f(3.0f, 0.0f);
    glVertex3f(6.49f, -3.6f, -1.0f);

    // SideWall
    glTexCoord2f(4.0f, 3.0f);
    glVertex3f(1.5f, -3.8f, -1.0f);
    glTexCoord2f(0.0f, 3.0f);
    glVertex3f(1.5f, -3.8f, -5.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.5f, -7.0f, -5.5f);
    glTexCoord2f(4.0f, 0.0f);
    glVertex3f(1.5f, -7.0f, -1.0f);

    glTexCoord2f(4.0f, 2.0f);
    glVertex3f(1.5f, -2.0f, -1.0f);
    glTexCoord2f(1.0f, 2.0f);
    glVertex3f(1.5f, -2.0f, -2.6f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.5f, -3.8f, -5.5f);
    glTexCoord2f(4.0f, 0.0f);
    glVertex3f(1.5f, -3.8f, -1.0f);

    // Left Side
    glTexCoord2f(3.0f, 2.0f);
    glVertex3f(-1.5f, -3.6f, -1.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-6.49f, -3.6f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-6.49f, -7.0f, -1.0f);
    glTexCoord2f(3.0f, 0.0f);
    glVertex3f(-1.5f, -7.0f, -1.0f);

    glTexCoord2f(2.5f, 2.0f);
    glVertex3f(-4.49f, -2.0f, -1.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-1.5f, -2.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.5f, -3.6f, -1.0f);
    glTexCoord2f(3.0f, 0.0f);
    glVertex3f(-6.49f, -3.6f, -1.0f);

    // SideWall
    glTexCoord2f(4.0f, 3.0f);
    glVertex3f(-1.5f, -3.8f, -1.0f);
    glTexCoord2f(0.0f, 3.0f);
    glVertex3f(-1.5f, -3.8f, -5.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.5f, -7.0f, -5.5f);
    glTexCoord2f(4.0f, 0.0f);
    glVertex3f(-1.5f, -7.0f, -1.0f);

    glTexCoord2f(4.0f, 2.0f);
    glVertex3f(-1.5f, -2.0f, -1.0f);
    glTexCoord2f(1.0f, 2.0f);
    glVertex3f(-1.5f, -2.0f, -2.6f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.5f, -3.8f, -5.5f);
    glTexCoord2f(4.0f, 0.0f);
    glVertex3f(-1.5f, -3.8f, -1.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Door on Right Room
    glPushMatrix();
    glTranslatef(2.8f, -1.0f, -4.55f);
    glScalef(1.7f, 1.52f, 1.0f);
    house2_Door();
    glPopMatrix();

    // Door on Left Room
    glPushMatrix();
    glTranslatef(-5.0f, -1.0f, -2.55f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.7f, 1.52f, 1.0f);
    house2_Door();
    glPopMatrix();

    // Upper Side Floor
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glTranslatef(0.0f, -3.0f, 0.0f);
    glScalef(5.5f, 0.05f, 4.25f);
    woodenBlocks2();
    glPopMatrix();
    glColor3f(0.9f, 0.9f, 0.9f);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // Jhopala
    /*
        glPushMatrix();
        glTranslatef(3.25f, -6.0f, 2.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glScalef(0.38f, 0.8f, 1.0f);
        jhopala();
        glPopMatrix();
    */
    /////////////////////////////////////////////////////////////////////////////////////////////
    // OutSide Compound Wall

    void sideWall(void);

    // Front Side Wall
    glPushMatrix();
    glTranslatef(5.3f, -5.5f, 9.5f);
    sideWall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.3f, -5.5f, 9.5f);
    sideWall();
    glPopMatrix();

    // Back Side Wall
    glPushMatrix();
    glTranslatef(5.3f, -5.5f, -9.5f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    sideWall();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5.3f, -5.5f, -9.5f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    sideWall();
    glPopMatrix();

    // Left Side Wall
    glPushMatrix();
    glTranslatef(-9.5f, -5.5f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(2.7f, 1.0f, 1.0f);
    sideWall();
    glPopMatrix();

    // Left Side Wall
    glPushMatrix();
    glTranslatef(9.0f, -5.5f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(2.7f, 1.0f, 1.0f);
    sideWall();
    glPopMatrix();

    //////////////////////////////////////////////////////////////////////////////////////////////
    // OutSide Front Portion Area

    // Rangoli In front of Door
    glBindTexture(GL_TEXTURE_2D, rangoliTexture);
    glPushMatrix();

    glTranslatef(0.0f, -6.95f, 7.5f);
    glScalef(1.0f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    //  Wooden Structure
    glColor3f(0.6f, 0.6f, 0.6f);
    // Right
    glPushMatrix();
    glTranslatef(2.0f, -5.5f, 7.5f);
    glScalef(0.1f, 2.0f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Left
    glPushMatrix();
    glTranslatef(-2.0f, -5.5f, 7.5f);
    glScalef(0.1f, 2.0f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Top Right
    glPushMatrix();
    glTranslatef(2.0f, -3.5f, 6.5f);
    glScalef(0.1f, 0.1f, 1.1f);
    woodenBlocks2();
    glPopMatrix();

    // Top Left
    glPushMatrix();
    glTranslatef(-2.0f, -3.5f, 6.5f);
    glScalef(0.1f, 0.1f, 1.1f);
    woodenBlocks2();
    glPopMatrix();

    // Top Middle
    //  Top Right
    glPushMatrix();
    glTranslatef(0.0f, -3.5f, 7.5f);
    glScalef(2.0f, 0.1f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Top Middle
    glPushMatrix();
    glTranslatef(0.0f, -2.8f, 7.5f);
    glScalef(0.1f, 0.78f, 0.1f);
    woodenBlocks2();
    glPopMatrix();

    // Roof Structure
    glBindTexture(GL_TEXTURE_2D, roofTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, -2.0f, 2.7f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, -2.0f, 8.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(3.0f, -4.0f, 8.0f);
    glTexCoord2f(0.36f, 0.0f);
    glVertex3f(3.0f, -4.0f, 6.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.0f, -2.0f, 2.7f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, -2.0f, 8.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-3.0f, -4.0f, 8.0f);
    glTexCoord2f(0.36f, 0.0f);
    glVertex3f(-3.0f, -4.0f, 6.0f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(0.9f, 0.9f, 0.9f);

    //////////////////////////////////////////////////////////////////////////////////////////////
    // Outside Back Portion
    // Roof - Patra
    glBindTexture(GL_TEXTURE_2D, patraTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(-4.7f, -4.1f, -5.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(4.7f, -4.1f, -5.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4.7f, -5.0f, -8.8f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(-4.7f, -5.0f, -8.8f);
    glEnd();

    // Walls
    // Right
    glColor3f(0.9f, 0.9f, 0.9f);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(-4.5f, -4.1f, -5.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-4.5f, -5.0f, -8.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-4.5f, -7.0f, -8.5f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(-4.5f, -7.0f, -5.5f);

    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(4.5f, -5.0f, -8.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(4.5f, -4.1f, -5.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4.5f, -7.0f, -5.5f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(4.5f, -7.0f, -8.5f);

    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(-4.5f, -5.0f, -8.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(-0.7f, -5.0f, -8.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.7f, -7.0f, -8.5f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(-4.5f, -7.0f, -8.5f);

    glTexCoord2f(2.0f, 2.0f);
    glVertex3f(0.7f, -5.0f, -8.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(4.5f, -5.0f, -8.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4.5f, -7.0f, -8.5f);
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(0.7f, -7.0f, -8.5f);

    glEnd();

    glPushMatrix();
    glTranslatef(0.0f, -2.55f, -12.1f);
    glScalef(1.5f, 1.15f, 1.0f);
    house2_Door();
    glPopMatrix();

    // Floor on Back side
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f);
    glTranslatef(0.0f, -7.0f, -7.00f);
    glScalef(4.48f, 0.05f, 1.48f);
    woodenBlocks2();
    glPopMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void sideWall(void)
{
    glColor3f(0.6f, 0.6f, 0.6f);
    glBindTexture(GL_TEXTURE_2D, sideWallTexture);
    glPushMatrix();
    glTranslatef(-5.3f, 5.5f, -9.5f);

    glBegin(GL_QUADS);
    // Left Side Front Wall
    // Front side
    glTexCoord2f(4.0f, 2.0f);
    glVertex3f(9.0f, -5.5f, 10.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(1.5f, -5.5f, 10.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.5f, -8.0f, 10.0f);
    glTexCoord2f(4.0f, 0.0f);
    glVertex3f(9.0f, -8.0f, 10.0f);

    // Back side of front wall
    glTexCoord2f(4.0f, 2.0f);
    glVertex3f(1.5f, -5.5f, 9.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(9.0f, -5.5f, 9.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(9.0f, -8.0f, 9.5f);
    glTexCoord2f(4.0f, 0.0f);
    glVertex3f(1.5f, -8.0f, 9.5f);

    // Top side
    glTexCoord2f(4.0f, 0.3f);
    glVertex3f(9.0f, -5.5f, 9.5f);
    glTexCoord2f(0.0f, 0.3f);
    glVertex3f(1.5f, -5.5f, 9.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.5f, -5.5f, 10.0f);
    glTexCoord2f(4.0f, 0.0f);
    glVertex3f(9.0f, -5.5f, 10.0f);

    // Left Side
    glTexCoord2f(0.3f, 2.0f);
    glVertex3f(1.5f, -5.5f, 10.0f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(1.5f, -5.5f, 9.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.5f, -8.0f, 9.5f);
    glTexCoord2f(0.3f, 0.0f);
    glVertex3f(1.5f, -8.0f, 10.0f);

    // right Side
    glTexCoord2f(0.3f, 2.0f);
    glVertex3f(9.0f, -5.5f, 9.5f);
    glTexCoord2f(0.0f, 2.0f);
    glVertex3f(9.0f, -5.5f, 10.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(9.0f, -8.0f, 10.0f);
    glTexCoord2f(0.3f, 0.0f);
    glVertex3f(9.0f, -8.0f, 9.5f);

    /*
        glTexCoord2f(4.0f, 2.0f);
        glVertex3f(-1.5f, -5.5f, 10.0f);
        glTexCoord2f(0.0f, 2.0f);
        glVertex3f(-9.0f, -5.5f, 10.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-9.0f, -8.0f, 10.0f);
        glTexCoord2f(4.0f, 0.0f);
        glVertex3f(-1.5f, -8.0f, 10.0f);
    */
    glEnd();

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    glColor3f(1.0f, 1.0f, 1.0f);
}

void jhopala(void)
{
    static GLfloat fAngle = 0.0f;
    static int flag = 2;

    if (jhopala_move == 1)
    {
        flag = 0;
        jhopala_move = 0;
    }

    if (flag == 0)
    {
        fAngle += 2.0f * d_time;
        if (fAngle > 5.0f)
            flag = 1;
    }
    else if (flag == 1)
    {
        fAngle -= 2.0f * d_time;
        if (fAngle < -5.0f)
            flag = 0;
    }

    glPushMatrix();
    glTranslatef(0.0f, 4.5f, 0.0f);
    glRotatef(fAngle, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, -4.5f, 0.0f);
    glColor3f(0.9f, 0.9f, 0.9f);

    glBindTexture(GL_TEXTURE_2D, windowTexture);
    glPushMatrix();
    glScalef(2.0f, 0.05f, 1.0f);
    cube();
    glPopMatrix();

    glColor3f(0.4f, 0.4f, 0.4f);
    glPushMatrix();
    glTranslatef(1.8f, 0.0f, 0.8f);
    glScalef(1.0f, 2.0f, 1.0f);
    gluSphere(quadric, 0.1f, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8f, 0.0f, 0.8f);
    glScalef(1.0f, 2.0f, 1.0f);
    gluSphere(quadric, 0.1f, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8f, 0.0f, -0.8f);
    glScalef(1.0f, 2.0f, 1.0f);
    gluSphere(quadric, 0.1f, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8f, 0.0f, -0.8f);
    glScalef(1.0f, 2.0f, 1.0f);
    gluSphere(quadric, 0.1f, 20, 20);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    glColor3f(1.0f, 1.0f, 1.0f);

    // Chains
    glBindTexture(GL_TEXTURE_2D, chainTexture);
    glPushMatrix();
    glTranslatef(1.8f, 2.5f, 0.4f);
    glRotatef(-10.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 3.0f);
    glVertex2f(0.06f, 2.5f);
    glTexCoord2f(0.0f, 3.0f);
    glVertex2f(-0.06f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.06f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.06f, -2.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.8f, 2.5f, -0.4f);
    glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 3.0f);
    glVertex2f(0.06f, 2.5f);
    glTexCoord2f(0.0f, 3.0f);
    glVertex2f(-0.06f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.06f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.06f, -2.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8f, 2.5f, 0.4f);
    glRotatef(-10.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 3.0f);
    glVertex2f(0.06f, 2.5f);
    glTexCoord2f(0.0f, 3.0f);
    glVertex2f(-0.06f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.06f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.06f, -2.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.8f, 2.5f, -0.4f);
    glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 3.0f);
    glVertex2f(0.06f, 2.5f);
    glTexCoord2f(0.0f, 3.0f);
    glVertex2f(-0.06f, 2.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.06f, -2.5f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.06f, -2.5f);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
}

void woodenBlocks2(void)
{
    glBindTexture(GL_TEXTURE_2D, windowTexture);
    glPushMatrix();
    // glScalef(2.0f, 0.1f, 0.1f);
    cube();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}
void house2_widnow1(void)
{
    glBindTexture(GL_TEXTURE_2D, windowTexture);
    glColor3f(0.5f, 0.5f, 0.5f);
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
    /*
        glColor3f(0.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -0.41f, 0.01f);
        glScalef(0.5f, 0.45f, 1.0f);
        glBegin(GL_QUADS);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glEnd();
        */
    glColor3f(1.0f, 1.0f, 1.0f);
}

void house2_widnow2(void)
{
    glBindTexture(GL_TEXTURE_2D, windowTexture2);
    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glScalef(0.8f, 0.4f, 1.0f);
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
    glColor3f(1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void house2_Door(void)
{
    static GLfloat fAngle = 0.0f;
    static int flag = 1;

    if (open_door == 1)
    {
        flag = 0;
        open_door = 0;
    }

    if (flag == 0)
    {
        fAngle += 4.0f * d_time;
        if (fAngle >= 60.0f)
            flag = 1;
    }

    if (close_door == 1)
    {
        fAngle = 0;
    }
    /*
    else
    {
        fAngle -= 1.0f * d_time;

        if (fAngle <= -45.0f)
            flag = 0;
    }*/

    glPushMatrix();

    glTranslatef(0.0f, -3.0f, 3.56f);

    glBindTexture(GL_TEXTURE_2D, windowTexture);
    glColor3f(0.9f, 0.9f, 0.9f);

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
    glColor3f(0.6f, 0.6f, 0.6f);

    glPushMatrix();
    glTranslatef(-0.48f, 0.0f, 0.0f);
    glRotatef(fAngle, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.5f, 1.0f);
    glVertex2f(0.48f, 0.82f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0.0f, 0.82f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0.0f, -0.8f);
    glTexCoord2f(0.5f, 0.0f);
    glVertex2f(0.48f, -0.8f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.48f, 0.0f, 0.0f);
    glRotatef(-fAngle, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(-0.48f, 0.82f);
    glTexCoord2f(0.5f, 1.0f);
    glVertex2f(0.0f, 0.82f);
    glTexCoord2f(0.5f, 0.0f);
    glVertex2f(0.0f, -0.8f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(-0.48f, -0.8f);
    glEnd();
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
}
