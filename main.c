/*
---------------------------------------

Hi, this program is something like a library for raycasting. You can use it for different purposes, this project is open source.                                                                                                                                                      UwU
I hope this program will help you in your work and you will actively work with it and make changes. And I can't comment...

P.S. There is a small bug in the code related to the walls, which I called strange, and with the middle ray.
This ray can pass through these walls, although it should not. Bug works when count of rays is odd.

---------------------------------------
*/



#include <windows.h>
#include <gl/gl.h>
#include "raycasting01.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "Raycasting",
                          WS_OVERLAPPEDWINDOW,
                          /*CW_USEDEFAULT,*/0,
                          /*CW_USEDEFAULT,*/0,
                          /*GetSystemMetrics(SM_CXFULLSCREEN),*/1024,
                          /*GetSystemMetrics(SM_CYFULLSCREEN),*/512,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    /* program initialization */
    player.coord.x = 1;
    player.coord.y = 7;
    player.angle = 0.5 * PI;
    player.dx = cos(player.angle);
    player.dy = sin(player.angle);

    int wallsCount = 9;
    TBoundary wall[wallsCount];
    wall[0].a.x = 3;
    wall[0].a.y = 7;
    wall[0].b.x = 10;
    wall[0].b.y = 7;

    wall[1].a.x = 6 + 0.01f;
    wall[1].a.y = 3;
    wall[1].b.x = 6 + 0.01f;
    wall[1].b.y = 10;

    wall[2].a.x = 1;
    wall[2].a.y = 12;
    wall[2].b.x = 14;
    wall[2].b.y = 12;

    wall[3].a.x = 13;
    wall[3].a.y = 4;
    wall[3].b.x = 13;
    wall[3].b.y = 12;

    // "strange" wall
    wall[4].a.x = 0 + 0.01f;
    wall[4].a.y = 0 + 0.01f;
    wall[4].b.x = MAP_WIDTH - 0.01f;
    wall[4].b.y = 0 + 0.01f;

    wall[5].a.x = 0 + 0.01f;
    wall[5].a.y = MAP_HEIGHT - 0.01f;
    wall[5].b.x = MAP_WIDTH - 0.01f;
    wall[5].b.y = MAP_HEIGHT - 0.01f;

    // "strange" wall
    wall[6].a.x = 0 + 0.01f;
    wall[6].a.y = 0 + 0.01f;
    wall[6].b.x = 0 + 0.01f;
    wall[6].b.y = MAP_HEIGHT - 0.01f;

    wall[7].a.x = MAP_WIDTH - 0.01f;
    wall[7].a.y = 0 + 0.01f;
    wall[7].b.x = MAP_WIDTH - 0.01f;
    wall[7].b.y = MAP_HEIGHT - 0.01f;

    // "strange" wall
    wall[8].a.x = 3;
    wall[8].a.y = 1;
    wall[8].b.x = 3;
    wall[8].b.y = 0;

    int raysCount = 121; // count of rays
    TVector ray[raysCount];

    char pointIntersected = 0;
    TPoint point;
    point.x = 0;
    point.y = 0;

    //InitMap();
    for (int i = 0; i < MAP_HEIGHT ; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            printf("%i ", map[i][j]);
        }
        printf("\n");
    }

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();

            glScalef(1.0f / MAP_WIDTH, 2.0f / MAP_HEIGHT, 1.0f);
            glTranslatef(-MAP_WIDTH * 0.5, -MAP_HEIGHT * 0.5, 0);


            DrawMap();

            for (int i = 0; i < wallsCount; i++)
            {
                DrawBoundary(wall[i]);
            }

            PlayerControl();

            // magic and raycasting
            for (int j = 0; j < wallsCount; j++)
            {
                DefineRays(ray, raysCount, wall[j]);
                DrawRays(ray, raysCount, wall, wallsCount, &point, 1.0f, 1.0f, 1.0f);
            }

            DrawPlayer(player.coord.x, player.coord.y, player.angle, player.dx, player.dy);

            glPopMatrix();

            SwapBuffers(hDC);
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

