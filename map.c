#include <windows.h>
#include <gl/gl.h>
#include "raycasting01.h"
#include <math.h>

void InitMap()
{

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if ((i == 0) || (i == MAP_HEIGHT - 1))
            {
                map[i][j] = 1;
            }
            else if ((j == 0) || (j == MAP_WIDTH - 1))
            {
                map[i][j] = 1;
            }
            else
            {
                map[i][j] = 0;
            }
        }
    }
}

void DrawMap()
{
    int x, y;
    float x1, x2, x3, x4, y1, y2, y3, y4;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            x1 = x + 0.02f; y1 = y + 0.02f;
            x2 = x + 1.0f - 0.02f; y2 = y + 0.02f;
            x3 = x + 0.02f; y3 = y + 1.0f - 0.02f;
            x4 = x + 1.0f - 0.02f, y4 = y + 1.0f - 0.02f;
            if (map[y][x] == 1)
            {
                DrawRectangle(x1, y1, x2, y2, x3, y3, x4, y4, 1, 0.6f, 1);
            }
            if (map[y][x] == 0)
            {
                DrawRectangle(x1, y1, x2, y2, x3, y3, x4, y4, 0.2f, 0.2f, 0.2f);
            }
        }
    }
}
