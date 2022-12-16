#include <windows.h>
#include <gl/gl.h>
#include "raycasting01.h"
#include <math.h>

//player.coord.x = 0;
//player.coord.y = 0;

void DrawPlayer(float x, float y, float a, float dx, float dy)
{
    glPointSize(8);
    glBegin(GL_POINTS);

        glColor3f(0.8f, 0.23f, 0.23f);
        glVertex2f(x, y);

    glEnd();
}

void PlayerControl()
{
    if (GetKeyState('W') < 0)
    {
        player.coord.y += player.dy / 15;
        player.coord.x += player.dx / 15;
    }
    if (GetKeyState('A') < 0)
    {
        player.angle += 0.08f;
        if (player.angle > PI * 2)
        {
            player.angle = 0;
        }
        player.dx = cos(player.angle);
        player.dy = sin(player.angle);
    }
    if (GetKeyState('S') < 0)
    {
        player.coord.y -= player.dy / 15;
        player.coord.x -= player.dx / 15;
    }
    if (GetKeyState('D') < 0)
    {
        player.angle -= 0.08f;
        if (player.angle < 0.0f)
        {
            player.angle = PI * 2;
        }
        player.dx = cos(player.angle);
        player.dy = sin(player.angle);
    }

    player.dx = cos(player.angle);
    player.dy = sin(player.angle);
}
