#ifndef __COMMON_H
// For Random rand_s() used in intro for saturn
#define CRT_RAND_S
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "glcorearb.h"

#define _USE_MATH_DEFINES
#include <math.h>
/*
typedef struct vec3 vec3_t;

struct vec3
{
    GLfloat x, y, z;
};
*/

// Delta time
clock_t start_time, end_time, delta_time;

double total_time;
double d_time;

float lerp(float start, float end, float t);
GLuint createTexture2D(const char *filepath);
GLuint createTexture2DTree(const char *filepath);

// Font Rendering
GLuint BuildFont(char *fontName, int fontSize, float depth);
GLuint BuildFontBitmap(char *name, int fontSize, int bold);
GLvoid glPrint(GLuint base, const char *str, ...);
void glPrintBitmap(GLuint base, const char *str, ...);

void cube(void);

void stbi_image_free(void *retval_from_stbi_load);
unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
void stbi_set_flip_vertically_on_load(int flag_true_if_should_flip);

void calculateNormal(GLfloat x1, GLfloat y1, GLfloat z1,
                     GLfloat x2, GLfloat y2, GLfloat z2,
                     GLfloat x3, GLfloat y3, GLfloat z3);

void shadowMatrix(float ground[], float light[]);

void initTorus(void);
void drawTorus(void);

#endif
