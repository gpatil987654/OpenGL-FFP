#include "common.h"
#include "trees.h"

#define COCONUT_TREES_COUNT 20

int shadow = 0;
extern GLfloat eyeX, eyeY, eyeZ, centerX, centerY, centerZ;
GLuint coconutTexture;
GLuint palmTexture;
GLuint mangoTexture;
GLuint roundPitTexture;
GLuint mangoTreePitTexture;
GLuint treeTexture1;
GLuint treeTexture2;
GLuint treeTexture3;

extern GLfloat lightPosition[4];
GLfloat fRotAngle[COCONUT_TREES_COUNT];
GLfloat fTreeHeight[COCONUT_TREES_COUNT];

extern GLuint torusDisplayList;
extern GLUquadric *quadric;
extern int coconut_tree_order;

GLuint treesDisplayList;

int mangoTreeShadow = 0;

#define MAP_X 32
#define MAP_Z 32

extern float terrain[MAP_X][MAP_Z][3];

void tree(GLuint texture, int num)
{
    GLfloat x, y, z, rad;
    //  GLfloat fAngle = 0.0f;
    /*
        x = eyeX - centerX;
        y = eyeY - centerY;
        z = eyeZ - centerZ;

        rad = sqrt((x * x) + (y * y) + (z * z));
        GLfloat fAngle = 0.0f;

        if (x != 0)
        {
            fAngle = -(acos(x / rad) * 180.0f / M_PI - 90.0f);

            if (z < 0)
                fAngle = -1 * fAngle;
        }


    rad = sqrt((eyeX * eyeX) + (eyeY * eyeY) + (eyeZ * eyeZ));

    x = eyeX / rad;
    y = eyeY / rad;
    z = eyeZ / rad;

    GLfloat fAngle = acos(z) * 180.0f / M_PI;
*/
    GLfloat fAngle = 0.0f;

    // GLfloat fAngle = 0;
    if (shadow == 1)
        fAngle = 0;
    // glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glRotatef(fAngle, 0.0f, 1.0f, 0.0f);

    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(3.0f, fTreeHeight[num]);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-3.0f, fTreeHeight[num]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-3.0f, -3.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(3.0f, -3.0f);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void coconutTreeFinal(int i)
{

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, -45.0f, 0.0f);
    glScalef(20.0f, 20.0f, 20.0f);

    glPushMatrix();
    glRotatef(fRotAngle[i], 0.0f, 1.0f, 0.0f);
    tree(coconutTexture, i);
    glPushMatrix();
    glTranslatef(-0.1f, 0.0f, -0.05f);
    glRotatef(90.0f, 0.0, 1.0f, 0.0f);
    tree(coconutTexture, i);
    glPopMatrix();
    glPopMatrix();

    // Shadow
    shadow = 1;
    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);

    glPushMatrix();
    glTranslatef(0.0f, -4.62f, 5.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    tree(coconutTexture, i);
    shadow = 0;
    glPopMatrix();

    glPopMatrix();
}

void palmTreeFinal(int i)
{

    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, -45.0f, 0.0f);
    glScalef(20.0f, 20.0f, 20.0f);

    glPushMatrix();
    glRotatef(fRotAngle[i], 0.0f, 1.0f, 0.0f);
    tree(palmTexture, i);
    glPushMatrix();
    glTranslatef(-0.1f, 0.0f, -0.05f);
    glRotatef(90.0f, 0.0, 1.0f, 0.0f);
    tree(palmTexture, i);
    glPopMatrix();
    glPopMatrix();

    // Shadow
    shadow = 1;
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);

    glPushMatrix();
    glTranslatef(0.0f, -4.68f, 5.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    tree(palmTexture, i);
    shadow = 0;
    glPopMatrix();
    //   glDisable(GL_BLEND);

    glPopMatrix();
}

void mangoTreeFinal(int i)
{

    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, -45.0f, 0.0f);
    glScalef(10.0f, 14.0f, 10.0f);
    if (mangoTreeShadow == 0)
    {

        glPushMatrix();
        glRotatef(fRotAngle[i], 0.0f, 1.0f, 0.0f);
        i = 0;
        tree(mangoTexture, i);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.1f);
        glRotatef(90.0f, 0.0, 1.0f, 0.0f);
        tree(mangoTexture, i);
        glPopMatrix();
        glPopMatrix();
    }
    // Shadow
    shadow = 1;
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);

    glPushMatrix();
    glTranslatef(0.0f, -4.85f, 5.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    tree(mangoTexture, i);
    shadow = 0;
    glPopMatrix();
    //   glDisable(GL_BLEND);

    glColor4f(0.6f, 0.5f, 0.5f, 1.0f);
    void pitForMangoTree(GLuint texture);

    if (mangoTreeShadow == 0)
    {
        glTranslatef(0.0f, -4.8f, 0.0f);
        pitForMangoTree(mangoTreePitTexture);
    }
    glPopMatrix();
}

void randomTreeFinal(int i, int j)
{
    GLuint treeTexture;
    if (j == 1)
    {
        treeTexture = treeTexture1;
    }
    else if (j == 2)
    {
        treeTexture = treeTexture2;
    }
    else
    {
        treeTexture = treeTexture3;
    }

    // glColor3f(0.7f, 1.0f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, -45.0f, 0.0f);
    glScalef(20.0f, 20.0f, 20.0f);

    glPushMatrix();
    glRotatef(fRotAngle[i], 0.0f, 1.0f, 0.0f);
    tree(treeTexture, i);
    glPushMatrix();
    glTranslatef(-0.1f, 0.0f, -0.05f);
    glRotatef(90.0f, 0.0, 1.0f, 0.0f);
    tree(treeTexture, i);
    glPopMatrix();
    glPopMatrix();

    // Shadow
    /*
    shadow = 1;
    //  glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.25f);

    glPushMatrix();
    glTranslatef(0.0f, -4.62f, 5.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    tree(treeTexture, i);
    shadow = 0;
    glPopMatrix();
    //  glDisable(GL_BLEND);
*/
    glPopMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
}

void initTrees(void)
{
    void drawTreesDisplayList(void);

    roundPitTexture = createTexture2D("treesTexture/bandh2.jpg");
    coconutTexture = createTexture2D("treesTexture/coconut.png");
    palmTexture = createTexture2D("treesTexture/palm8.png");
    mangoTexture = createTexture2D("treesTexture/mango2.png");
    mangoTreePitTexture = createTexture2D("treesTexture/pit.png");

    treeTexture1 = createTexture2DTree("treesTexture/tree2.png");
    treeTexture2 = createTexture2DTree("treesTexture/tree6.png");
    treeTexture3 = createTexture2DTree("treesTexture/tree7.png");

    for (int i = 0; i < COCONUT_TREES_COUNT; i++)
    {
        fRotAngle[i] = rand() % 360;
        fTreeHeight[i] = (float)(rand() % 30) / 10.0f;

        if (fTreeHeight[i] < 1.0f)
            fTreeHeight[i] = 1.0f;
    }

    treesDisplayList = glGenLists(1);

    glNewList(treesDisplayList, GL_COMPILE);
    drawTreesDisplayList();
    glEndList();
}

void drawTrees()
{
    glPushMatrix();
    glTranslatef(0.0f, 99.0f, 0.0f);
    glCallList(treesDisplayList);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Coconut Trees in Front of House
    // glEnable(GL_ALPHA_TEST);
    // glAlphaFunc(GL_GEQUAL, 0.1f);
    glDisable(GL_LIGHTING);
    int count = 4;
    if (coconut_tree_order == 0)
    {

        glPushMatrix();

        glTranslatef(20.0f, 0.06f, 170.0f);
        coconutTreeFinal(count++);

        glTranslatef(0.0f, 0.05f, 50.0f);
        coconutTreeFinal(count++);

        glTranslatef(0.0f, 0.04f, 50.0f);
        coconutTreeFinal(count++);

        glTranslatef(0.0f, 0.03f, 50.0f);
        coconutTreeFinal(count++);

        glTranslatef(0.0f, 0.02f, 50.0f);
        coconutTreeFinal(count++);

        glTranslatef(0.0f, 0.01f, 50.0f);
        coconutTreeFinal(count++);

        glTranslatef(0.0f, 0.01f, 50.0f);
        coconutTreeFinal(count++);

        glTranslatef(0.0f, 0.01f, 50.0f);
        coconutTreeFinal(count++);

        glTranslatef(0.0f, 0.01f, 50.0f);
        coconutTreeFinal(count++);

        glPopMatrix();
    }
    else if (coconut_tree_order == 1)
    {
        glPushMatrix();

        glTranslatef(20.0f, 0.01f, 570.0f);
        coconutTreeFinal(12);

        glTranslatef(0.0f, 0.01f, -50.0f);
        coconutTreeFinal(11);

        glTranslatef(0.0f, 0.01f, -50.0f);
        coconutTreeFinal(10);

        glTranslatef(0.0f, 0.01f, -50.0f);
        coconutTreeFinal(9);

        glTranslatef(0.0f, 0.02f, -50.0f);
        coconutTreeFinal(8);

        glTranslatef(0.0f, 0.03f, -50.0f);
        coconutTreeFinal(7);

        glTranslatef(0.0f, 0.04f, -50.0f);
        coconutTreeFinal(6);

        glTranslatef(0.0f, 0.05f, -50.0f);
        coconutTreeFinal(5);

        glTranslatef(0.0f, 0.06f, -50.0f);
        coconutTreeFinal(4);

        glPopMatrix();
    }
    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void drawTreesDisplayList(void)
{
    int count = 0;

    glDisable(GL_LIGHTING);
    ////////////////////////////////////////////////////////////////////////////
    // Random Trees Surronding the area
    glColor3f(0.0f, 0.4f, 0.0f);
    count = 0;

    glPushMatrix();
    glTranslatef(-(MAP_X * 100 / 2), -40, MAP_Z * 100 / 2);
    for (int k = 0; k < MAP_X; k++)
    {
        for (int j = 0; j < MAP_Z; j++)
        {
            if (k < 5) // || k > 25)
            {
                // if (j < 8 || j > 20)
                {
                    int n = 0; // rand() % 2 - 1;
                    int m = 0; // rand() % 2 - 1;

                    glPushMatrix();
                    glTranslatef(terrain[k + n][j + m][0], terrain[k + n][j + m][1] + 40.0f, terrain[k + n][j + m][2]);
                    // randomTreeFinal(rand() % 20, rand() % 3 + 1);
                    randomTreeFinal((k * j) % 20, (k * j) % 3 + 1);
                    glPopMatrix();
                }
            }

            if (j < 5) // || j > 26)
            {
                // if (j < 8 || j > 20)
                {
                    int n = 0; // rand() % 2 - 1;
                    int m = 0; // rand() % 2 - 1;

                    glPushMatrix();
                    glTranslatef(terrain[k + n][j + m][0], terrain[k + n][j + m][1] + 40.0f, terrain[k + n][j + m][2]);
                    // randomTreeFinal(rand() % 20, rand() % 3 + 1);
                    randomTreeFinal((k * j) % 20, (k * j) % 3 + 1);
                    glPopMatrix();
                }
            }
        }
    }

    for (int k = MAP_X - 1; k >= 0; k--)
    {
        for (int j = MAP_Z - 1; j >= 0; j--)
        {
            if (k > 26)
            {
                // if (j < 8 || j > 20)
                {
                    int n = 0; // rand() % 2 - 1;
                    int m = 0; // rand() % 2 - 1;

                    glPushMatrix();
                    glTranslatef(terrain[k + n][j + m][0], terrain[k + n][j + m][1] + 40.0f, terrain[k + n][j + m][2]);
                    // randomTreeFinal(rand() % 20, rand() % 3 + 1);
                    randomTreeFinal((k * j) % 20, (k * j) % 3 + 1);
                    glPopMatrix();
                }
            }

            if (j > 26)
            {
                // if (j < 8 || j > 20)
                {
                    int n = 0; // rand() % 2 - 1;
                    int m = 0; // rand() % 2 - 1;

                    glPushMatrix();
                    glTranslatef(terrain[k + n][j + m][0], terrain[k + n][j + m][1] + 40.0f, terrain[k + n][j + m][2]);
                    // randomTreeFinal(rand() % 20, rand() % 3 + 1);
                    randomTreeFinal((k * j) % 20, (k * j) % 3 + 1);
                    glPopMatrix();
                }
            }
        }
    }

    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);

    count = 0;
    /////////////////////////////////////////////////////////////////////////////
    // Mango Trees
    // Left Side
    glPushMatrix();
    glTranslatef(-550.0f, -25.0f, 450);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-400.0f, -23.0f, 450);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-550.0f, -25.0f, 250);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-400.0f, -25.0f, 250);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    //////////////////////////////////////

    glPushMatrix();
    glTranslatef(-550.0f, -25.0f, 750);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-400.0f, -25.0f, 750);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-550.0f, -25.0f, 950);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-400.0f, -25.0f, 950);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    //////////////////////////////////////////////////////////////////////////////
    // Right Side Mango Trees
    glPushMatrix();
    glTranslatef(550.0f, -25.0f, 450);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400.0f, -25.0f, 450);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(550.0f, -25.0f, 250);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400.0f, -25.0f, 250);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    //////////////////////////////////////

    glPushMatrix();
    glTranslatef(550.0f, -25.0f, 750);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400.0f, -25.0f, 750);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(550.0f, -25.0f, 950);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400.0f, -18.0f, 950);
    glScalef(2.0f, 1.0f, 2.0f);
    mangoTreeFinal(count++);
    glPopMatrix();

    /////////////////////////////////////////////
    // Mango Trees Near House

    count = 0;
    // Left Side
    mangoTreeShadow = 1;

    glPushMatrix();
    glTranslatef(-130.0f, -25.0f, 0);
    glScalef(1.5f, 1.0f, 1.5f);
    mangoTreeFinal(count++);
    glPopMatrix();
    mangoTreeShadow = 0;
    /*
    glPushMatrix();
    glTranslatef(-130.0f, -25.0f, -100);
    glScalef(1.5f, 1.0f, 1.5f);
    mangoTreeFinal(count++);
    glPopMatrix();

        // Right Side
        glPushMatrix();
        glTranslatef(130.0f, -25.0f, -100);
        glScalef(1.5f, 1.0f, 1.5f);
        mangoTreeFinal(count++);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(130.0f, -25.0f, 0);
        glScalef(1.5f, 1.0f, 1.5f);
        mangoTreeFinal(count++);
        glPopMatrix();
    */

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Coconut Trees in Front of House
    // glEnable(GL_ALPHA_TEST);
    // glAlphaFunc(GL_GEQUAL, 0.1f);
    /*
        if (coconut_tree_order == 0)
        {

            glPushMatrix();

            glTranslatef(20.0f, 0.06f, 170.0f);
            coconutTreeFinal(count++);

            glTranslatef(0.0f, 0.05f, 50.0f);
            coconutTreeFinal(count++);

            glTranslatef(0.0f, 0.04f, 50.0f);
            coconutTreeFinal(count++);

            glTranslatef(0.0f, 0.03f, 50.0f);
            coconutTreeFinal(count++);

            glTranslatef(0.0f, 0.02f, 50.0f);
            coconutTreeFinal(count++);

            glTranslatef(0.0f, 0.01f, 50.0f);
            coconutTreeFinal(count++);

            glTranslatef(0.0f, 0.01f, 50.0f);
            coconutTreeFinal(count++);

            glTranslatef(0.0f, 0.01f, 50.0f);
            coconutTreeFinal(count++);

            glTranslatef(0.0f, 0.01f, 50.0f);
            coconutTreeFinal(count++);

            glPopMatrix();
        }
        else if (coconut_tree_order == 1)
        {
            glPushMatrix();

            glTranslatef(20.0f, 0.01f, 570.0f);
            coconutTreeFinal(12);

            glTranslatef(0.0f, 0.01f, -50.0f);
            coconutTreeFinal(11);

            glTranslatef(0.0f, 0.01f, -50.0f);
            coconutTreeFinal(10);

            glTranslatef(0.0f, 0.01f, -50.0f);
            coconutTreeFinal(9);

            glTranslatef(0.0f, 0.02f, -50.0f);
            coconutTreeFinal(8);

            glTranslatef(0.0f, 0.03f, -50.0f);
            coconutTreeFinal(7);

            glTranslatef(0.0f, 0.04f, -50.0f);
            coconutTreeFinal(6);

            glTranslatef(0.0f, 0.05f, -50.0f);
            coconutTreeFinal(5);

            glTranslatef(0.0f, 0.06f, -50.0f);
            coconutTreeFinal(4);

            glPopMatrix();
        }
    */
    count = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            glPushMatrix();
            glTranslatef(-200.0f - i * 50.0f, (i * 4 + j) * 0.005f, 100 - j * 50.0f);
            coconutTreeFinal(count++);
            glPopMatrix();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////
    // Palm Trees
    count = 19;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            glPushMatrix();
            glTranslatef(200.0f + i * 50.0f, (i * j) * 0.003f, 100 - j * 50.0f);
            palmTreeFinal(count--);
            glPopMatrix();
        }
    }

    glEnable(GL_LIGHTING);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void uninitTrees(void)
{
    if (treesDisplayList)
        glDeleteLists(treesDisplayList, 1);

    if (coconutTexture)
    {
        glDeleteTextures(1, &coconutTexture);
    }

    if (palmTexture)
    {
        glDeleteTextures(1, &palmTexture);
    }

    if (mangoTexture)
    {
        glDeleteTextures(1, &mangoTexture);
    }

    if (mangoTreePitTexture)
    {
        glDeleteTextures(1, &mangoTreePitTexture);
    }

    if (treeTexture1)
        glDeleteTextures(1, &treeTexture1);

    if (treeTexture2)
        glDeleteTextures(1, &treeTexture2);

    if (treeTexture3)
        glDeleteTextures(1, &treeTexture3);
}

void pitForMangoTree(GLuint texture)
{
    GLfloat fAngle1 = 0.0f, fAngle2 = 0.0f;
    GLfloat height = 0.5f;
    GLfloat r1 = 1.5f, r2 = 1.25f;
    GLfloat N = 15;

    glBindTexture(GL_TEXTURE_2D, texture);
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

    glScalef(0.9f, 0.9f, 1.0f);
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

    /*
    glBegin(GL_QUADS);
    for (int i = 1; i <= N; i++)
    {
        fAngle1 = 2 * M_PI * (float)i / N;
        fAngle2 = 2 * M_PI * (float)(i - 1) / N;
        float d = 1.0f / N;

        glTexCoord2f(d * i, 1.0f);
        glVertex3f(r2 * cos(fAngle2), r2 * sin(fAngle2), -height);

        glTexCoord2f(d * (i - 1), 1.0f);
        glVertex3f(r2 * cos(fAngle1), r2 * sin(fAngle1), -height);

        glTexCoord2f(d * (i - 1), 1.0f);
        glVertex3f(r2 * cos(fAngle1), r2 * sin(fAngle1), height);

        glTexCoord2f(d * i, 0.0f);
        glVertex3f(r2 * cos(fAngle2), r2 * sin(fAngle2), height);
    }

    glEnd();
    */

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
        glTexCoord2f(0.4f, 0.5f);
        glVertex3f(r2 * cos(fAngle2), r2 * sin(fAngle2), 0);
        glTexCoord2f(0.4f, 0.4f);
        glVertex3f(r1 * cos(fAngle2), r1 * sin(fAngle2), 0);
        glTexCoord2f(0.5f, 0.4f);
        glVertex3f(r1 * cos(fAngle1), r1 * sin(fAngle1), 0);
    }

    glEnd();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}
