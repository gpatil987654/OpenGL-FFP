#include "common.h"
#include "environmentMap.h"

GLuint cubeMapTexture;

void initEnvMap(void)
{
    cubeMapTexture = createTexture2D("enviornmentMapTexture/cubemap7.png");
}

void drawEnvMap(void)
{

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);

    GLfloat size = 2000.0f;
    GLfloat height = 800;

    glPushMatrix();

    glTranslatef(0.0f, 99.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, cubeMapTexture);
    // Front
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(3.0f / 4.0f, 2.0f / 3.0f);
    glVertex3f(size, height, -size);
    glTexCoord2f(2.0f / 4.0f, 2.0f / 3.0f);
    glVertex3f(-size, height, -size);
    glTexCoord2f(2.0f / 4.0f, 1.0f / 3.0f);
    glVertex3f(-size, -height, -size);
    glTexCoord2f(3.0f / 4.0f, 1.0f / 3.0f);
    glVertex3f(size, -height, -size);

    // Right
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(4.0f / 4.0f, 2.0f / 3.0f);
    glVertex3f(size, height, size);
    glTexCoord2f(3.0f / 4.0f, 2.0f / 3.0f);
    glVertex3f(size, height, -size);
    glTexCoord2f(3.0f / 4.0f, 1.0f / 3.0f);
    glVertex3f(size, -height, -size);
    glTexCoord2f(4.0f / 4.0f, 1.0f / 3.0f);
    glVertex3f(size, -height, size);

    // Left
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(2.0f / 4.0f, 2.0f / 3.0f);
    glVertex3f(-size, height, -size);
    glTexCoord2f(1.0f / 4.0f, 2.0f / 3.0f);
    glVertex3f(-size, height, size);
    glTexCoord2f(1.0f / 4.0f, 1.0f / 3.0f);
    glVertex3f(-size, -height, size);
    glTexCoord2f(2.0f / 4.0f, 1.0f / 3.0f);
    glVertex3f(-size, -height, -size);

    // Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0f / 4.0f, 2.0f / 3.0f);
    glVertex3f(-size, height, size);
    glTexCoord2f(0.0f / 4.0f, 2.0f / 3.0f);
    glVertex3f(size, height, size);
    glTexCoord2f(0.0f / 4.0f, 1.0f / 3.0f);
    glVertex3f(size, -height, size);
    glTexCoord2f(1.0f / 4.0f, 1.0f / 3.0f);
    glVertex3f(-size, -height, size);

    /*
        // Top
        glTexCoord2f(3.0f / 4.0f, 3.0f / 3.0f);
        glVertex3f(size, size, size);
        glTexCoord2f(2.0f / 4.0f, 3.0f / 3.0f);
        glVertex3f(-size, size, size);
        glTexCoord2f(2.0f / 4.0f, 2.0f / 3.0f);
        glVertex3f(-size, size, -size);
        glTexCoord2f(3.0f / 4.0f, 2.0f / 3.0f);
        glVertex3f(size, size, -size);

        // Bottom
        glTexCoord2f(3.0f / 4.0f, 1.0f / 3.0f);
        glVertex3f(size, -size, -size);
        glTexCoord2f(2.0f / 4.0f, 1.0f / 3.0f);
        glVertex3f(-size, -size, -size);
        glTexCoord2f(2.0f / 4.0f, 0.0f / 3.0f);
        glVertex3f(-size, -size, size);
        glTexCoord2f(3.0f / 4.0f, 0.0f / 3.0f);
        glVertex3f(size, -size, size);
      */
    // Top
    glEnd();

    size += 8;
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(2.0f / 4.0f, 3.0f / 3.0f);
    glVertex3f(size, height - 15, size);
    glTexCoord2f(1.0f / 4.0f, 3.0f / 3.0f);
    glVertex3f(-size, height - 15, size);
    glTexCoord2f(1.0f / 4.0f, 2.0f / 3.0f);
    glVertex3f(-size, height - 15, -size);
    glTexCoord2f(2.0f / 4.0f, 2.0f / 3.0f);
    glVertex3f(size, height - 15, -size);

    // Bottom
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(2.0f / 4.0f, 1.0f / 3.0f);
    glVertex3f(size, -height, -size);
    glTexCoord2f(1.0f / 4.0f, 1.0f / 3.0f);
    glVertex3f(-size, -height, -size);
    glTexCoord2f(1.0f / 4.0f, 0.0f / 3.0f);
    glVertex3f(-size, -height, size);
    glTexCoord2f(2.0f / 4.0f, 0.0f / 3.0f);
    glVertex3f(size, -height, size);

    glEnd();
    glPopMatrix();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_LIGHTING);
}

void uninitEnvMap(void)
{
    if (cubeMapTexture)
    {
        glDeleteTextures(1, &cubeMapTexture);
    }
}
