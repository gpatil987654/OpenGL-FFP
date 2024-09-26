#include "common.h"
#include "crops.h"

GLfloat r;
GLuint grassTexture;
GLuint groundTexture;
GLuint bandhTexture;
extern GLfloat eyeX, eyeY, eyeZ;
extern GLUquadric *quadric;

GLuint cropsDisplayList;
GLuint grassDisplayList;

#define NUM_GRASS_X 10
#define NUM_GRASS_Z 10

struct grassMeshLocation
{
    GLfloat x, z;
    GLfloat fAngle;

} grassMesh_1[NUM_GRASS_X * NUM_GRASS_Z];

void grass(void)
{
    // glColor3f(0.4f, 0.4f, 0.4f);
    glBindTexture(GL_TEXTURE_2D, grassTexture);

    GLfloat x, y, z, rad;
    x = eyeX;
    y = eyeY;
    z = eyeZ;

    rad = sqrt((x * x) + (y * y) + (z * z));
    GLfloat fAngle = 0.0f;

    if (x != 0)
    {
        fAngle = -(acos(x / rad) * 180.0f / M_PI - 90.0f);
    }
    glColor3f(0.7, 1.0, 0.7);
    glPushMatrix();
    glRotatef(fAngle, 0.0f, 1.0f, 0.0f);

    // glRasterPos2f(-45.0f, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.8f, 0.6f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.2f + r, 2.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.2f + r, 2.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.2f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.2f, -1.0f);
    glEnd();

    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.8f, 0.6f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 2.0f, r / 1.5f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 2.0f, r / 1.5f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();

    /*
        glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
        // glRotatef(-35.0f, 1.0f, 0.0f, 0.0f);

        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.8f, 0.6f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.7f, 2.2f, r / 2.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.7f, 2.2f, r / 2.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-0.7f, -1.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(0.7f, -1.0f);
        glEnd();
        glPopMatrix();

        glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
        glPushMatrix();
        //  glRotatef(25.0f, 1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.8f, 0.6f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.5f, 2.5f, r);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.5f, 2.5f, r);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-1.5f, -1.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(1.5f, -1.0f);
        glEnd();
        glPopMatrix();
    */
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void grassMesh(void)
{
    static GLfloat t = 0.0f;
    static GLfloat random, prevRandom = 0.0f;
    if (t == 0.0f)
        random = ((GLfloat)rand() / (GLfloat)RAND_MAX) * 0.3f - 0.15;

    if (t < 1.0f)
    {
        // r = lerp(prevRandom, random, t);
        t += 0.1f;
    }
    else
    {
        prevRandom = random;
        t = 0.0f;
    }

    glPushMatrix();
    glScalef(2.0f, 3.0f, 2.0f);

    for (int i = 0; i < NUM_GRASS_X * NUM_GRASS_Z; i++)
    {
        // for (int j = 0; j < NUM_GRASS_Z; j++)
        {
            glPushMatrix();
            glTranslatef(grassMesh_1[i].x, 0.0f, grassMesh_1[i].z);
            glRotatef(grassMesh_1[i].fAngle, 0.0f, 1.0f, 0.0f);
            grass();
            //  glCallList(grassDisplayList);
            glPopMatrix();
        }
    }

    glBindTexture(GL_TEXTURE_2D, groundTexture);

    for (int i = 0; i < NUM_GRASS_X * NUM_GRASS_Z; i++)
    {
        // for (int j = 0; j < NUM_GRASS_Z; j++)
        {
            glBegin(GL_QUADS);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(grassMesh_1[i].x + 2.5, -0.95f, grassMesh_1[i].z + 2.5);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(grassMesh_1[i].x - 2.5, -0.95f, grassMesh_1[i].z + 2.5);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(grassMesh_1[i].x - 2.5, -0.95f, grassMesh_1[i].z - 2.5);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(grassMesh_1[i].x + 2.5, -0.95f, grassMesh_1[i].z - 2.5);
            glEnd();
        }
    }

    glBindTexture(GL_TEXTURE_2D, bandhTexture);
    // Right Side Bandh
    glPushMatrix();
    glTranslatef(NUM_GRASS_X * 5.0f / 2.0f - 1.0f, -2.0f, -(NUM_GRASS_Z) * 5.0f / 2.0f - 4.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    gluCylinder(quadric, 2.0f, 2.0f, (NUM_GRASS_Z) * 5.5f, 50, 50);
    glPopMatrix();

    // Left side
    glPushMatrix();
    glTranslatef(-NUM_GRASS_X * 5.0f / 2.0f - 4.0f, -2.0f, -(NUM_GRASS_Z) * 5.0f / 2.0f - 4.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    gluCylinder(quadric, 2.0f, 2.0f, (NUM_GRASS_Z) * 5.5f, 50, 50);
    glPopMatrix();

    // Front side
    glPushMatrix();
    glTranslatef(-NUM_GRASS_X * 5.0f / 2.0f - 5.0f, -2.0f, (NUM_GRASS_Z) * 5.0f / 2.0f - 1.5f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    gluCylinder(quadric, 2.0f, 2.0f, (NUM_GRASS_X) * 5.0f + 5, 50, 50);
    glPopMatrix();

    // Back side
    glPushMatrix();
    glTranslatef(-NUM_GRASS_X * 5.0f / 2.0f - 5.0f, -2.0f, -(NUM_GRASS_Z) * 5.0f / 2.0f - 2.5f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    gluCylinder(quadric, 2.0f, 2.0f, (NUM_GRASS_X) * 5.0f + 5, 50, 50);
    glPopMatrix();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}

void initCrops(void)
{
    void drawCropsDisplayList(void);

    grassTexture = createTexture2D("cropsTexture/ricehd.png");
    groundTexture = createTexture2D("cropsTexture/ground2.jpg");
    bandhTexture = createTexture2D("cropsTexture/bandh2.jpg");
    int k = 0;
    for (int i = 0; i < NUM_GRASS_X; i++)
    {
        for (int j = 0; j < NUM_GRASS_Z; j++)
        {
            grassMesh_1[k].x = (float)(i - NUM_GRASS_X / 2) * 5.0f;
            grassMesh_1[k].z = (float)(j - NUM_GRASS_Z / 2) * 5.0f;
            grassMesh_1[k].fAngle = rand();
            k++;
        }
    }
    grassDisplayList = glGenLists(1);
    glNewList(grassDisplayList, GL_COMPILE);
    grass();
    glEndList();

    cropsDisplayList = glGenLists(1);

    glNewList(cropsDisplayList, GL_COMPILE);
    drawCropsDisplayList();
    glEndList();
}

void drawCropsDisplayList(void)
{
    glDisable(GL_LIGHTING);

    // glEnable(GL_ALPHA_TEST);
    // glAlphaFunc(GL_GEQUAL, 0.1f);

    // Right Side Crop fields
    glPushMatrix();
    glTranslatef(100.0f, -35.0f, 200.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100.0f, -35.0f, 350.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100.0f, -35.0f, 500.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250.0f, -35.0f, 200.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250.0f, -35.0f, 350.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250.0f, -35.0f, 500.0f);
    grassMesh();
    glPopMatrix();

    // Left Side Crop fields
    glPushMatrix();
    glTranslatef(-100.0f, -35.0f, 200.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-100.0f, -35.0f, 350.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-100.0f, -34.0f, 500.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-250.0f, -35.0f, 200.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-250.0f, -32.0f, 350.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-250.0f, -30.0f, 500.0f);
    grassMesh();
    glPopMatrix();

    ///////////////////////////////////////////////////////////////////
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 550.0f);

    // Right Side Crop fields
    glPushMatrix();
    glTranslatef(100.0f, -35.0f, 200.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100.0f, -34.0f, 350.0f);
    // grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250.0f, -35.0f, 200.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250.0f, -35.0f, 350.0f);
    // grassMesh();
    glPopMatrix();

    // Left Side Crop fields
    glPushMatrix();
    glTranslatef(-100.0f, -35.0f, 200.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-100.0f, -35.0f, 350.0f);
    // grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-250.0f, -35.0f, 200.0f);
    grassMesh();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-250.0f, -32.0f, 350.0f);
    // grassMesh();
    glPopMatrix();

    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void drawCrops(void)
{
    glCallList(cropsDisplayList);
}

void uninitCrops(void)
{
    if (cropsDisplayList)
        glDeleteLists(cropsDisplayList, 1);

    if (grassTexture)
    {
        glDeleteTextures(1, &grassTexture);
    }

    if (groundTexture)
    {
        glDeleteTextures(1, &groundTexture);
    }

    if (bandhTexture)
    {
        glDeleteTextures(1, &bandhTexture);
    }
}
