#include <windows.h>
#include <gl/gl.h>
#include "raycasting01.h"
#include <stdio.h>
#include <math.h>

void DefineRays(TVector *rays, int count, TBoundary wall)
{
    float delay = -(float)count / 2;
    TPoint point;

    for (int i = 0; i < count; i++)
    {
        rays[i].position.x = player.coord.x;
        rays[i].position.y = player.coord.y;


        rays[i].direction.x = cos(player.angle + (delay / 180 * PI));
        rays[i].direction.y = sin(player.angle + (delay / 180 * PI));


        if (GetIntersection(rays[i], wall, &point))
        {
            rays[i].direction.x = point.x - rays[i].position.x;
            rays[i].direction.y = point.y - rays[i].position.y;
        }

        delay += 1;
    }
}

void DrawRay(TVector ray, float r, float g, float b)
{
    glBegin(GL_LINES);

        glColor4f(r, g, b, 0.3f);
        glVertex2f(ray.position.x, ray.position.y);
        glVertex2f(ray.position.x + ray.direction.x, ray.position.y + ray.direction.y);

    glEnd();
}

void DrawRays(TVector *rays, int rCount, TBoundary *walls, int wCount, TPoint *ptrPoint, float r, float g, float b)
{
    TPoint closest, farthest, dist;
    for (int i = 0; i < rCount; i++)
    {
        closest.x = 0;
        closest.y = 0;

        farthest.x = 1999999;
        farthest.y = 1999999;

        for (int j = 0; j < wCount; j++)
        {
            if (GetIntersection(rays[i], walls[j], ptrPoint))
            {
                dist = GetDistance(rays[i].position, *ptrPoint);

                if ((dist.x < farthest.x) && (dist.y < farthest.y))
                {
                    farthest = dist;
                    closest = *ptrPoint;
                }
            }
        }

        if (closest.x && closest.y)
        {


            //glPointSize(7);



            glBegin(GL_LINES);

                glColor3f(r, g, b);
                glVertex2f(rays[i].position.x, rays[i].position.y);
                glVertex2f(closest.x, closest.y);

            glEnd();
        }
        else
        {
            DrawRay(rays[i], 0.8f, 0.23f, 0.23f);
        }
    }
}

char GetIntersection(TVector ray, TBoundary wall, TPoint *ptrPoint)
{
    float r; // ray's coefficient
    float s; // line segment coefficient

    float x1 = wall.a.x;
    float y1 = wall.a.y;
    float x2 = wall.b.x;
    float y2 = wall.b.y;

    float x3 = ray.position.x;
    float y3 = ray.position.y;
    float x4 = ray.position.x + ray.direction.x;
    float y4 = ray.position.y + ray.direction.y;

    //float den = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    float den = ((y2 - y1) * (x4 - x3) - (x2 - x1) * (y4 - y3));
    if (den == 0)
    {
        return FALSE;
    }

    //s = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    //r = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / den;

    s = ((x1 - x3) * (y4 - y3) - (x4 - x3) * (y1 - y3)) / den;
    r = ((y3 - y1) * (x2 - x1) - (x3 - x1) * (y2 - y1)) / den;

    if ((r >= 0) && (s >= 0) && (s <= 1))
    {
        ptrPoint->x = s * (x2 - x1) + x1;
        ptrPoint->y = s * (y2 - y1) + y1;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

TPoint GetDistance(TPoint point1, TPoint point2)
{
    TPoint dist;
    dist.x = sqrt((point1.x - player.coord.x) * (point1.x - player.coord.x) + (point2.y - player.coord.y) * (point2.y - player.coord.y));
    dist.y = sqrt((point1.x - player.coord.x) * (point1.x - player.coord.x) + (point2.y - player.coord.y) * (point2.y - player.coord.y));

    return dist;
}
