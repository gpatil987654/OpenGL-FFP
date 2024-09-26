#include "common.h"
#include "fractalMangoTree.h"
#include "graph.h"

extern GLUquadric *quadric;

GLuint treeTrunkTexture;
GLuint treeLeavesTexture;
GLuint fractalMangoTreeDisplayList;
extern GLuint mangoTreePitTexture;
GLuint cylinderDisplayList;
GLuint fractalTreeDisplayList;

extern GLuint mangoTexture;
extern int shadow;

void pitForMangoTree(GLuint texture);
void drawTree(vec3_t pos, float fAngle, float fAngle2, float r, float radius);

graph_t *g_tree = NULL;

void createFractalTreeGraph(graph_t *g, vertex_t v, vec3_t pos, float fAngle, float fAngle2, float r, float rad);
void drawFractalTreeGraph();

void initFractalMangoTree()
{
    treeTrunkTexture = createTexture2D("fractalMangoTreeTexture/treeTrunk.png");
    treeLeavesTexture = createTexture2D("fractalMangoTreeTexture/leaves.png");

    vec3_t pos = {0.0f, 0.0f, 0.0f};

    g_tree = g_create_graph();
    g_add_vertex(g_tree, 0, pos);

    createFractalTreeGraph(g_tree, 0, pos, M_PI / 2, M_PI / 2, 3.0f, 0.3f);

    cylinderDisplayList = glGenLists(1);
    glNewList(cylinderDisplayList, GL_COMPILE);
    GLUquadric *quadric1 = gluNewQuadric();
    gluQuadricTexture(quadric1, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, treeTrunkTexture);
    gluCylinder(quadric1, 1.0, 0.8, 1.0, 5, 2); // Default size and detail
    glBindTexture(GL_TEXTURE_2D, 0);
    gluDeleteQuadric(quadric1);
    glEndList();

    fractalTreeDisplayList = glGenLists(1);
    glNewList(fractalTreeDisplayList, GL_COMPILE);
    drawTree(pos, M_PI / 2, M_PI / 2, 3.0, 0.3f);
    glEndList();

    fractalMangoTreeDisplayList = glGenLists(1);
    glNewList(fractalMangoTreeDisplayList, GL_COMPILE);

    // drawTree(pos, M_PI / 2, M_PI / 2, 3.0, 0.3f);

    glEnable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(-130.0f, -50.0f, 0.0f);
    glScalef(8.0f, 8.0f, 8.0f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
    // drawFractalTreeGraph();
    // drawTree(pos, M_PI / 2, M_PI / 2, 3.0, 0.3f);
    glCallList(fractalTreeDisplayList);

    glColor4f(0.6f, 0.5f, 0.5f, 1.0f);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glScalef(2.0f, 2.0f, 2.0f);
    glTranslatef(0.0f, 0.7f, 0.0f);
    pitForMangoTree(mangoTreePitTexture);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    glPopMatrix();

    glEndList();
}

void drawFractalMangoTree(void)
{
    glCallList(fractalMangoTreeDisplayList);
}

void uninitFractalMangoTree()
{
    if (fractalMangoTreeDisplayList)
    {
        glDeleteLists(1, fractalMangoTreeDisplayList);
        fractalMangoTreeDisplayList = 0;
    }

    if (fractalTreeDisplayList)
        glDeleteLists(1, fractalTreeDisplayList);

    if (cylinderDisplayList)
        glDeleteLists(1, cylinderDisplayList);


    if (treeTrunkTexture)
        glDeleteTextures(1, &treeTrunkTexture);

    if (treeLeavesTexture)
        glDeleteTextures(1, &treeLeavesTexture);

    if (g_tree)
        g_destroy_graph(&g_tree);
}

static int ver_count = 0;

void createFractalTreeGraph(graph_t *g_tree, vertex_t v, vec3_t pos, float fAngle, float fAngle2, float r, float rad)
{

    vec3_t pos2;
    pos2.x = pos.x + r * cos(fAngle) * sin(fAngle2);
    pos2.y = pos.y + r * sin(fAngle) * sin(fAngle2);
    pos2.z = pos.z + r * cos(fAngle2);
    vertex_t v_end = ++ver_count;

    g_add_edge(g_tree, v, pos, v_end, pos2, r, fAngle, fAngle2, rad);

    if (r > 0.5)
    {
        createFractalTreeGraph(g_tree, v_end, pos2, fAngle + (M_PI / 5), fAngle2, r - 0.5f, rad - 0.045f);
        createFractalTreeGraph(g_tree, v_end, pos2, fAngle - (M_PI / 5), fAngle2, r - 0.5f, rad - 0.045f);
        createFractalTreeGraph(g_tree, v_end, pos2, fAngle, fAngle2 + M_PI / 5, r - 0.5f, rad - 0.045f);
        createFractalTreeGraph(g_tree, v_end, pos2, fAngle, fAngle2 - M_PI / 5, r - 0.5f, rad - 0.045f);

        //  drawTree(pos2, fAngle + (M_PI / 6), fAngle2, r - 0.5, radius - 0.045f);
        // drawTree(pos2, fAngle - (M_PI / 6), fAngle2, r - 0.5, radius - 0.045f);

        // drawTree(pos2, fAngle + (M_PI / 6), fAngle2 + M_PI / 4, r - 0.5, radius - 0.045f);
        // drawTree(pos2, fAngle - (M_PI / 6), fAngle2 - M_PI / 4, r - 0.5, radius - 0.045f);
    }
}

void drawFractalTreeGraph()
{

    vnode_t *pv_run = NULL;
    hnode_t *ph_run = NULL;

    int flag = 0;

    for (pv_run = g_tree->pv_list->next; pv_run != g_tree->pv_list; pv_run = pv_run->next)
    {
        for (ph_run = pv_run->ph_list->next; ph_run != pv_run->ph_list; ph_run = ph_run->next)
        {

            float xlen = ph_run->pos.x - pv_run->pos.x;
            float ylen = ph_run->pos.y - pv_run->pos.y;
            float zlen = ph_run->pos.z - pv_run->pos.z;

            float height = sqrt(xlen * xlen + ylen * ylen + zlen * zlen);

            glBindTexture(GL_TEXTURE_2D, treeTrunkTexture);
            glPushMatrix();
            glTranslatef(pv_run->pos.x, pv_run->pos.y, pv_run->pos.z);
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
            glRotatef(ph_run->fAngle1 * 180.0f / M_PI, 0.0f, 0.0f, 1.0f);
            glRotatef(ph_run->fAngle2 * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadric, ph_run->rad, ph_run->rad - 0.045f, height, 5, 5);
            glPopMatrix();
            glBindTexture(GL_TEXTURE_2D, 0);

            if (ph_run->height <= 1.0)
            {

                // Flowers
                glBindTexture(GL_TEXTURE_2D, treeLeavesTexture);
                glPushMatrix();
                glTranslatef(ph_run->pos.x, ph_run->pos.y, ph_run->pos.z);
                glRotatef(ph_run->fAngle1 * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
                glRotatef(ph_run->fAngle2 * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
                // glColor3f(1.0f, 1.0f, 1.0f);
                glBegin(GL_QUADS);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(0.5f, 0.5f);
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f(-0.5f, 0.5f);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(-0.5f, -0.5f);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(0.5f, -0.5f);
                glEnd();
                glPopMatrix();
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }
    }
}

/*
void drawTree(vec3_t pos, float fAngle, float fAngle2, float r, float radius)
{

    vec3_t pos2;
    static int flag = 0;
    pos2.x = pos.x + r * cos(fAngle) * sin(fAngle2);
    pos2.y = pos.y + r * sin(fAngle) * sin(fAngle2);
    pos2.z = pos.z + r * cos(fAngle2);

    float xlen = pos2.x - pos.x;
    float ylen = pos2.y - pos.y;
    float zlen = pos2.z - pos.z;

    float height = sqrt(xlen * xlen + ylen * ylen + zlen * zlen);

    glBindTexture(GL_TEXTURE_2D, treeTrunkTexture);
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(fAngle * 180.0f / M_PI, 0.0f, 0.0f, 1.0f);
    glRotatef(fAngle2 * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadric, radius, radius - 0.045f, height, 5, 5);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    if (r > 0.5)
    {
        //  drawTree(pos2, fAngle + (M_PI / 6), fAngle2, r - 0.5, radius - 0.045f);
        // drawTree(pos2, fAngle - (M_PI / 6), fAngle2, r - 0.5, radius - 0.045f);

        // drawTree(pos2, fAngle + (M_PI / 6), fAngle2 + M_PI / 4, r - 0.5, radius - 0.045f);
        // drawTree(pos2, fAngle - (M_PI / 6), fAngle2 - M_PI / 4, r - 0.5, radius - 0.045f);

        drawTree(pos2, fAngle + (M_PI / 5), fAngle2, r - 0.5, radius - 0.045f);
        drawTree(pos2, fAngle - (M_PI / 5), fAngle2, r - 0.5, radius - 0.045f);

        drawTree(pos2, fAngle, fAngle2 + M_PI / 5, r - 0.5, radius - 0.045f);
        drawTree(pos2, fAngle, fAngle2 - M_PI / 5, r - 0.5, radius - 0.045f);

        // drawTree(pos, M_PI / 2 + M_PI / 6, M_PI / 2 + M_PI / 6, r - 1, 1, 1);
        // drawTree(pos, M_PI / 2 - M_PI / 6, M_PI / 2 + M_PI / 6, r - 1, 1, 1);
        // drawTree(pos, M_PI / 2, M_PI / 2 - M_PI / 6, r - 1, 1, 1);
    }
    if (r <= 0.5 && flag == 0)
    {
        // Flowers
        glBindTexture(GL_TEXTURE_2D, treeLeavesTexture);
        glPushMatrix();
        glTranslatef(pos2.x, pos2.y, pos2.z);
        glRotatef(fAngle * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(fAngle2 * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
        // glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(0.5f, 0.5f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-0.5f, 0.5f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        glPopMatrix();
    }
}
*/

void drawTree(vec3_t pos, float fAngle, float fAngle2, float r, float radius)
{

    vec3_t pos2;
    static int flag = 0;
    pos2.x = pos.x + r * cos(fAngle) * sin(fAngle2);
    pos2.y = pos.y + r * sin(fAngle) * sin(fAngle2);
    pos2.z = pos.z + r * cos(fAngle2);

    float xlen = pos2.x - pos.x;
    float ylen = pos2.y - pos.y;
    float zlen = pos2.z - pos.z;

    float height = sqrt(xlen * xlen + ylen * ylen + zlen * zlen);

    glBindTexture(GL_TEXTURE_2D, treeTrunkTexture);
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(fAngle * 180.0f / M_PI, 0.0f, 0.0f, 1.0f);
    glRotatef(fAngle2 * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
    //   gluCylinder(quadric, radius, radius - 0.045f, height, 5, 5);
    glScalef(radius, radius, height);
    glCallList(cylinderDisplayList);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

    if (r > 0.5)
    {
        //  drawTree(pos2, fAngle + (M_PI / 6), fAngle2, r - 0.5, radius - 0.045f);
        // drawTree(pos2, fAngle - (M_PI / 6), fAngle2, r - 0.5, radius - 0.045f);

        // drawTree(pos2, fAngle + (M_PI / 6), fAngle2 + M_PI / 4, r - 0.5, radius - 0.045f);
        // drawTree(pos2, fAngle - (M_PI / 6), fAngle2 - M_PI / 4, r - 0.5, radius - 0.045f);

        drawTree(pos2, fAngle + (M_PI / 5), fAngle2, r - 0.5, radius - 0.045f);
        drawTree(pos2, fAngle - (M_PI / 5), fAngle2, r - 0.5, radius - 0.045f);

        drawTree(pos2, fAngle, fAngle2 + M_PI / 5, r - 0.5, radius - 0.045f);
        drawTree(pos2, fAngle, fAngle2 - M_PI / 5, r - 0.5, radius - 0.045f);

        // drawTree(pos2, fAngle, fAngle2 + (M_PI / 5), r - 0.5, radius - 0.045f);
        // drawTree(pos2, fAngle - (M_PI / 4), fAngle2 - (M_PI / 5), r - 0.5, radius - 0.045f);
        // drawTree(pos2, fAngle + M_PI / 4, fAngle2 - M_PI / 5, r - 0.5, radius - 0.045f);

        // drawTree(pos, M_PI / 2 + M_PI / 6, M_PI / 2 + M_PI / 6, r - 1, 1, 1);
        // drawTree(pos, M_PI / 2 - M_PI / 6, M_PI / 2 + M_PI / 6, r - 1, 1, 1);
        // drawTree(pos, M_PI / 2, M_PI / 2 - M_PI / 6, r - 1, 1, 1);
    }

    if (r <= 0.5)
    {
        // Flowers
        glBindTexture(GL_TEXTURE_2D, treeLeavesTexture);
        glPushMatrix();
        glTranslatef(pos2.x, pos2.y, pos2.z);
        glRotatef(fAngle * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(fAngle2 * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
        // glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(0.5f, 0.5f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-0.5f, 0.5f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        glPopMatrix();
    }
}
