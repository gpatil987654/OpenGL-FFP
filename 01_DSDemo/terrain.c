#include "common.h"
#include "terrain.h"

#define MAP_X 32
#define MAP_Z 32

#define MAP_SCALE 100

static unsigned char *heightMapData = NULL;

float terrain[MAP_X][MAP_Z][3];
static GLuint grassTexture;

GLuint terrainDisplayList;

static GLfloat Alpha = 1.0f;

// Call in initialise()
void initTerrain(void)
{
    void terrainDrawing(void);

    int width,
        height, channels;
    heightMapData = stbi_load("terrainTexture/heightmap11.png", &width, &height, &channels, 0);

    for (int z = 0; z < MAP_Z; z++)
    {
        for (int x = 0; x < MAP_X; x++)
        {
            GLfloat a1 = 2 * M_PI * (float)z / MAP_Z;
            GLfloat a2 = 2 * M_PI * (float)x / MAP_X;

            terrain[x][z][0] = (float)x * MAP_SCALE;
            terrain[x][z][1] = (float)heightMapData[(z * MAP_Z + x) * channels]; // 4->No of heightmap image channels
            terrain[x][z][2] = -(float)z * MAP_SCALE;
        }
    }
    grassTexture = createTexture2D("terrainTexture/grass.bmp");

    terrainDisplayList = glGenLists(1);

    glNewList(terrainDisplayList, GL_COMPILE);
    terrainDrawing();
    glEndList();
}

// Call in display()
void drawTerrain(void)
{
    glCallList(terrainDisplayList);
}

void terrainDrawing(void)
{

    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, grassTexture);
    glColor4f(1.0f, 1.0f, 1.0f, Alpha);

    GLfloat groundColor[3] = {0.812, 0.643, 0.255};
    GLfloat grassColor[3] = {0.239, 0.712, 0.204};
    GLfloat height = 100.0f;

    glPushMatrix();

    glTranslatef(-(MAP_X * MAP_SCALE / 2), -40, MAP_Z * MAP_SCALE / 2);

    for (int z = 0; z < MAP_Z - 1; z++)
    {
        glBegin(GL_TRIANGLES);
        for (int x = 0; x < MAP_X - 1; x++)
        {
            /*
            if (x == 0)
                calculateNormal(terrain[x][z][0], terrain[x][z][1], terrain[x][z][2],
                                terrain[x + 1][z][0], terrain[x + 1][z][1], terrain[x + 1][z][2],
                                terrain[x][z + 1][0], terrain[x][z + 1][1], terrain[x][z + 1][2]);

            glTexCoord2f(0.0f, 0.0f);
            glColor3f(lerp(groundColor[0], grassColor[0], terrain[x][z][1] / height), lerp(groundColor[1], grassColor[1], terrain[x][z][1] / height), lerp(groundColor[2], grassColor[2], terrain[x][z][1] / height));
            glVertex3f(terrain[x][z][0], terrain[x][z][1], terrain[x][z][2]);

            glTexCoord2f(1.0f, 0.0f);
            glColor3f(lerp(groundColor[0], grassColor[0], terrain[x + 1][z][1] / height), lerp(groundColor[1], grassColor[1], terrain[x + 1][z][1] / height), lerp(groundColor[2], grassColor[2], terrain[x + 1][z][1] / height));
            glVertex3f(terrain[x + 1][z][0], terrain[x + 1][z][1], terrain[x + 1][z][2]);

            glTexCoord2f(0.0f, 1.0f);
            glColor3f(lerp(groundColor[0], grassColor[0], terrain[x][z + 1][1] / height), lerp(groundColor[1], grassColor[1], terrain[x][z + 1][1] / height), lerp(groundColor[2], grassColor[2], terrain[x][z + 1][1] / height));
            glVertex3f(terrain[x][z + 1][0], terrain[x][z + 1][1], terrain[x][z + 1][2]);

            glTexCoord2f(1.0f, 1.0f);
            glColor3f(lerp(groundColor[0], grassColor[0], terrain[x + 1][z + 1][1] / height), lerp(groundColor[1], grassColor[1], terrain[x + 1][z + 1][1] / height), lerp(groundColor[2], grassColor[2], terrain[x + 1][z + 1][1] / height));
            glVertex3f(terrain[x + 1][z + 1][0], terrain[x + 1][z + 1][1], terrain[x + 1][z + 1][2]);


            */
            // 1
            calculateNormal(terrain[x][z][0], terrain[x][z][1], terrain[x][z][2],
                            terrain[x][z + 1][0], terrain[x][z + 1][1], terrain[x][z + 1][2],
                            terrain[x + 1][z][0], terrain[x + 1][z][1], terrain[x + 1][z][2]);

            glTexCoord2f(0.0f, 0.0f);
            glColor4f(lerp(groundColor[0], grassColor[0], terrain[x][z][1] / height), lerp(groundColor[1], grassColor[1], terrain[x][z][1] / height), lerp(groundColor[2], grassColor[2], terrain[x][z][1] / height), Alpha);
            glVertex3f(terrain[x][z][0], terrain[x][z][1], terrain[x][z][2]);

            glTexCoord2f(1.0f, 0.0f);
            glColor4f(lerp(groundColor[0], grassColor[0], terrain[x + 1][z][1] / height), lerp(groundColor[1], grassColor[1], terrain[x + 1][z][1] / height), lerp(groundColor[2], grassColor[2], terrain[x + 1][z][1] / height), Alpha);
            glVertex3f(terrain[x + 1][z][0], terrain[x + 1][z][1], terrain[x + 1][z][2]);

            glTexCoord2f(0.0f, 1.0f);
            glColor4f(lerp(groundColor[0], grassColor[0], terrain[x][z + 1][1] / height), lerp(groundColor[1], grassColor[1], terrain[x][z + 1][1] / height), lerp(groundColor[2], grassColor[2], terrain[x][z + 1][1] / height), Alpha);
            glVertex3f(terrain[x][z + 1][0], terrain[x][z + 1][1], terrain[x][z + 1][2]);

            // 2
            calculateNormal(terrain[x + 1][z + 1][0], terrain[x + 1][z + 1][1], terrain[x + 1][z + 1][2],
                            terrain[x + 1][z][0], terrain[x + 1][z][1], terrain[x + 1][z][2],
                            terrain[x][z + 1][0], terrain[x][z + 1][1], terrain[x][z + 1][2]);

            glTexCoord2f(1.0f, 1.0f);
            glColor4f(lerp(groundColor[0], grassColor[0], terrain[x + 1][z + 1][1] / height), lerp(groundColor[1], grassColor[1], terrain[x + 1][z + 1][1] / height), lerp(groundColor[2], grassColor[2], terrain[x + 1][z + 1][1] / height), Alpha);
            glVertex3f(terrain[x + 1][z + 1][0], terrain[x + 1][z + 1][1], terrain[x + 1][z + 1][2]);

            glTexCoord2f(0.0f, 1.0f);
            glColor4f(lerp(groundColor[0], grassColor[0], terrain[x][z + 1][1] / height), lerp(groundColor[1], grassColor[1], terrain[x][z + 1][1] / height), lerp(groundColor[2], grassColor[2], terrain[x][z + 1][1] / height), Alpha);
            glVertex3f(terrain[x][z + 1][0], terrain[x][z + 1][1], terrain[x][z + 1][2]);

            glTexCoord2f(1.0f, 0.0f);
            glColor4f(lerp(groundColor[0], grassColor[0], terrain[x + 1][z][1] / height), lerp(groundColor[1], grassColor[1], terrain[x + 1][z][1] / height), lerp(groundColor[2], grassColor[2], terrain[x + 1][z][1] / height), Alpha);
            glVertex3f(terrain[x + 1][z][0], terrain[x + 1][z][1], terrain[x + 1][z][2]);
        }
        glEnd();
    }
    glPopMatrix();

    glColor4f(1.0f, 1.0f, 1.0f, Alpha);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_LIGHTING);
}

// Call in uninitialise()
void uninitTerrain(void)
{
    if (terrainDisplayList)
        glDeleteLists(terrainDisplayList, 1);

    if (grassTexture)
    {
        glDeleteTextures(1, &grassTexture);
    }
}
