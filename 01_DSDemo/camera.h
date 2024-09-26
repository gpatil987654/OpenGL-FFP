#ifndef __CAMERA_H
#define __CAMERA_H
#include "common.h"

typedef struct vec3_cam vec3_cam_t;

struct vec3_cam
{
    GLfloat x, y, z;
};


vec3_cam_t bazierCurve(vec3_cam_t c1, vec3_cam_t c2, vec3_cam_t c3, vec3_cam_t c4, GLfloat t);
vec3_cam_t b_spline(vec3_cam_t *c, int n, GLfloat t);
vec3_cam_t catMull(vec3_cam_t *c1, int n, GLfloat t);
#endif
