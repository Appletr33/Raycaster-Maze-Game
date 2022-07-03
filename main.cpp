#include <glew.h>
#include <glfw3.h>
#include <SDL.h>


#include <iostream>
#include <math.h>

#include <stack>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "audio.h"

#define PI 3.1415926535
#define P2 PI/2
#define P3 3 * PI/2
#define DR 0.0174533 // one degree in radians

int screenHeight = 512;
int screenWidth = 1024;
int drawscreenH;
int drawscreenW;

bool debug = false;

float px, py, pdx, pdy, pa; //Player Position
//key
bool keys[1024];
//mouse
bool inwindow;
bool cursorLock = false;
float mouseX;
float mouseY;
float mousepreviousX;
//Menu
bool mazeGeneration = true;
int bull = 0;
//Present
int presentX = 1;
int presentY = 1;


int mapX = 32, mapY = 32, mapS = 1024;
int mapOffeset = mapS / pow(mapX / 8, 3);
int map[] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};



void drawMap2D()
{
    int xo, yo;
    for (int y = 0; y < mapY; y++)
    {
        for (int x = 0; x < mapX; x++)
        {
            if (map[y * mapX + x] == 1) {glColor3f(1, 1, 1);}
            else if (map[y * mapX + x] == 2) {glColor3f(1, 1, 0);}
            else {glColor3f(0, 0, 0);}
            xo = x * mapOffeset; yo = y * mapOffeset;
            
            glBegin(GL_QUADS);
            glVertex2i(xo + 1, yo + 1);
            glVertex2i(xo + 1, yo + mapOffeset - 1);
            glVertex2i(xo + mapOffeset - 1, yo + mapOffeset - 1);
            glVertex2i(xo + mapOffeset - 1, yo + 1);
            glEnd();
        }
    }
}

float dist(float ax, float ay, float bx, float by, float ang)
{
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void drawRays2D()
{
    int r, mx, my, mp, dof;
    float rx = 0.0, ry = 0.0, ra, xo = 0.0, yo = 0.0, disT;
    
    ra = pa - DR * 30;
    if (ra < 0)
        ra += 2 * PI;
    if (ra > 2 * PI)
        ra -= 2 * PI;

        
    for (r = 0; r < 60; r++)
    {

        // Check Horizontal Lines
        dof = 0;
        float disH = 10000000, hx=px, hy=py;
        float aTan = -1 / tan(ra); //WHAT THE FUC ...
        if (ra > PI) //looking up or down
        {
            ry = (((int)py / mapOffeset) * mapOffeset) - 0.0001;
            rx = (py - ry) * aTan + px;
            yo = -mapOffeset;
            xo =- yo * aTan;
        }
        
        if (ra < PI)
        {
            ry = (((int)py / mapOffeset) * mapOffeset) + mapOffeset;
            rx = (py - ry) * aTan + px;
            yo = mapOffeset;
            xo =- yo * aTan;
        }
        
        if(ra == 0 || ra== PI) // looking straight left or right
        {
            rx = px;
            ry = py;
            dof = mapX;
        }
        
        while (dof < mapX)
        {
            mx = (int)(rx) / mapOffeset;
            my = (int)(ry) / mapOffeset;
            mp = my * mapX + mx;
            
            if (mp > 0 && mp < mapX * mapY && map[mp] != 0)
            {
                hx = rx;
                hy = ry;
                disH = dist(px, py, hx, hy, ra);
                dof = mapX; // Wall Hit
            }


            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }

        // Check Vertical Lines
        dof = 0;
        float disV = 10000000, vx=px, vy=py;
        float nTan = -tan(ra);
        if (ra > P2 && ra < P3) //looking left
        {
            rx = (((int)px / mapOffeset) * mapOffeset) - 0.0001;
            ry = (px - rx) * nTan + py;
            xo = -mapOffeset;
            yo =- xo * nTan;
        }
        
        if (ra < P2 || ra > P3) //looking right
        {
            rx = (((int)px / mapOffeset) * mapOffeset) + mapOffeset;
            ry = (px - rx) * nTan + py;
            xo = mapOffeset;
            yo =- xo * nTan;
        }
        
        if(ra == 0 || ra== PI) // looking up or down
        {
            rx = px;
            ry = py;
            dof = mapX;
        }
        
        while (dof < mapX)
        {
            mx = (int)(rx) / mapOffeset;
            my = (int)(ry) / mapOffeset;
            mp = my * mapX + mx;
            
            if (mp > 0 && mp < mapX * mapY && map[mp] != 0)
            {
                vx = rx;
                vy = ry;
                disV = dist(px, py, vx, vy, ra);
                dof = mapX; // Wall Hit
            }

            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        
        if (disV < disH)
        {
            rx=vx;
            ry = vy;
            disT = disV;
            
            if (map[((int)(ry) / mapOffeset) * mapX + ((int)(rx) / mapOffeset)] == 1)
                glColor3f(0.9, 0, 0);
            else
                glColor3f(0.9, 0.9, 0.9);
        }
        else if (disV > disH)
        {
            rx=hx;
            ry = hy;
            disT = disH;
            if (map[((int)(ry) / mapOffeset) * mapX + ((int)(rx) / mapOffeset)] == 1)
                glColor3f(0.7, 0, 0);
            else
                glColor3f(0.7, 0.7, 0.7);
        }
        
        if (debug)
        {
            //Draw 2d ray
            glLineWidth(1);
            glBegin(GL_LINES);
            glVertex2i(px, py);
            glVertex2i(rx, ry);
            glEnd();
        }
        
        
        //Draw 3d Walls-----
        float ca = pa - ra;
        if (ca < 0)
            ca += 2 * PI;
        if (ca > 2 * PI)
            ca -= 2 * PI;
        disT = disT * cos(ca); // no more fisheye
        
        if (debug)
        {
            drawscreenH = 320;
            drawscreenW = 530;
        }
        else
        {
            drawscreenH = screenHeight;
        }  drawscreenW = screenWidth;
            

        float lineH = (mapOffeset * drawscreenH) / disT; //change? ...
        if (lineH > drawscreenH)//line height
            lineH = drawscreenH;
        float lineO = ((drawscreenH / 2) - (lineH / 2));//offest ... change? 160 = full window height /2 (320) / 2
        
        glLineWidth(drawscreenW / mapX);
        glBegin(GL_LINES);
        
        if (!debug)
        {
            glVertex2i(r * (mapX / 2) + 50, lineO);
            glVertex2i(r * (mapX / 2) + 50, lineH + lineO);
        }
        else
        {
            glVertex2i(r * 8 + 530, lineO);
            glVertex2i(r * 8 + 530, lineH + lineO);
        }
        glEnd();
        
        
       /*
        //Check if object can be seen
        float fVectX = presentX - px;
        float fVectY = presentY - py;
        float fDistanceFromPlayer = sqrt(fVectX * fVectX + fVectY * fVectY);
        float fObjectAngle = atan2f(pdy, pdx) - atan2f(fVectY, fVectX);
        if(fObjectAngle < -PI)
            fObjectAngle += 2.0f * PI;
        if (fObjectAngle > PI)
            fObjectAngle -= 2.0f * PI;
        
        bool objinvew = fabs(fObjectAngle) < (DR * 30) / 2.0f;
        if (objinvew)
            std::cout << fDistanceFromPlayer << std::endl;
        
        if (objinvew && fDistanceFromPlayer >= 0.5f && fDistanceFromPlayer < mapX * mapOffeset)
        {
            lineH = (mapOffeset * 320) / fDistanceFromPlayer; //change? ...
            if (lineH > 320)//line height
                lineH = 320;
            lineO = (160 - (lineH / 2));
            
            glColor3f(1, 1, 1);
            glBegin(GL_LINES);
            glVertex2i(r * 8 + 530, lineO);
            glVertex2i(r * 8 + 530, lineH + 100 + lineO);
            glEnd();
        }
        */
        
        
        
        ra += DR;
        if (ra < 0)
            ra += 2 * PI;
        if (ra > 2 * PI)
            ra -= 2 * PI;
    }
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        if (cursorLock)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            cursorLock = false;
        }

        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            cursorLock = true;
        }
    }
}

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos)
{
    if (inwindow)
    {
        mouseX = xPos;
        mouseY = yPos;
    }

}

void cursorEnterCallback (GLFWwindow *window, int entered)
{
    if (entered)
    {
        inwindow = true;
    }
    else
    {
        inwindow = false;
    }
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods )
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (mouseX >= screenWidth / 2 - 60 && mouseX <= screenWidth / 2 + 60 && mouseY >= screenHeight / 2 - 20 && mouseY <= screenHeight / 2 + 20)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            cursorLock = true;
            
        }
        else if (mouseX >= screenWidth / 2 - 60 && mouseX <= screenWidth / 2 + 60 && mouseY >= screenHeight / 2 - 20 +50 && mouseY <= screenHeight / 2 + 20 + 50)
        {
            if (debug)
                debug = false;
            else
                debug = true;
        }
    }
        
}

void drawPlayer()
{
    glColor3f(1, 1, 0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(px, py);
    glEnd();
    
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px + pdx * 3, py + pdy * 3);
    glEnd();
}

void init(Audio &sound)
{
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 1024, 512, 0);
    px = mapOffeset * 2; py = mapOffeset * 2;
    pdx = cos(pa) * 1;
    pdy = sin(pa) * 1;
    
    sound.play();
    

}

void InputMovement(Audio &sound)
{
    if(keys[GLFW_KEY_W])
    {
        px += pdx; py += pdy;
        if (map[(((int)py / mapOffeset) * mapX + ((int)px / mapOffeset))] == 1)
        {
            px -= pdx; py -= pdy;
        }
        if (map[(((int)py / mapOffeset) * mapX + ((int)px / mapOffeset))] == 2)
        {
            init(sound);
            mazeGeneration = true;
            cursorLock = false;
        }
        
    }
    if(keys[GLFW_KEY_A])
    {
        px += pdy; py -= pdx;
        if (map[(((int)py / mapOffeset) * mapX + ((int)px /mapOffeset))] == 1)
        {
            px -= pdy; py += pdx;
        }
        if (map[(((int)py / mapOffeset) * mapX + ((int)px /mapOffeset))] == 2)
        {
            init(sound);
            mazeGeneration = true;
            cursorLock = false;
        }
            
    }
    if(keys[GLFW_KEY_S])
    {
        px -= pdx; py -= pdy;
        
        if (map[(((int)py / mapOffeset) * mapX + ((int)px /mapOffeset))] == 1)
        {
            px += pdx; py += pdy;
        }
        if (map[(((int)py / mapOffeset) * mapX + ((int)px /mapOffeset))] == 2)
        {
            init(sound);
            mazeGeneration = true;
            cursorLock = false;
        }
            
    }
    if(keys[GLFW_KEY_D])
    {
        px -= pdy; py += pdx;
        if (map[(((int)py / mapOffeset) * mapX + ((int)px / mapOffeset))] == 1)
        {
            px += pdy; py -= pdx;
        }
        if (map[(((int)py / mapOffeset) * mapX + ((int)px / mapOffeset))] == 2)
        {
            init(sound);
            mazeGeneration = true;
            cursorLock = false;
        }
            
    }
}

void InputMouseMovement()
{
    if (cursorLock)
    {
        if (mousepreviousX < mouseX)
        {
            pa += 0.05;
            if (pa > 2 * PI)
                pa -= 2*PI;
            pdx = cos(pa) * 1;
            pdy = sin(pa) * 1;
        }
        
        else if (mousepreviousX > mouseX)
        {
            pa -= 0.05;
            if (pa < 0)
                pa += 2*PI;
            pdx = cos(pa) * 1;
            pdy = sin(pa) * 1;
        }
            
        
        mousepreviousX = mouseX;
    }
}

void drawMenu(GLFWwindow* window)
{
    glfwGetWindowSize(window, &screenWidth, &screenHeight);
    
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glVertex2i(screenWidth / 2 - 60, screenHeight / 2 - 20);
    glVertex2i(screenWidth / 2 - 60, screenHeight /2 + 20);
    glVertex2i(screenWidth / 2 + 60, screenHeight / 2 + 20);
    glVertex2i(screenWidth / 2 + 60, screenHeight / 2 - 20);
    glEnd();
    
    if (debug)
        glColor3f(0, 1, 0);
    else
        glColor3f(1, 0, 0);
    
    glBegin(GL_QUADS);
    glVertex2i(screenWidth / 2 - 60, screenHeight / 2 - 20 + 50);
    glVertex2i(screenWidth / 2 - 60, screenHeight /2 + 20 + 50);
    glVertex2i(screenWidth / 2 + 60, screenHeight / 2 + 20 + 50);
    glVertex2i(screenWidth / 2 + 60, screenHeight / 2 - 20 + 50);
    glEnd();
    
    
    



    glLineWidth(2);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    // P
    glVertex2i(screenWidth / 2 - 50, screenHeight / 2 - 10);
    glVertex2i(screenWidth / 2 - 50, screenHeight /2 + 10);
    
    glVertex2i(screenWidth / 2 - 50, screenHeight / 2);
    glVertex2i(screenWidth / 2 - 40, screenHeight / 2);
    
    glVertex2i(screenWidth / 2 - 50, screenHeight / 2 - 10);
    glVertex2i(screenWidth / 2 - 40, screenHeight / 2 - 10);
    
    glVertex2i(screenWidth / 2 - 40, screenHeight / 2 - 10);
    glVertex2i(screenWidth / 2 - 40, screenHeight / 2);
    
    //L
    glVertex2i(screenWidth / 2 - 30, screenHeight / 2 - 10);
    glVertex2i(screenWidth / 2 - 30, screenHeight / 2 + 10);
    
    glVertex2i(screenWidth / 2 - 30, screenHeight / 2 + 10);
    glVertex2i(screenWidth / 2 - 20, screenHeight / 2 + 10);
    
    // A
    glVertex2i(screenWidth / 2 - 10, screenHeight / 2 - 10);
    glVertex2i(screenWidth / 2 - 15, screenHeight /2 + 10);
    
    glVertex2i(screenWidth / 2 - 10, screenHeight / 2 - 10);
    glVertex2i(screenWidth / 2 - 5, screenHeight / 2 + 10);
    
    glVertex2i(screenWidth / 2 - 15, screenHeight / 2);
    glVertex2i(screenWidth / 2 - 5, screenHeight / 2);
    
    // Y
    glVertex2i(screenWidth / 2 + 5, screenHeight / 2);
    glVertex2i(screenWidth / 2 + 5, screenHeight /2 + 10);
    
    glVertex2i(screenWidth / 2, screenHeight / 2 - 10);
    glVertex2i(screenWidth / 2 + 5, screenHeight /2);
    
    glVertex2i(screenWidth / 2 + 10, screenHeight / 2 - 10);
    glVertex2i(screenWidth / 2 + 5, screenHeight /2 );
    
    glEnd();
    
    
    //std::cout << "WINDOW HEIGHT: " << screenHeight << "\t WINDOW WIDTH: " << screenWidth << std::endl;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    /*MAZE GENERATION ALGORITHM*/

    //init
    int mazeWidth = mapX;
    int mazeHeight = mapY;


    std::stack<std::pair<int, int>> m_stack;
    m_stack.push(std::make_pair(1, 1));
    map[mapX + 1] = 0; //bc top left 1,1 is where we start
    
    unsigned long previousStackSize = m_stack.size();
    // end init
    

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 512, "MAZE DAY", NULL, NULL);
    
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetCursorEnterCallback(window, cursorEnterCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    
    
    SDL_Init(SDL_INIT_AUDIO);
    //Sound
    Audio sound;
    sound.load("song.wav");
    init(sound); // Init our values
    
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        
        InputMouseMovement();
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        if (cursorLock && !mazeGeneration)
        {
            InputMovement(sound);
            if (debug)
            {
                drawMap2D();
                drawPlayer();
            }
            drawRays2D();
        }
        
        else if (mazeGeneration && cursorLock)
        {
            
           
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            
            std::vector<int> neighbors;
            int next_cellX = m_stack.top().first;
            int next_cellY = m_stack.top().second;
            
            if(map[mapX * m_stack.top().second +  m_stack.top().first + 1] == 1 && next_cellX + 1 < mapX - 1 && map[mapX * m_stack.top().second +  m_stack.top().first + 2] == 1 && map[mapX * (m_stack.top().second + 1) +  m_stack.top().first + 1] == 1 && map[mapX * (m_stack.top().second - 1) +  m_stack.top().first + 1] == 1) //RIGHT :0:
            {
                neighbors.push_back(0);
            }
                
            if(map[mapX * m_stack.top().second +  m_stack.top().first - 1] == 1 && next_cellX - 1> 0 && map[mapX * m_stack.top().second +  m_stack.top().first - 2] == 1 && map[mapX * (m_stack.top().second + 1) +  m_stack.top().first - 1] == 1 && map[mapX * (m_stack.top().second - 1) +  m_stack.top().first - 1] == 1) //LEFT :0:
            {
                neighbors.push_back(1);
            }
                
            if(map[mapX * (m_stack.top().second + 1) +  m_stack.top().first] == 1 && next_cellY + 1 < mapY - 1 && map[mapX * (m_stack.top().second + 2) +  m_stack.top().first] == 1 && map[mapX * (m_stack.top().second + 1) +  m_stack.top().first + 1] == 1 && map[mapX * (m_stack.top().second + 1) +  m_stack.top().first - 1] == 1) //DOWN :0:
            {
                neighbors.push_back(2);
            }
                
            if(map[mapX * (m_stack.top().second - 1) +  m_stack.top().first] == 1 && next_cellY - 1 > 0 && map[mapX * (m_stack.top().second - 2) +  m_stack.top().first] == 1 && map[mapX * (m_stack.top().second - 1) + m_stack.top().first + 1] == 1 && map[mapX * (m_stack.top().second - 1) +  m_stack.top().first - 1] == 1) //UP :0:
            {
                neighbors.push_back(3);
            }
                
            
            if (neighbors.size() > 0)
            {
                int next_cell_dir = neighbors[rand() % neighbors.size()];
                
                switch (next_cell_dir) {
                    case 0:
                        next_cellX += 1;
                        map[mapX * next_cellY + next_cellX] = 0;
                        m_stack.push(std::make_pair((next_cellX), (next_cellY)));
                        break;
                    
                    case 1:
                        next_cellX -= 1;
                        map[mapX * next_cellY + next_cellX] = 0;
                        m_stack.push(std::make_pair((next_cellX), (next_cellY)));
                        break;
                        
                    case 2:
                        next_cellY += 1;
                        map[mapX * next_cellY + next_cellX] = 0;
                        m_stack.push(std::make_pair((next_cellX), (next_cellY)));
                        break;
                    case 3:
                        next_cellY -= 1;
                        map[mapX * next_cellY + next_cellX] = 0;
                        m_stack.push(std::make_pair((next_cellX), (next_cellY)));
                        break;
                        
                        
                    default:
                        break;
                }
            }
            else if (m_stack.size() != 1)
            {
                m_stack.pop();
            }
            else
            {
                mazeGeneration = false;
                map[mapX * presentY + presentX] = 2;
            }
            
            if (previousStackSize < m_stack.size())
            {
                presentX = m_stack.top().first;
                presentY = m_stack.top().second;
                //std::cout << "PRESENT X: " << presentX << std::endl;
                //std::cout << "PRESENT Y: " << presentY << "\t" << m_stack.size() << std::endl;
                previousStackSize = m_stack.size();
                
            }
                
            
            
            
            
            /*
            if (direction == 0) // Right
            {
                next_cellX = m_stack.top().first + 1;
                next_cellY = m_stack.top().second;
                
                if (map[mapX * next_cellY + next_cellX] == 1 && next_cellX < mapX - 1)
                {
                    map[mapX * next_cellY + next_cellX] = 0;
                    m_stack.push(std::make_pair((next_cellX), (next_cellY)));
                }
                else if (current_cellX == m_stack.top().first && current_cellY == m_stack.top().second && m_stack.size() != 1 )
                {
                    m_stack.pop();
                }

            }
            
            else if (direction == 1) // Down;
            {
                next_cellX = m_stack.top().first;
                next_cellY = m_stack.top().second + 1;
                
                if (map[mapX * next_cellY + next_cellX] == 1 && next_cellY < mapY - 1 && map[mapX * (current_cellY - 1) + current_cellX] == 1 && map[mapX * (current_cellY - 1) + current_cellX] == 1)
                {
                    map[mapX * next_cellY + next_cellX] = 0;
                    m_stack.push(std::make_pair((next_cellX), (next_cellY)));
                }
            }
            
            else if (direction == 2) // LEFT;
            {
                next_cellX = m_stack.top().first - 1;
                next_cellY = m_stack.top().second;
                
                if (map[mapX * next_cellY + next_cellX] == 1 && next_cellX > 0 && map[mapX * current_cellY + current_cellX - 2] == 1)
                {
                    map[mapX * next_cellY + next_cellX] = 0;
                    m_stack.push(std::make_pair((next_cellX), (next_cellY)));
                }

            }
            
            
            map[mapX * next_cellY + next_cellX] = 0;
            m_stack.push(std::make_pair((next_cellX), (next_cellY)));
                
             */
            
                
            for (int x = 0; x < mazeWidth; x++)
            {
                for (int y = 0; y < mazeHeight; y++)
                {
                    int xo = x * mapOffeset; int yo = y * mapOffeset;
                    if (x == m_stack.top().first && y == m_stack.top().second)
                    {
                        glColor3f(1, 1, 0);
                    }
                    else if (map[y * mazeWidth + x] == 1)
                        glColor3f(1, 0, 0);
                    else
                        glColor3f(0, 0, 1);
                    
                    glBegin(GL_QUADS);
                    glVertex2i(xo + 1, yo + 1);
                    glVertex2i(xo + 1, yo + mapOffeset - 1);
                    glVertex2i(xo + mapOffeset - 1, yo + mapOffeset - 1);
                    glVertex2i(xo + mapOffeset - 1, yo + 1);
                    glEnd();
                }
            }
            
        }
        
        else
        {
            drawMenu(window);
        }
        
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
