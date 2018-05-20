//
//  main.cpp
//  DunhamDarryl_project03
//
//  Created by Darryl Dunham on 4/9/18.
//  Copyright © 2018 Darryl Dunham. All rights reserved.
//
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <unistd.h>
#include <chrono>
#include <fstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;
using namespace std::chrono;

void keyboard(unsigned char key, int x, int y);
// ********** Global variables *************
int dancer = 0;
double hipX = 0.1;
double direction = 0.1;
double leftRotate = 0;
double leftReverse = 5;
double rightRotate = -60;
double rightReverse = 5;
double randomR = ((rand()%99)+1)*0.01; // generates random number for the color red
double randomG = ((rand()%99)+1)*0.01; // generates random number for the color green
double randomB = ((rand()%99)+1)*0.01; // generates random number for the color blue
int yes = 0;
static int year = 0;
high_resolution_clock::time_point drawTime;

// ****** Function Prototypes ****************
void intructions();
void init(void) ;
void display(void);
void reshape (int w, int h);
void keyboard (unsigned char key, int x, int y);
void lights(void);
void stickFigure(void);
void renderbitmap(float x, float y, void *font, char *string);

// ******** Main routine ***************************
/*
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
int main(int argc, char** argv)
{
    intructions();
    drawTime = high_resolution_clock::now();
    // Initialize GLUT
    // Allow cmd line arguments to be passed to the glut
    glutInit(&argc, argv);
    // Using double buffer for animation
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    // GLUT Window Initialization
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    //glutCreateWindow (argv[0]);
    glutCreateWindow ("Disco Fever!");
    // Initialize OpenGL graphics state
    init ();
    
    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPostRedisplay();
    glutIdleFunc(lights);
    glutKeyboardFunc(keyboard);
    
    // Turn the flow of control over to GLUT and enter the main event loop
    glutMainLoop();

    return 0;
}

void intructions()              // print to concolse to show control instructions
{
    cout << "Press the space bar for a special suprise!" << endl;
    cout << "Press enter to end special surpise" << endl;
    cout << "Press esc to end program" << endl;
    cout << "Press c to make billy dance in multi-funky-colors!" << endl;
    cout << "Press v to make billy normal" << endl;
}

void lights (void)
{
    duration<double, std::milli> lappedTime = (high_resolution_clock::now()- drawTime); // timer that tracks milli seconds
    
    if (lappedTime.count() > 100)
    {
        drawTime = high_resolution_clock::now(); // get active clock
        
        randomR = ((rand()%99)+1)*0.01; // generates random number for the color red
        randomG = ((rand()%99)+1)*0.01; // generates random number for the color green
        randomB = ((rand()%99)+1)*0.01; // generates random number for the color blue
        
        year = (year + 2) % 360;           // the rate at which the lights spin around the disco ball
    }
    rightRotate = rightRotate + rightReverse;   // movement of right arm
    if (rightRotate < -100)                     // when the right arm reaches max point to the left, switch directions
    {
        rightReverse = 6.5;
    }
    if (rightRotate > 35)                       // when the right arm reaches max point to the right, switch directions
    {
        rightReverse = -6.5;
    }
    
    leftRotate = leftRotate + leftReverse;  // movement of left arm
    if (leftRotate < -35)                   // when the left arm reaches max point to the left, switch directions
    {
        leftReverse = 6.5;
    }
    if (leftRotate > 100)                   // when the left arm reaches max point to the right, switch directions
    {
        leftReverse = -6.5;
    }
    
    hipX = hipX + direction;    // movement of hips
    if (hipX < -0.1)            // when hips reach max point on the left, switch directions
    {
        direction = 0.02;
    }
    if (hipX > 0.1)             // when hips reach max point on the right, switch directions
    {
        direction = -0.02;
    }
    glutPostRedisplay();
}

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void display(void)
{
    int numP = 15;      // set number of disco lights to be drawn
    
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
        glBegin (GL_LINES);             // draw line for disco ball
            glColor3f (1.0, 1.0, 1.0);  // set color to white
            glVertex2i (0, 2);
            glVertex2i (0, 5);
        glEnd();                        // end drawing
    
        glLineWidth(50.0);              // change the with of pole for disco ball

        glTranslatef(0.0,1.5,0.0);                  // translate disco ball
        glColor3f (randomR, randomG, randomB);      // set color to be random
        glutSolidSphere(1.0, 20, 16);               // draw disco ball
        glTranslatef(0.0,-3.0,0.0);                 // translate the disco ball back
        glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);  // rotate disco lights about the y - axis
    
        for (int j = 0; j <= 360; j+=15)
        {
            glRotatef ((GLfloat) 15, 0.0, 1.0, 0.0);    // rotate 15 degrees
        
            for (int i = 0; i < numP; i++)      // for loop that makes numP of disco lights
            {
                glPushMatrix();
                    double theta = (2*3.14*i)/numP;                     // theta for translate function
                    glTranslatef ((5*cos(theta)), (5*sin(theta)), 0.0); // translate in a circular motion for each disco light
                    glutSolidSphere(0.1, 2, 2);                         // Draw a disco lights
                glPopMatrix();
            }
        }
    glPopMatrix();
    
    glPushMatrix();
        if (dancer == 1)
        {
            if (yes == 1)
                glColor3f (randomR, randomG, randomB);                        // set color to lights
            if (yes == 0)
                glColor3f (1,1,1);

             glBegin (GL_LINES);                        // draw main body.
                glVertex2f (0.0, -1.0);
                glVertex2f (hipX, -2.0);
            glEnd();                                    // end drawing

            glBegin (GL_LINES);                         // draw left leg
                glVertex2f (hipX, -2.);
                glVertex2f (-0.5, -2.75);
            glEnd();                                    // end drawing
 
            glBegin (GL_LINES);                         // draw right leg
                glVertex2f (hipX, -2.0);
                glVertex2f (0.5, -2.75);
            glEnd();                                    // end drawing
        
            glPushMatrix();                             // left arm push
                glTranslated(0.0, -1.3, 0.0);           // translate left arm rotating point
                glRotated(leftRotate, 0.0, 0.0, 1.0);   // rotate arm around translated point
                glTranslated(0.0, 1.3, 0.0);            // translate the point back to normal
                glBegin (GL_LINES);                     // draw left arm
                    glVertex2f (0.0, -1.3);
                    glVertex2f (-0.2, -2.0);
                glEnd();                                // end drawing
            glPopMatrix();                              // left arm pop
        
            glPushMatrix();                             // right arm push
                glTranslated(0.0, -1.3, 0.0);           // translate right arm rotating point
                glRotated(rightRotate, 0.0, 0.0, 1.0);  // rotate arm around translated point
                glTranslated(0.0, 1.3, 0.0);            // translate the point back to normal
                glBegin (GL_LINES);                     // draw right arm
                    glVertex2f (0.0, -1.3);
                    glVertex2f (0.2, -2.0);
                glEnd();                                // end drawing
            glPopMatrix();                              // right arm pop
        
            glTranslatef(0.0,-1.0,0.0);                 // set position for head of stick figure
            glutSolidSphere(0.4, 50, 5);                // draw 3D sphrere
            
            char text[10] = {0};
            
            sprintf(text,"Billy");
            renderbitmap(-0.1,0.5,GLUT_BITMAP_TIMES_ROMAN_10,text);
        }
    glPopMatrix();
    glutSwapBuffers();
}

void renderbitmap(float x, float y, void *font, char *string)
{
    char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// keyboard functions
void keyboard(unsigned char key, int x, int y)
{
    // space bar
    switch (key)
    {
        case 32:
            dancer = 1;
            break;
    }
    
    // enter key
    switch (key)
    {
        case 13:
            dancer = 0;
            break;
    }
    
    // esc key
    switch (key)
    {
        case 27:
            exit(0);
            break;
    }
    
    // speed up key
    switch(key)
    {
        case 'f':
            break;
    }
    
    // slow down key
    switch (key)
    {
        case 's':
            break;
    }
    
    // change color of bill to disco lights
    switch (key)
    {
        case 'c':
            yes = 1;
            break;
    }
    
    // change color of bill to normal
    switch (key)
    {
        case 'v':
            yes = 0;
            break;
    }
    
}
