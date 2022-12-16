#include <windows.h>
#include <gl/gl.h>
#include "raycasting01.h"
#include <math.h>

void DrawRectangle(float x1, float y1, float x2, float y2,
                float x3, float y3, float x4, float y4, float r, float g, float b)
{
    glBegin(GL_QUAD_STRIP);

        glColor3f(r, g, b);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);

    glEnd();
}
