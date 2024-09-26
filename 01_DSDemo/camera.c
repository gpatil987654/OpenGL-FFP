#include "common.h"
#include "camera.h"

vec3_cam_t bazierCurve(vec3_cam_t c1, vec3_cam_t c2, vec3_cam_t c3, vec3_cam_t c4, GLfloat t)
{
    vec3_cam_t p1, p2, p3;
    vec3_cam_t f1, f2;
    vec3_cam_t b1;

    p1.x = lerp(c1.x, c2.x, t);
    p1.y = lerp(c1.y, c2.y, t);
    p1.z = lerp(c1.z, c2.z, t);

    p2.x = lerp(c2.x, c3.x, t);
    p2.y = lerp(c2.y, c3.y, t);
    p2.z = lerp(c2.z, c3.z, t);

    p3.x = lerp(c3.x, c4.x, t);
    p3.y = lerp(c3.y, c4.y, t);
    p3.z = lerp(c3.z, c4.z, t);

    f1.x = lerp(p1.x, p2.x, t);
    f1.y = lerp(p1.y, p2.y, t);
    f1.z = lerp(p1.z, p2.z, t);

    f2.x = lerp(p2.x, p3.x, t);
    f2.y = lerp(p2.y, p3.y, t);
    f2.z = lerp(p2.z, p3.z, t);

    b1.x = lerp(f1.x, f2.x, t);
    b1.y = lerp(f1.y, f2.y, t);
    b1.z = lerp(f1.z, f2.z, t);

    return b1;
}

vec3_cam_t b_spline(vec3_cam_t *c1, int n, GLfloat t)
{
    vec3_cam_t *c = (vec3_cam_t *)malloc(sizeof(vec3_cam_t) * n);

    for (int i = 0; i < n; i++)
    {
        c[i] = c1[i];
    }

    for (int j = 0; j < n - 1; j++)
    {
        for (int i = 0; i < n - 1 - j; i++)
        {
            c[i].x = lerp(c[i].x, c[i + 1].x, t);
            c[i].y = lerp(c[i].y, c[i + 1].y, t);
            c[i].z = lerp(c[i].z, c[i + 1].z, t);
        }
    }
    vec3_cam_t cp = c[0];

    free(c);

    return cp;
}

vec3_cam_t catMull(vec3_cam_t *c1, int n, GLfloat t)
{
    vec3_cam_t *c = (vec3_cam_t *)malloc(sizeof(vec3_cam_t) * n);
    for (int i = 0; i < n; i++)
    {
        c[i] = c1[i];
    }

    vec3_cam_t cp;
    float tension = 1.0f;

    {

        t = fmin(fmax(t, 0.0f), 1.0f);

        int segment = (int)(t * (n - 3));
        segment = fmin(segment, n - 4);
        t = (t * (n - 3)) - segment;

        vec3_cam_t prev = c[segment];          // i == 0 ? c[i] : c[i - 1];
        vec3_cam_t currStart = c[segment + 1]; // c[i];
        vec3_cam_t currEnd = c[segment + 2];   // c[i + 1];
        vec3_cam_t next = c[segment + 3];      // i == n - 2 ? c[i + 1] : c[i + 2];

        float tSquared = t * t;
        float tCubed = tSquared * t;

        cp.x =
            (-.5f * tension * tCubed + tension * tSquared - .5f * tension * t) * prev.x +
            (1 + .5f * tSquared * (tension - 6) + .5f * tCubed * (4 - tension)) * currStart.x +
            (.5f * tCubed * (tension - 4) + .5f * tension * t - (tension - 3) * tSquared) * currEnd.x +
            (-.5f * tension * tSquared + .5f * tension * tCubed) * next.x;

        cp.y =
            (-.5f * tension * tCubed + tension * tSquared - .5f * tension * t) * prev.y +
            (1 + .5f * tSquared * (tension - 6) + .5f * tCubed * (4 - tension)) * currStart.y +
            (.5f * tCubed * (tension - 4) + .5f * tension * t - (tension - 3) * tSquared) * currEnd.y +
            (-.5f * tension * tSquared + .5f * tension * tCubed) * next.y;

        cp.z =
            (-.5f * tension * tCubed + tension * tSquared - .5f * tension * t) * prev.z +
            (1 + .5f * tSquared * (tension - 6) + .5f * tCubed * (4 - tension)) * currStart.z +
            (.5f * tCubed * (tension - 4) + .5f * tension * t - (tension - 3) * tSquared) * currEnd.z +
            (-.5f * tension * tSquared + .5f * tension * tCubed) * next.z;
    }

    return cp;
}
