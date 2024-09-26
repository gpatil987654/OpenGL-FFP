#include "common.h"
#include "flowerPlants.h"
#include "graph.h"

GLuint leafTexture;
GLuint juiflowerTexture;
GLuint shevantileafTexture;
GLuint shevantiflowerTexture;
GLuint potTexture;

extern GLuint groundTexture;

graph_t *g = NULL;
GLuint juiDisplayList;
GLuint shevantiDisplayList;

void initFlowerPlants()
{
    // leafTexture = createTexture2D("flowerPlantsTexture/leaf.png");
    juiflowerTexture = createTexture2D("flowerPlantsTexture/juiflower.png");
    shevantiflowerTexture = createTexture2D("flowerPlantsTexture/shevantiflower.png");
    // shevantileafTexture = createTexture2D("flowerPlantsTexture/shevantileaf.png");
    potTexture = createTexture2D("flowerPlantsTexture/pot.png");

    void createTreeGraph(graph_t * g, vertex_t v, vec3_t pos, float fAngle, float fAngle2, float r, float rad);
    void drawTreeGraph(GLuint flowerTexture, GLuint leafTexture);

    g = g_create_graph();

    vec3_t pos = {0, 0, 0};
    g_add_vertex(g, 0, pos);

    createTreeGraph(g, 0, pos, M_PI / 2 + M_PI / 6, M_PI / 2, 5, 0.0f);
    createTreeGraph(g, 0, pos, M_PI / 2 - M_PI / 6, M_PI / 2, 5, 0.0f);
    createTreeGraph(g, 0, pos, M_PI / 2, M_PI / 2, 5, 0.0f);

    juiDisplayList = glGenLists(1);
    shevantiDisplayList = glGenLists(1);

    glNewList(juiDisplayList, GL_COMPILE);
    drawTreeGraph(juiflowerTexture, leafTexture);
    glEndList();

    glNewList(shevantiDisplayList, GL_COMPILE);
    drawTreeGraph(shevantiflowerTexture, shevantileafTexture);
    glEndList();

    g_destroy_graph(&g);

    /*
 void juiTree();
 void shevantiTree();

 juiDisplayList = glGenLists(1);
 shevantiDisplayList = glGenLists(1);

 glNewList(juiDisplayList, GL_COMPILE);
 //  drawTreeGraph(juiflowerTexture, leafTexture);
 juiTree();
 glEndList();

 glNewList(shevantiDisplayList, GL_COMPILE);
 // drawTreeGraph(shevantiflowerTexture, shevantileafTexture);
 shevantiTree();
 glEndList();
 */
}

void juiTree()
{
    glCallList(juiDisplayList);
}

void shevantiTree()
{
    glCallList(shevantiDisplayList);
}

void pot(void)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, potTexture);

    glPushMatrix();
    glTranslatef(0.0f, -1.0f, 0.0f);
    glScalef(3.0f, 4.0f, 3.0f);
    cube();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
}
void drawFlowerPlants()
{
    glDisable(GL_LIGHTING);

    void juiTree();
    void shevantiTree();

    glPushMatrix();
    glTranslatef(-22.0f, -38.0f, 100.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    // shevantiTree();
    glCallList(shevantiDisplayList);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(22.0f, -38.0f, 100.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    //  juiTree();
    glCallList(juiDisplayList);
    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void uninitFlowerPlants()
{
    if (juiDisplayList)
        glDeleteLists(juiDisplayList, 1);

    if (shevantiDisplayList)
        glDeleteLists(shevantiDisplayList, 1);

    if (g)
    {
        if (g_destroy_graph(&g) == SUCCESS)
        {
            // MessageBox(NULL, TEXT("SUCCESS"), TEXT("SUCCESS"), MB_OK);
        }
    }
    if (leafTexture)
        glDeleteTextures(1, &leafTexture);

    if (juiflowerTexture)
        glDeleteTextures(1, &juiflowerTexture);

    if (shevantiflowerTexture)
        glDeleteTextures(1, &shevantiflowerTexture);

    if (shevantileafTexture)
        glDeleteTextures(1, &shevantileafTexture);

    if (potTexture)
        glDeleteTextures(1, &potTexture);
}

void drawTreeGraph(GLuint flowerTexture, GLuint leafTexture)
{
    vnode_t *pv_run = NULL;
    hnode_t *ph_run = NULL;

    int flag = 0;

    for (pv_run = g->pv_list->next; pv_run != g->pv_list; pv_run = pv_run->next)
    {
        for (ph_run = pv_run->ph_list->next; ph_run != pv_run->ph_list; ph_run = ph_run->next)
        {
            glLineWidth(5.0f);
            glColor3f(0.0f, 0.3f, 0.0f);
            glBegin(GL_LINES);
            glVertex3f(pv_run->pos.x, pv_run->pos.y, pv_run->pos.z);
            glVertex3f(ph_run->pos.x, ph_run->pos.y, ph_run->pos.z);
            glEnd();
            glLineWidth(1.0f);

            if (ph_run->height == 0)
            {

                if (flag == 1)
                {
                    // Flowers
                    glBindTexture(GL_TEXTURE_2D, flowerTexture);
                    glPushMatrix();
                    glTranslatef(ph_run->pos.x, ph_run->pos.y, ph_run->pos.z);
                    glRotatef(ph_run->fAngle1 * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
                    glRotatef(ph_run->fAngle2 * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
                    glColor3f(1.0f, 1.0f, 1.0f);
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
                if (flag == 0)
                    flag = 1;
                else if (flag == 1)
                    flag = 2;
                else if (flag == 2)
                    flag = 3;
                else if (flag == 3)
                    flag = 0;
            }
            /*
            else if (ph_run->height < 5 && flag == 1)
            {
                float m1, m2, delT;
                float dx, dy, dz, alpha;
                dx = ph_run->pos.x - pv_run->pos.x;
                dy = ph_run->pos.y - pv_run->pos.y;
                dz = ph_run->pos.z - pv_run->pos.z;

                glBindTexture(GL_TEXTURE_2D, leafTexture);

                for (int i = 0; i < ph_run->height - 2; i++)
                {
                    alpha = (float)i / ph_run->height;

                    glPushMatrix();
                    glTranslatef(i % 2 ? -0.25f : 0.25f, 0.0f, 0.0f);
                    glTranslatef(pv_run->pos.x + alpha * dx, pv_run->pos.y + alpha * dy, pv_run->pos.z + alpha * dz);
                    glRotatef(ph_run->fAngle1 * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
                    glRotatef(ph_run->fAngle2 * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
                    glColor3f(0.0f, 1.0f, 0.0f);
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
                }
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            */
        }
    }

    glBindTexture(GL_TEXTURE_2D, groundTexture);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);
    glScalef(3.0f, 1.0f, 3.0f);
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

    glBindTexture(GL_TEXTURE_2D, potTexture);

    glColor3f(0.5f, 0.5f, 0.5f);
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glScalef(3.0f, 4.0f, 3.0f);
    cube();
    glPopMatrix();

    // Right
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(3.5f, 2.5f, 0.0f);
    glScalef(0.5f, 0.5f, 4.0f);
    cube();
    glPopMatrix();

    // Left
    glPushMatrix();
    glTranslatef(-3.5f, 2.5f, 0.0f);
    glScalef(0.5f, 0.5f, 4.0f);
    cube();
    glPopMatrix();

    // Front
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 3.5f);
    glScalef(3.5f, 0.5f, 0.5f);
    cube();
    glPopMatrix();

    // Back
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, -3.5f);
    glScalef(3.5f, 0.5f, 0.5f);
    cube();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    glColor3f(1.0f, 1.0f, 1.0f);
}

static int ver_count = 0;

void createTreeGraph(graph_t *g, vertex_t v, vec3_t pos, float fAngle, float fAngle2, float r, float rad)
{

    vec3_t pos2;
    pos2.x = pos.x + r * cos(fAngle) * sin(fAngle2);
    pos2.y = pos.y + r * sin(fAngle) * sin(fAngle2);
    pos2.z = pos.z + r * cos(fAngle2);
    vertex_t v_end = ++ver_count;

    g_add_edge(g, v, pos, v_end, pos2, r, fAngle, fAngle2, rad);

    if (r > 0)
    {
        createTreeGraph(g, v_end, pos2, fAngle + (M_PI / 6), fAngle2, r - 1, rad);
        createTreeGraph(g, v_end, pos2, fAngle - (M_PI / 6), fAngle2, r - 1, rad);
        createTreeGraph(g, v_end, pos2, fAngle + (M_PI / 6), fAngle2 + M_PI / 4, r - 1, rad);
        createTreeGraph(g, v_end, pos2, fAngle - (M_PI / 6), fAngle2 - M_PI / 4, r - 1, rad);
    }
}

extern GLUquadric *quadric;

/*
void drawTree(vec3_t pos, float fAngle, float fAngle2, float r, GLuint flowerTexture, GLuint leafTexture)
{

    vec3_t pos2;
    pos2.x = pos.x + r * cos(fAngle) * sin(fAngle2);
    pos2.y = pos.y + r * sin(fAngle) * sin(fAngle2);
    pos2.z = pos.z + r * cos(fAngle2);

    glLineWidth(5.0f);
    glColor3f(0.0f, 0.3f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(pos.x, pos.y, pos.z);
    glVertex3f(pos2.x, pos2.y, pos2.z);
    glEnd();

    if (r > 0)
    {
        drawTree(pos2, fAngle + (M_PI / 6), fAngle2, r - 1, flowerTexture, leafTexture);
        drawTree(pos2, fAngle - (M_PI / 6), fAngle2, r - 1, flowerTexture, leafTexture);

        drawTree(pos2, fAngle + (M_PI / 6), fAngle2 + M_PI / 4, r - 1, flowerTexture, leafTexture);
        drawTree(pos2, fAngle - (M_PI / 6), fAngle2 - M_PI / 4, r - 1, flowerTexture, leafTexture);
    }

    if (r == 0)
    {
        // Flowers
        glBindTexture(GL_TEXTURE_2D, flowerTexture);
        glPushMatrix();
        glTranslatef(pos2.x, pos2.y, pos2.z);
        glRotatef(fAngle * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
        glRotatef(fAngle2 * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
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
    }
    else if (r < 5)
    {
        float m1, m2, delT;
        float dx, dy, dz, alpha;
        dx = pos2.x - pos.x;
        dy = pos2.y - pos.y;
        dz = pos2.z - pos.z;

        for (int i = 0; i < r; i++)
        {
            alpha = (float)i / r;

            glBindTexture(GL_TEXTURE_2D, leafTexture);
            glPushMatrix();
            glTranslatef(i % 2 ? -0.25f : 0.25f, 0.0f, 0.0f);
            glTranslatef(pos.x + alpha * dx, pos.y + alpha * dy, pos.z + alpha * dz);
            glRotatef(fAngle * 180.0f / M_PI, 1.0f, 0.0f, 0.0f);
            glRotatef(fAngle2 * 180.0f / M_PI, 0.0f, 1.0f, 0.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
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

void juiTree()
{
    vec3_t pos = {0.0f, 0.0f, 0.0f};

    drawTree(pos, M_PI / 2 + M_PI / 6, M_PI / 2, 5, juiflowerTexture, leafTexture);
    drawTree(pos, M_PI / 2 - M_PI / 6, M_PI / 2, 5, juiflowerTexture, leafTexture);
    drawTree(pos, M_PI / 2, M_PI / 2, 5, juiflowerTexture, leafTexture);
}

void shevantiTree()
{
    vec3_t pos = {0.0f, 0.0f, 0.0f};

    drawTree(pos, M_PI / 2 + M_PI / 6, M_PI / 2, 5, shevantiflowerTexture, shevantileafTexture);
    drawTree(pos, M_PI / 2 - M_PI / 6, M_PI / 2, 5, shevantiflowerTexture, shevantileafTexture);
    drawTree(pos, M_PI / 2, M_PI / 2, 5, shevantiflowerTexture, shevantileafTexture);
}
*/