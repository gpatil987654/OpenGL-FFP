#include "common.h"
#include "credits.h"

GLuint englishFont, marathiFont;
GLuint englishTitleFont, marathiTitleFont, fontCreditsTexture, bkgndTexture;

GLuint presentedTexture, ganeshTexture, rasterTexture, rtrTexture;

void initCredits()
{
    englishFont = BuildFont("Georgia", 50, 0.1f);
    englishTitleFont = BuildFont("Georgia", 50, 0.1f);

    marathiFont = BuildFont("Shivaji05", 50, 0.1f);
    marathiTitleFont = BuildFont("Shivaji05", 50, 0.1f);

    fontCreditsTexture = createTexture2DIntro("creditsTexture/grass4.png");
    bkgndTexture = createTexture2D("creditsTexture/ground3.png");
}

void print(GLuint texture);

void drawCredits()
{
    static int flag = 0;
    static GLfloat t = 0.0f;
    static GLfloat Alpha = 0.0f;

    //  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    /*
        glDisable(GL_LIGHTING);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_BLEND);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

        if (flag == 0)
        {
            glColor4f(1.0f, 1.0f, 1.0f, Alpha);
            glRasterPos2f(-0.5f, 0.3f);
            glPrintBitmap(marathiTitleFont, "KoD\\yaamaQalao Gar kaOlaa$....");

            glRasterPos2f(-0.3f, 0.0f);
            glPrintBitmap(marathiFont, "gaIt : ga. id. maaDgaULkr");

            glRasterPos2f(-0.3f, -0.15f);
            glPrintBitmap(marathiFont, "saMgaIt : sauQaIr fDko");

            glRasterPos2f(-0.3f, -0.3f);
            glPrintBitmap(marathiFont, "svar : AaSaa Baaosalao");

            glRasterPos2f(-0.3f, -0.45f);
            glPrintBitmap(marathiFont, "ica~pT : }na pa}sa");

            glRasterPos2f(-0.3f, -0.6f);
            glPrintBitmap(marathiFont, "gaIt p`kar : caI~gaIt ");
        }
        else if (flag == 1)
        {
            glColor4f(1.0f, 1.0f, 1.0f, Alpha);

            glRasterPos2f(-0.4f, 0.2f);
            glPrintBitmap(englishTitleFont, "Presented By");

            glRasterPos2f(-0.2f, 0.0f);
            glPrintBitmap(englishFont, "Ganesh Patil");

            glRasterPos2f(-0.3f, -0.2f);
            glPrintBitmap(englishFont, "Raster Group(RTR 5.0)");
        }
        else if (flag == 2)
        {
            glColor4f(1.0f, 1.0f, 1.0f, Alpha);
            glRasterPos2f(-0.45f, 0.6f);
            glPrintBitmap(englishTitleFont, "Technology Used");

            glRasterPos2f(-0.2f, 0.45f);
            glPrintBitmap(englishFont, "OpenGL FFP");

            glRasterPos2f(-0.2f, 0.3f);
            glPrintBitmap(englishFont, "Win32 SDK");

            glRasterPos2f(-0.55f, 0.0f);
            glPrintBitmap(englishTitleFont, "Data Structure Used");

            glRasterPos2f(-0.25f, -0.15f);
            glPrintBitmap(englishFont, "Doubly Linked List");

            glRasterPos2f(-0.3f, -0.45f);
            glPrintBitmap(englishTitleFont, "References");

            glRasterPos2f(-0.2f, -0.6f);
            glPrintBitmap(englishFont, "RTR Assignments");

            glRasterPos2f(-0.35f, -0.75f);
            glPrintBitmap(englishFont, "OpenGL Red Book 3rd Edition");
        }
        else if (flag == 3)
        {
            glColor4f(1.0f, 1.0f, 1.0f, Alpha);

            glRasterPos2f(-0.5f, 0.1f);
            glPrintBitmap(englishTitleFont, "Special Thanks To");

            glRasterPos2f(-0.4f, -0.15f);
            glPrintBitmap(englishFont, "Rushikesh Vidye (Group Leader)");
        }
        else if (flag == 4)
        {
            glColor4f(1.0f, 1.0f, 1.0f, Alpha);
            glRasterPos2f(-0.35f, 0.2f);
            glPrintBitmap(englishTitleFont, "Guided By");

            glRasterPos2f(-0.42f, -0.05f);
            glPrintBitmap(englishFont, "Dr. Rama Vijay Gokhale Mam");

            glRasterPos2f(-0.42f, -0.2f);
            glPrintBitmap(englishFont, "Pradnya Vijay Gokhale Mam");

            glRasterPos2f(-0.42f, -0.35f);
            glPrintBitmap(englishFont, "Rushikesh Vidye (Group Leader)");
        }
        else if (flag == 5)
        {

            glColor4f(1.0f, 1.0f, 1.0f, Alpha);
            glRasterPos2f(-0.3f, 0.0f);
            glPrintBitmap(englishTitleFont, "Inspired By");

            glRasterPos2f(-0.25f, -0.2f);
            glPrintBitmap(englishFont, "Dr. Vijay Gokhale sir");
        }
        */

    // Background
    glDisable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D, bkgndTexture);

    if (flag == 0)
        glColor4f(1.0f, 1.0f, 1.0f, t < 0.5f ? Alpha : 1.0f);
    else
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glBegin(GL_QUADS);

    for (int i = -16.0f; i < 16.0f; i += 2)
    {
        for (int j = -10.0f; j < 10.0f; j += 2)
        {
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(i + 2, j + 2);
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(i, j + 2);
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(i, j);
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(i + 2, j);
        }
    }
    /*
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(16, 16);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-16, 16);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-16, -16);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(16, -16);
    */
    glEnd();
    glPopMatrix();

    // Credits
    // glEnable(GL_LIGHTING);

    glEnable(GL_TEXTURE_GEN_S); // Auto Texture Generation
    glEnable(GL_TEXTURE_GEN_T);

    glBindTexture(GL_TEXTURE_2D, fontCreditsTexture);
    //  glColor3f(0.0f, 1.0f, 0.0f);
    if (flag == 0)
    {
        glColor4f(1.0f, 1.0f, 1.0f, Alpha);
        glPushMatrix();
        glScalef(2.0f, 2.0f, 2.0f);
        glTranslatef(1.0f, 2.0f, 0.0f);
        glPrint(marathiTitleFont, "KoD\\yaamaQalao Gar kaOlaa$....");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.0f);
        glPrint(marathiFont, "gaIt : ga. id. maaDgaULkr");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.0f, -1.0f, 0.0f);
        glPrint(marathiFont, "saMgaIt : sauQaIr fDko");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.2f, -3.0f, 0.0f);
        glPrint(marathiFont, "svar : AaSaa Baaosalao");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.1f, -5.0f, 0.0f);
        glPrint(marathiFont, "ica~pT : }na pa}sa");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.8f, -7.0f, 0.0f);
        glPrint(marathiFont, "gaIt p`kar : ica~gaIt ");
        glPopMatrix();
    }
    else if (flag == 1)
    {
        glColor4f(1.0f, 1.0f, 1.0f, Alpha);

        glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.0f);
        glScalef(2.0f, 2.0f, 2.0f);
        glPrint(englishTitleFont, "Presented By");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.0f, -1.0f, 0.0f);
        glPrint(englishFont, "Ganesh Patil");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.0f, -2.0f, 0.0f);
        glPrint(englishFont, "Raster Group(RTR 5.0)");
        glPopMatrix();
    }
    else if (flag == 2)
    {
        glColor4f(1.0f, 1.0f, 1.0f, Alpha);

        glPushMatrix();
        glTranslatef(-2.0f, 5.0f, 0.0f);
        glScalef(2.0f, 2.0f, 2.0f);
        glPrint(englishTitleFont, "Technology Used");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.0f, 3.5f, 0.0f);
        glPrint(englishFont, "OpenGL FFP");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.0f, 2.5f, 0.0f);
        glPrint(englishFont, "Win32 SDK");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-2.0f, 0.0f, 0.0f);
        glScalef(2.0f, 2.0f, 2.0f);
        glPrint(englishTitleFont, "Data Structure Used");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.5f, -1.5f, 0.0f);
        glPrint(englishFont, "Doubly Linked List");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, -4.0f, 0.0f);
        glScalef(2.0f, 2.0f, 2.0f);
        glPrint(englishTitleFont, "References");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-0.5f, -5.5f, 0.0f);
        glPrint(englishFont, "RTR Assignments");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.2f, -6.5f, 0.0f);
        glPrint(englishFont, "OpenGL Red Book 3rd Edition");
        glPopMatrix();
    }
    else if (flag == -1)
    {
        glColor4f(1.0f, 1.0f, 1.0f, Alpha);

        glPushMatrix();
        glTranslatef(-1.0f, 0.0f, 0.0f);
        glScalef(2.0f, 2.0f, 2.0f);
        glPrint(englishTitleFont, "Special Thanks To");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.0f, -2.0f, 0.0f);
        glPrint(englishFont, "Rushikesh Vidye (Group Leader)");
        glPopMatrix();
    }
    else if (flag == 3)
    {
        glColor4f(1.0f, 1.0f, 1.0f, Alpha);

        glPushMatrix();
        glTranslatef(-1.0f, 2.0f, 0.0f);
        glScalef(2.0f, 2.0f, 2.0f);
        glPrint(englishTitleFont, "Guided By");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.5f, 0.0f, 0.0f);
        glPrint(englishFont, "Dr. Rama Vijay Gokhale Mam");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-1.5f, -1.0f, 0.0f);
        glPrint(englishFont, "Pradnya Vijay Gokhale Mam");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, -2.0f, 0.0f);
        glPrint(englishFont, "Rushikesh Vidye (Group Leader)");
        glPopMatrix();
    }
    else if (flag == 4)
    {
        glColor4f(1.0f, 1.0f, 1.0f, Alpha);

        glPushMatrix();
        glTranslatef(0.0f, 1.0f, 0.0f);
        glScalef(2.0f, 2.0f, 2.0f);
        glPrint(englishTitleFont, "Inspired By");
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, -1.0f, 0.0f);
        glPrint(englishFont, "Dr. Vijay D. Gokhale sir");
        glPopMatrix();
    }

    if (t <= 1.0f)
    {
        t += 0.18f * d_time;

        if (t <= 0.2f)
        {
            Alpha = lerp(0.0f, 1.0f, t * 5.0f);
        }
        else if (t >= 0.8f)
        {
            Alpha = lerp(1.0f, 0.0f, (t - 0.8f) * 5.0f);
        }
    }
    else
    {
        t = 0;
        flag++;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_GEN_S); // Auto Texture Generation
    glDisable(GL_TEXTURE_GEN_T);

    glEnable(GL_LIGHTING);
}

void uninitCredits()
{
    if (fontCreditsTexture)
        glDeleteTextures(1, &fontCreditsTexture);

    if (bkgndTexture)
        glDeleteTextures(1, &bkgndTexture);
}
