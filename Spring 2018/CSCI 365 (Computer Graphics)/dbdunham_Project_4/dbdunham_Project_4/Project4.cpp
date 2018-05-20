//
//  main.cpp
//  DunhamDarryl_project03
//
//  Created by Darryl Dunham on 4/15/18.
//  Copyright © 2018 Darryl Dunham. All rights reserved.
//

/*  CSCI B365 Project04 starting code */
// This sample code can be of our reference or starting code.
// Students must modify the documentation and add more detailed comments if this code is used.
// ******** Students do NOT have to use this sample code. ***********

/*
 Please outout the following information to the C++ window console
 keyboard controls:
 Space Bar:    Toggle Animation
 r/R:    Reset the scene to its initial status.
 s/S:    Positive/negative shoulder rotation about Z axis.
 e/E:    Positive/negative elbow rotation about Z axis.
 O/C:    Open/Close the hand
 
 x/X:    Positive/negative X-axis shift of the robot.
 y/Y:    Positive/negative Y-axis shift of the robot.
 z/Z:    Positive/negative robot rotation about Z-axis.
 UP/DOWN ARROWS:    (zoom in/out) Z-axis shift of the robot.
 
 LEFT/RIGHT ARROWS:    Y-axis rotations of the robot.
 PAGE UP/DOWN:    X-axis rotations of the robot.
 ESC:    exit
 */
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

#define ESC 27

// ************ Globals *************************
static GLfloat red[]={1,0,0},green[]={0,1,0}, blue[] = {0,0,1}, cyan[] = {0,1,1};
static int shoulder=0,elbow=0, finger=0;
static int xrot=0,yrot=0,zrot=0,armRot=0,handsRot=0, shoulderRot=0,animationCount=0, bodyRot=0;;
static GLfloat xshift=0.0,yshift=0.0,zoom=-3.0;
static double animationX=0, animationY=0, animationZ=0;
static bool animationToggle = false;


// ************** Function Prototypes ************
void printInteraction(void);
void init();
void myDisplay();
void reshape(int w, int h);
void myKeyboard(unsigned char key, int x, int y);
void mySpecialKeys(int key, int x, int y);
void animation();

// ******** Main routine ***************************
// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv)
{
    int winWidth = 800, winHeight = 600, winPosX = 100, winPosY = 100; // OpenGL window
    
    // Print user instructions for controls
    printInteraction();
    
    // Initialize GLUT.
    // Allow cmd line arguments to be passed to the glut
    glutInit(&argc,argv);
    
    // Set display mode as double-buffered and RGB color.
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    
    // GLUT Window Initialization:
    glutInitWindowSize(800,600);    // Set OpenGL window size.
    glutInitWindowPosition(100,100);
    glutCreateWindow("CSCI B365 - Project04");
    
    // Initialize OpenGL graphics state
    init();
    
    // Register callbacks:
    glutDisplayFunc(myDisplay);    // Register display routine.
    glutReshapeFunc(reshape);        // Register reshape routine.
    glutKeyboardFunc(myKeyboard);            // Register keyboard routine.
    glutSpecialFunc(mySpecialKeys);    // Begin processing.
    
    glutMainLoop();
    
    return 0;
}


// ************* Function implementations ****************
// Routine to output interaction instructions to the C++ window.
// please implement this function
void printInteraction(void)
{
    cout << "Instructions ..."<<endl;
    cout << "Press space bar to start/stop animation..." << endl;
    cout << "Press the up or down arrow key to zoom in or out..." << endl;
    cout << "Press (fn + up or fn + down)/(Page up or Page down) to rotate forward or back..." << endl;
    cout << "Press the left or right arrow key to rotate to the left or right..." << endl;
    cout << "r/R Reset the scene to its initial status..." << endl;
    cout << "s/S Positive/negative shoulder rotation about Z axis..." << endl;
    cout << "e/E Positive/negative elbow rotation about Z axis..." << endl;
    cout << "o/O Open/Close the fingers..." << endl;
    cout << "c/C Close the fingers..." << endl;
    cout << "x/X Positive/negative X axis shift of the robot..." << endl;
    cout << "y/Y Positive/negative Y axis shift of the robot..." << endl;
    cout << "z/Z Positive/negative robot roatation about Z axis... " << endl;
    
}

/* some basic GL initialization */
void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
}

// Display call back routine
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0,0.0,-20.0);                          // set camera back -20
    glPushMatrix();                                       // push matrix for the whole robot
        glTranslatef(xshift,yshift,zoom);                 // translate function to whole robot
        glRotatef((GLfloat)xrot,1.0,0.0,0.0);             // rotate function for x axis
        glRotatef((GLfloat)yrot,0.0,1.0,0.0);             // rotate function for y axis
        glRotatef((GLfloat)zrot,0.0,0.0,1.0);             // rotate function for z axis
    
                                                          // Chest of robot
        glPushMatrix();                                   // Push matrix chest
            glRotatef((GLfloat)bodyRot,0.0,1.0,0.0);      // Rotate the check about the y axis
            glColor3fv(cyan);                             // color the chest of the robot
                glPushMatrix();                           // push matrix to draw chest
                    glScalef(4.0,4.0,1.0);                // scaling of chest
                    glutSolidCube(1.0);                   // draws chest
                glPopMatrix();                            // pop matrix to draw chest
        glPopMatrix();                                    // pop matrix for chest
    
                                                          // Head of robot
        glPushMatrix();                                   // push matrix for the head of the robot
            glTranslated(0.0, animationY+3.0, 0.0);       // translate function for head
            glColor3fv(red);                              // color the head of the robot
            glPushMatrix();                               // push matrix to draw head
                glScalef(2.0,2.0,1.0);                    // scale head of robot
                glutSolidCube(1.0);                       // draw head
            glPopMatrix();                                // pop matrix to draw head
        glPopMatrix();                                    // pop matrix for head of robot
    
                                                          // Right arm
        glPushMatrix();                                   // push matrix for right arm
            glTranslatef(2.0,1.75,0.0);                   // translate function to the right arm
            glRotatef((GLfloat)-shoulderRot,0.0,0.0,1.0); // rotate function of the right arm shoulder on z axis
            glTranslatef(animationX+1.0,0,0.0);           // translate function of right arm shoulder
            glColor3fv(red);                              // color of the right arm shoulde
            glPushMatrix();                               // push matrix to draw right arm shoulder
                glScalef(2.0,0.4,1.0);                    // scale right arm shoulder
                glutSolidCube(1.0);                       // draw right arm shoulder
            glPopMatrix();                                // pop matrix to draw right arm shoulder
    
                                                          // Elbow of right elbow
            glColor3fv(green);                            // color of right elbow
            glTranslatef(1.0,0.0,0.0);                    // translate function to the right elbow
            glRotatef((GLfloat)armRot,0.0,0.0,1.0);       // rotate right elbow along the z axis
            glTranslatef(animationX+1.0,0.0,0.0);         // translate function of the right elbow
            glPushMatrix();                               // push matrix of right elbow
                glScalef(2.0,0.4,1.0);                    // scaling the right elbow
                glutSolidCube(1.0);                       // draw right elbow
            glPopMatrix();                                // pop matrix for right elbow
    
                                                          // draw top finger
            glPushMatrix();                               // push matrix to top finger
                glColor3fv(blue);                         // color finger
                glTranslatef(0.75,0.1,0.0);               // translate top finger
                glRotatef((GLfloat)handsRot,0.0,0.0,1.0); // rotate function to top finger
                glTranslatef(animationX+0.75,0,0.0);      // translate the top finger
                glScalef(1,0.1,0.1);                      // scale top finger
                glutSolidCube(1.0);                       // draw top finger
            glPopMatrix();                                // pop matrix for top finger
    
                                                          // draw bottom finger
            glPushMatrix();                               // push matrix to the bottom finger
                glColor3fv(blue);                         // color bottom finger
                glTranslatef(0.75,-0.1,0.0);              // translate bottom finger
                glRotatef((GLfloat)-handsRot,0.0,0.0,1.0);// rotate function to bottom finger
                glTranslatef(animationX+0.75,0,0.0);      // translate bottom finger
                glScalef(1,0.1,0.1);                      // scale the finger
                glutSolidCube(1.0);                       // draws the finger
            glPopMatrix();                                // pop matrix of bottom finger
        glPopMatrix();                                    // pop matrix of right arm
    
                                                          // Left Arm
        glPushMatrix();                                   // push matrix for left arm
            glTranslated(-2, 1.75, 0);                    // translate function for left arm
            glRotatef((GLfloat)shoulderRot,0.0,0.0,1.0);  // rotate function for left arm
            glTranslated(-animationX-1, 0, 0);            // translate left arm
            glColor3fv(red);                              // color left shoulder
            glPushMatrix();                               // push matrix for left shoulder
                glScalef(2.0,0.4,1.0);                    // scale left shoulder
                glutSolidCube(1.0);                       // draw left shoulder
            glPopMatrix();                                // pop left shoulder
    
                                                          // left elbow
            glColor3fv(green);                            // color left elbow
            glTranslatef(-1.0,0.0,0.0);                   // translate left elbow
            glRotatef((GLfloat)-armRot,0.0,0.0,1.0);      // rotate left elbow
            glTranslatef(-animationX-1.0,0.0,0.0);        // translate left elbow
            glPushMatrix();                               // push matrix of left albow
                glScalef(2.0,0.4,1.0);                    // scale left elbow
                glutSolidCube(1.0);                       // draw left elbow
            glPopMatrix();                                // pop matrix of left elbow
    
                                                          // left top finger
            glPushMatrix();                               // push matrix for left top finger
                glColor3fv(blue);                         // color left top finger
                glTranslatef(-0.75,-0.1,0.0);             // translate the top finger
                glRotatef((GLfloat)-handsRot,0.0,0.0,1.0);// rotate the left top finger
                glTranslatef(-animationX-0.75,0.1,0.0);   // translate the top finger
                glScalef(1,0.1,0.1);                      // scale left top finger
                glutSolidCube(1.0);                       // draw left top finger
            glPopMatrix();                                // pop matrix for left top finger
    
                                                          // left bottom finger
            glPushMatrix();                               // push matrix for bottom finger
                glColor3fv(blue);                         // color left bottom finger
                glTranslatef(-0.75,-0.1,0.0);             // translate left bottom finger
                glRotatef((GLfloat)handsRot,0.0,0.0,1.0); // rotate left bottom finger
                glTranslatef(-animationX-0.75,-0.1,0.0);  // translate left bottom finger
                glScalef(1,0.1,0.1);                      // scale left bottom finger
                glutSolidCube(1.0);                       // draw left bottom finger
            glPopMatrix();                                // pop matrix for left bottom finger
        glPopMatrix();                                    // pop matrix for left arm
    
                                                          // Right leg
        glPushMatrix();                                   // push matrix for right top half leg
            glTranslatef(1.75,-animationY-3,0.0);         // translate right top half leg
            glRotatef((GLfloat)90,0.0,0.0,1.0);           // rotate right top half leg
            glColor3fv(green);                            // color right top half leg
            glPushMatrix();                               // push matrix for right top half of leg
                glScalef(2.0,0.4,1.0);                    // sclae right top half of leg
                glutSolidCube(1.0);                       // draw right top half of leg
            glPopMatrix();                                // pop right top half of leg matrix
    
                                                          // right bottom half of leg
            glColor3fv(red);                              // right bottom half og leg
            glTranslatef(-2.0-animationY,0.0,0.0);        // translate right bottom half of leg
            glPushMatrix();                               // push matrix for right bottom half of leg
                glScalef(2.0,0.4,1.0);                    // scale bottom half of leg
                glutSolidCube(1.0);                       // draw bottom half of leg
            glPopMatrix();                                // pop matrix for bottom half of leg
    
                                                          // right foot
            glPushMatrix();                               // push matrix of right foot
                glColor3fv(blue);                         // color right foot
                glTranslatef(-animationY-1,0.0,0.5);      // translate right foot
                glScalef(0.4,1,2.0);                      // scale right foot
                glutSolidCube(1.0);                       // draw right foot
            glPopMatrix();                                // pop matrix for right foot
        glPopMatrix();                                    // pop matrix for the right leg
    
                                                          // Left leg
        glPushMatrix();                                   // push matrix for left top half leg
            glTranslated(-1.75, -animationY-3, 0);        // translate function for left top half leg
            glRotatef((GLfloat)90,0.0,0.0,1.0);           // rotate function for left top half leg
            glColor3fv(green);                            // color left top half leg
            glPushMatrix();                               // push matrix for left top half leg
                glScalef(2.0,0.4,1.0);                    // slace left top half leg
                glutSolidCube(1.0);                       // draw left top half leg
            glPopMatrix();                                // pop matrix for left top half leg
    
                                                          // left bottom half of leg
            glColor3fv(red);                              // color left bottom half of leg
            glTranslatef(-animationY-2.0, 0, 0.0);        // translate left bottom half of leg
            glPushMatrix();                               // push matrix for left bottom half of leg
                glScalef(2.0,0.4,1.0);                    // scale left bottom half of leg
                glutSolidCube(1.0);                       // draw left bottom half of leg
            glPopMatrix();                                // pop matrix for left bottom half of leg
    
                                                          // left foot
            glPushMatrix();                               // push matrix for left foot
                glColor3fv(blue);                         // color left foot
                glTranslatef(-animationY-1,0,0.5);        // translate left foot
                glScalef(0.4,1,2.0);                      // scale left foot
                glutSolidCube(1.0);                       // draw left foot
            glPopMatrix();                                // pop for left foot
        glPopMatrix();                                    // pop for left leg
    glPopMatrix();                                        // pop for whole robot body
    glutSwapBuffers();
} // end display function

void animation()                        // animation function that controls movements
{
    if (animationCount < 50)            // if statement to move in positive direction
    {
        animationX+=0.1;                // moves parts in the x direction
        animationY+=0.1;                // moves parts in the y direction
        zoom-=0.1;                      // zooms away
        armRot+=10;                     // rotates arm
        shoulderRot-=5;                 // rotates shoulder
        bodyRot+=5;                     // roates the body of the robot
        glutPostRedisplay();            // redisplay the robot
        animationCount++;               // function counter
    }
    else if (animationCount >= 50       // if else statement to reverse the directions of each movement
             && animationCount < 100)
    {
        animationX-=0.1;                // moves parts in the x direction
        animationY-=0.1;                // moves parts in the y direction
        zoom+=0.1;                      // zooms away
        armRot-=10;                     // rotates arm
        shoulderRot+=5;                 // rotates shoulder
        bodyRot-=5;                     // roates the body of the robot
        glutPostRedisplay();            // redisplay the robot
        animationCount++;               // function counter
    }
}
/* the window-reshape callback */
void reshape(int w, int h)
{
    GLfloat myFov = 65.0, myNear = 1.0, myFar = 30.0;
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Projection
    gluPerspective(myFov,(GLfloat)w/(GLfloat)h, myNear, myFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* The basic keyboard controls, callback for glutKeyboardFunc() */
void myKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case ESC:                       // exit program
            exit(0);
            break;
        case 'e':                       // elbow
            if (armRot < 135)
            {
                armRot+=5;
                glutPostRedisplay();
            }
            break;
        case 'E':                       // elbow
            if (armRot > 0)
            {
                armRot-=5;
                glutPostRedisplay();
            }
            break;
        case 'o':                       // open hand
        case 'O':
            if (handsRot < 45)
            {
                handsRot+=5;
                glutPostRedisplay();
            }
            break;
        case 'c':                       // close hand
        case 'C':
            if (handsRot > 0)
            {
                handsRot-=5;
                glutPostRedisplay();
            }
            break;
        case 's':                       // shoulder
            if (shoulderRot < 85)
            {
                shoulderRot+=5;
                glutPostRedisplay();
            }
            break;
        case 'S':                       // shoulder
            if (shoulderRot > -90)
            {
                shoulderRot-=5;
                glutPostRedisplay();
            }
            break;
        case 'x':                       // x translate
            xshift+=1;
            glutPostRedisplay();
            break;
        case 'X':                       // x translate
            xshift-=1;
            glutPostRedisplay();
            break;
        case 'y':                       // y translate
            yshift+=1;
            glutPostRedisplay();
            break;
        case 'Y':                       // y translate
            yshift-=1;
            glutPostRedisplay();
            break;
        case 'z':                       // z rotate
            zrot=(zrot+5)%360;
            glutPostRedisplay();
            break;
        case 'Z':                       // z rotate
            zrot=(zrot-5)%360;
            glutPostRedisplay();
            break;
        case 'r':                       // reset values
        case 'R':
            shoulderRot = 0;
            armRot = 0;
            handsRot = 0;
            xrot = 0;
            yrot = 0;
            zrot = 0;
            xshift = 0;
            yshift = 0;
            zoom = 0;
            glutPostRedisplay();
            break;
        case 32:                        // space bar for animation
            if (animationToggle)        // if animation is false
            {
                shoulderRot = 0;
                armRot = 0;
                handsRot = 0;
                xrot = 0;
                yrot = 0;
                zrot = 0;
                xshift = 0;
                yshift = 0;
                zoom = 0;
                animationX = 0;
                animationY = 0;
                animationZ = 0;
                glutIdleFunc(NULL);
                glutPostRedisplay();
            }
            else                        // else animation true
            {
                glutIdleFunc(animation);
                glutPostRedisplay();
                animationCount = 0;
            }
            animationToggle = !animationToggle;
            break;
        default:
            break;
    }
}

/* The "special" keyboard controls, callback for glutSpecialFunc() */
void mySpecialKeys(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:               // zoom
            zoom+=1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:             // zoom
            zoom-=1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:             // rotate y axis
            yrot=(yrot+5)%360;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:            // rotate y axis
            yrot=(yrot-5)%360;
            glutPostRedisplay();
            break;
        case GLUT_KEY_PAGE_UP:          // rotate x axis
            xrot=(xrot-5)%360;
            glutPostRedisplay();
            break;
        case GLUT_KEY_PAGE_DOWN:        // rotate x axis
            xrot=(xrot+5)%360;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}
