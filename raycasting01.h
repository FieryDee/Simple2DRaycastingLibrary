#ifndef RAYCASTING01_H_INCLUDED
#define RAYCASTING01_H_INCLUDED



#endif // RAYCASTING01_H_INCLUDED

#define MAP_WIDTH 15
#define MAP_HEIGHT 15

#define PI 3.1415926535

typedef struct {
    float x, y;
} TPoint;

typedef struct {
    TPoint position;
    TPoint direction;
} TVector;

typedef struct {
    TPoint coord;
    float angle;
    float dx, dy;
} TPlayer;

typedef struct {
    TPoint a, b; // a is a beginning, and b is a ending
} TBoundary;

short map[MAP_HEIGHT][MAP_WIDTH + 1];
TPlayer player;


void DrawBoundary(TBoundary boundary);

void DrawRectangle(float x1, float y1, float x2, float y2,
                float x3, float y3, float x4, float y4, float red, float green, float blue);


void DrawPlayer(float x, float y, float angle, float dx, float dy);
void PlayerControl();


void InitMap();
void DrawMap();


TPoint GetDistance(TPoint point1, TPoint point2);

void DefineRays(TVector *masOfRays, int countOfRays, TBoundary boundary);

void DrawRay(TVector ray, float red, float green, float blue);
void DrawRays(TVector *masOfRays, int countOfRays, TBoundary *masOfWalls, int countOfWalls, TPoint *ptrPoint, float red, float green, float blue);

char GetIntersection(TVector ray, TBoundary boundary, TPoint *intersectionPoint);
