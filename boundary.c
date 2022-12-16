#include <windows.h>
#include <gl/gl.h>
#include "raycasting01.h"
#include <math.h>

void DrawBoundary(TBoundary wall)
{
    glBegin(GL_LINES);

        glColor3f(1, 1, 1);
        glVertex2f(wall.a.x, wall.a.y);
        glVertex2f(wall.b.x, wall.b.y);

    glEnd();
}
