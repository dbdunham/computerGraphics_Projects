//
//  main.cpp
//  dbdunham_Project_5
//
//  Created by Darryl Dunham Jr on 4/24/18.
//  Copyright © 2018 Darryl Dunham Jr. All rights reserved.
//

//*******************************************************************************
//
//  File Name    : Project05_startingCode.cpp
//  Author        : Xuwei Liang
//
//  Description    : To display a teapot in multiple views.
//                This is a starting code for a project
//                Students are expected to add functionalities to this template.
//
//  Note        : This starting code is only a suggestion of your code structure.
//                Students do NOT have to use it.
//******************************************************************************

// Include necessary headers if needed
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

// Represents gaps between subwindows
#define GAP  25
#define SUBWINDOW_WIDTH 200
#define SUBWINDOW_HEIGHT 200
#define NUMBER_OF_ROWS 2
#define NUMBER_OF_COLS 3

// ******** Globals *******************************************
//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13,
//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10,
//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
//  You can use whatever fonts you want
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

// Define the window position on screen
int window_x;
int window_y;

// Variables representing the main window size
int window_width = SUBWINDOW_WIDTH * NUMBER_OF_COLS + (NUMBER_OF_COLS + 1) * GAP;
int window_height = SUBWINDOW_HEIGHT*NUMBER_OF_ROWS + (NUMBER_OF_ROWS + 1) * GAP;

// Variable representing the main window title
char *window_title = "CSCI B365 Project demo";

// IDs of main windows and 6 subwindows
int main_window, subwindow_1, subwindow_2, subwindow_3, subwindow_4, subwindow_5, subwindow_6;

//  is true if the corresponding button is clicked, and false otherwise
bool leftButton = false;
bool rightButton = false;
bool middleButton = false;

// Variables for translating, scaling, and rotating objects in the scene
float rot_x = 0.0f, rot_y = 0.0f, rot_z = 0.0f;
float previousX = 0.0f, previousY = 0.0f, previousZ = 0.0f;
float scale_x = 1.0f, scale_y = 1.0f, scale_z = 1.0f;
float translate_x = 0.0f, translate_y = 0.0f, translate_z = 0.0f;

// Camera position, look at center, up vector
double eyeX = 0, eyeY = 0, eyeZ = 0;
double centerX = 0, centerY = 0, centerZ = 0;
double upX = 0, upY = 1, upZ = 0;

// Subwindow's position and size variables
float subwindow1_x;
float subwindow1_y;
float subwindow1_w = SUBWINDOW_WIDTH;
float subwindow1_h = SUBWINDOW_HEIGHT;

float subwindow2_x;
float subwindow2_y;
float subwindow2_w = SUBWINDOW_WIDTH;
float subwindow2_h = SUBWINDOW_HEIGHT;

float subwindow3_x;
float subwindow3_y;
float subwindow3_w = SUBWINDOW_WIDTH;
float subwindow3_h = SUBWINDOW_HEIGHT;

float subwindow4_x;
float subwindow4_y;
float subwindow4_w = SUBWINDOW_WIDTH;
float subwindow4_h = SUBWINDOW_HEIGHT;

float subwindow5_x;
float subwindow5_y;
float subwindow5_w = SUBWINDOW_WIDTH;
float subwindow5_h = SUBWINDOW_HEIGHT;

float subwindow6_x;
float subwindow6_y;
float subwindow6_w = SUBWINDOW_WIDTH;
float subwindow6_h = SUBWINDOW_HEIGHT;

// ********* Function prototypes ******************************
// Main Window callback functions
void main_display (void);
void main_reshape (int w, int h);
// The "keyboard" call back routine is shared by the main window and 6 subwindows
void keyboard (unsigned char key, int x, int y);

// SubWindows display call back functions
void display1 (void);
void display2 (void);
void display3 (void);
void display4 (void);
void display5 (void);
void display6 (void);

void display (int id);
void redisplayAll ();  // Re-display all 6 sub-windows

// Other callback routines
// 6 subwindows share the same 2 call back routines below.
void mouse (int, int, int, int);
void motion (int, int);

// Support Functions
void outputInteractions();
void reset();  // When the user click 'r' or 'R' the object will be its initial status
void centerOnScreen();
void drawObject();
void labels(int id);    // labels
//  Print function to print fonts to window
void printw (float x, float y, float z, char* format);

/////////////////////////////////////////
// Add more prototypes if necessary   ///
/////////////////////////////////////////


//-------------------------------------------------------------------------
//  Program Main method.
//-------------------------------------------------------------------------
int main (int argc, char **argv)
{
    outputInteractions();    // Output instructions about user interaction
    glutInit(&argc, argv);    // Connect to the windowing system
    
    // Set Display mode
    glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
    
    // ****** 1. Create and set a main window **********************//
    glutInitWindowSize (window_width, window_height);
    centerOnScreen();        // Set the window x and y coordinates such that the
    //   main window becomes centered
    glutInitWindowPosition (window_x, window_y);        // Position main Window
    main_window = glutCreateWindow (window_title);        // Create the main window with the specified title
    //cout << "The value of main_window = "<< main_window<<endl;
    
    // Set the callback functions for main window
    // Each created window has a unique associated OpenGL context,
    //   i.e., a set of call back functions to handle events.
    glutDisplayFunc (main_display);
    glutReshapeFunc  (main_reshape);
    glutKeyboardFunc (keyboard);  //shared with 6 subwindows
    
    // ****** 2. Create and set first subwindow *************************//
    subwindow_1 = glutCreateSubWindow (main_window, GAP, GAP, subwindow1_w, subwindow1_h);
    //cout << "The subwindow_1 = " << subwindow_1 << endl;
    // Each created window has a unique associated OpenGL context,
    //   i.e., a set of call back functions to handle events.
    glutDisplayFunc (display1);
    glutMouseFunc (mouse);       //shared with other subwindows
    glutMotionFunc (motion);     //shared with other subwindows
    glutKeyboardFunc (keyboard); //shared with other subwindows
    
    // ****** 2. Create and set second subwindow ********************//
    subwindow_2 = glutCreateSubWindow (main_window, SUBWINDOW_WIDTH + GAP*2, GAP, subwindow2_w, subwindow2_h);
    //cout << "The subwindow_2 = " << subwindow_2 << endl;
    // Each created window has a unique associated OpenGL context,
    //   i.e., a set of call back functions to handle events.
    glutDisplayFunc (display2);
    glutMouseFunc (mouse);       //shared with other subwindows
    glutMotionFunc (motion);     //shared with other subwindows
    glutKeyboardFunc (keyboard); //shared with other subwindows
    
    // ****** 2. Create and set third subwindow ********************//
    subwindow_3 = glutCreateSubWindow (main_window, 400 + GAP*3, GAP, subwindow3_w, subwindow3_h);
    //cout << "The subwindow_3 = " << subwindow_3 << endl;
    // Each created window has a unique associated OpenGL context,
    //   i.e., a set of call back functions to handle events.
    glutDisplayFunc (display3);
    glutMouseFunc (mouse);       //shared with other subwindows
    glutMotionFunc (motion);     //shared with other subwindows
    glutKeyboardFunc (keyboard); //shared with other subwindows
    
    // ****** 2. Create and set forth subwindow ********************//
    subwindow_4 = glutCreateSubWindow (main_window, GAP, 200 + GAP*2, subwindow4_w, subwindow4_h);
    //cout << "The subwindow_4 = " << subwindow_4 << endl;
    // Each created window has a unique associated OpenGL context,
    //   i.e., a set of call back functions to handle events.
    glutDisplayFunc (display4);
    glutMouseFunc (mouse);       //shared with other subwindows
    glutMotionFunc (motion);     //shared with other subwindows
    glutKeyboardFunc (keyboard); //shared with other subwindows
    
    // ****** 2. Create and set fifth subwindow ********************//
    subwindow_5 = glutCreateSubWindow (main_window, SUBWINDOW_WIDTH + GAP*2, 200 + GAP*2, subwindow5_w, subwindow5_h);
    //cout << "The subwindow_5 = " << subwindow_5 << endl;
    // Each created window has a unique associated OpenGL context,
    //   i.e., a set of call back functions to handle events.
    glutDisplayFunc (display5);
    glutMouseFunc (mouse);       //shared with other subwindows
    glutMotionFunc (motion);     //shared with other subwindows
    glutKeyboardFunc (keyboard); //shared with other subwindows
    
    // ****** 2. Create and set sixth subwindow ********************//
    subwindow_6 = glutCreateSubWindow (main_window, 400 + GAP*3, 200 + GAP*2, subwindow6_w, subwindow6_h);
    //cout << "The subwindow_6 = " << subwindow_6 << endl;
    // Each created window has a unique associated OpenGL context,
    //   i.e., a set of call back functions to handle events.
    glutDisplayFunc (display6);
    glutMouseFunc (mouse);       //shared with other subwindows
    glutMotionFunc (motion);     //shared with other subwindows
    glutKeyboardFunc (keyboard); //shared with other subwindows
    
    // Start GLUT event processing loop
    glutMainLoop();
    return 0;
}


// ********* Function Implementations *********************
// Output instructions about user interaction as before
void outputInteractions()
{
    cout << "Interactions:" << endl;
    cout << "  Press and drag right mouse button to translate." << endl
    << "  Press and drag middle mouse button to scale." << endl
    << "  Press and drag left mouse button to rotate." << endl
    << "  Press space bar to start/stop the animation." << endl
    << "  Press 'r' or 'R' to reset the scene." << endl
    << "  Press Esc to exit." << endl;
}

// Reset all transformation parameters
void reset()
{
    // Reset all relevant variables to their initial values so that hte object will
    //   its initial status
    rot_x = 0.0f;
    rot_y = 0.0f;
    rot_z = 0.0f;
    previousX = 0.0f;
    previousY = 0.0f;
    previousZ = 0.0f;
    
    eyeX = 0;
    eyeY = 0;
    eyeZ = 0;
    centerX = 0;
    centerY = 0;
    centerZ = 0;
    upX = 0;
    upY = 1;
    upZ = 0;
    
    translate_x = 0.0f;
    translate_y = 0.0f;
    translate_z = 0.0f;
    
    scale_x = 1.0f;
    scale_y = 1.0f;
    scale_z = 1.0f;
    
    // Last step - re-display all 6 sub-windows
    redisplayAll();
}

//-------------------------------------------------------------------------
//  Main Window Display Function
//-------------------------------------------------------------------------
void main_display (void)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glutSwapBuffers();
}

//-------------------------------------------------------------------------
//  Main window reshape function
//-------------------------------------------------------------------------
void main_reshape (int w, int h)
{
    // Disallow window re-sizing
    glutReshapeWindow (window_width, window_height);
}

//-------------------------------------------------------------------------
//  keyboard control call back function
//-------------------------------------------------------------------------
void keyboard (unsigned char key, int x, int y)
{
    // Press 'r' or 'R' key to reset object transformations in the scene
    // ‘Esc’ to quit the program
    switch(key)
    {
        case 'r':
        case 'R':
            reset();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

//-------------------------------------------------------------------------
// Input: An integer subwindowId representing a subwindow.
// Output: None
// Process:
//   Call display on the subwindow with the passed ID.
//   It will display the object from a different angle according the the ID for subwindows.
//-------------------------------------------------------------------------
void display (int subwindowId)
{
    // Clear subwindow
    glClearColor(1, 1, 1, 1);
    glClear (GL_COLOR_BUFFER_BIT);
    
    // Set Perspective projection
    glMatrixMode (GL_PROJECTION); // Make the projection matrix stack current
    glOrtho(-1, 1, -1, 1, -2, 2);
    
    // Set camera's position, viewing direction, and up vector
    glMatrixMode (GL_MODELVIEW);  // Make the modelview matrix stack current
    gluLookAt (eyeX, eyeY, eyeZ,
               centerX, centerY, centerZ,
               upX, upY, upZ);
    
    // Apply required translation, rotation, and scaling
    
    // Apply translations
    glTranslatef(translate_x, translate_y, translate_z);
    
    // apply rotations
    glRotatef (rot_x, 1.0f, 0.0f, 0.0f);
    glRotatef (rot_y, 0.0f, 1.0f, 0.0f);
    glRotatef (rot_z, 0.0f, 0.0f, 1.0f);
    
    // Apply scalings
    glScalef(scale_x, scale_y, scale_z);
    
    // Draw the teapot and apply all the above transformations to it
    drawObject ();
    
    
    // *** The following initialization makes the label not being transformed when we transform the object, i.e.,
    //     to isolate the labe from any transformation.
    glLoadIdentity ();             // Make the current ModelView matrix an identity matrix
    glMatrixMode (GL_PROJECTION);  // Make the projection matrix stack current
    glLoadIdentity ();             // Make the projection matrix an identity matrix
    
    // Label each subwindow
    labels(subwindowId);
    
    glutSwapBuffers ();
}

// Input: An integer "subwindowId" representing a subwindow
// Output: None
// Process: Label a subwindow according to the subwindows "subwindowId"
void labels(int subwindowId)
{
    // Label the subwindow
    switch (subwindowId)
    {
            //  Front
        case 1:
            printw (-0.9, -0.9, 0, "Front");
            break;
            //  Top
        case 2:
            printw (-0.9, -0.9, 0, "Top");
            break;
            //  Left
        case 3:
            printw (-0.9, -0.9, 0, "Left");
            break;
            //  Back
        case 4:
            printw (-0.9, -0.9, 0, "Back");
            break;
            //  Bottom
        case 5:
            printw (-0.9, -0.9, 0, "Bottom");
            break;
            //  Right
        case 6:
            printw (-0.9, -0.9, 0, "Right");
            break;
           
    }
    
}
//-------------------------------------------------------------------------
// Display the "Front" subwindow - Modify this function if needed
//-------------------------------------------------------------------------
void display1 (void)
{
    // Set the object color
    glColor3f (1, 0, 0);
    
    // Set the camera for this subwindow
    eyeX = 0;
    eyeY = 0;
    eyeZ = 1;
    upX = 0;
    upY = 1;
    upZ = 0;
    
    // Display the object
    display (1);
}

//-------------------------------------------------------------------------
// Display the "Top" subwindow - Modify this function if needed
//-------------------------------------------------------------------------
void display2 (void)
{
    // Set the object color
    glColor3f (0, 1, 0);
    
    // Set the camera for this subwindow
    eyeX = 0;
    eyeY = 1;
    eyeZ = 0;
    upX = 0;
    upY = 0;
    upZ = -1;
    
    // Display the object
    display (2);
}

//-------------------------------------------------------------------------
// Display 3 "Left"
//-------------------------------------------------------------------------
void display3 (void)
{
    // Set the object color
    glColor3f (0, 0, 1);
    
    // Set the camera for this subwindow
    eyeX = 1;
    eyeY = 0;
    eyeZ = 0;
    upX = 0;
    upY = 1;
    upZ = 0;
    
    // Display the object
    display (3);
}

//-------------------------------------------------------------------------
// Display 4 "Back"
//-------------------------------------------------------------------------
void display4 (void)
{
    // Set the object color
    glColor3f (1, 0, 0);
    
    // Set the camera for this subwindow
    eyeX = 0;
    eyeY = 0;
    eyeZ = -1;
    upX = 0;
    upY = 1;
    upZ = 0;
    
    // Display the object
    display (4);
}

//-------------------------------------------------------------------------
// Display 5 "Bottom"
//-------------------------------------------------------------------------
void display5 (void)
{
    // Set the object color
    glColor3f (0, 1, 0);
    
    // Set the camera for this subwindow
    eyeX = 0;
    eyeY = -1;
    eyeZ = 0;
    upX = 0;
    upY = 0;
    upZ = 1;
    
    // Display the object
    display (5);
}

//-------------------------------------------------------------------------
// Display 6 "Right"
//-------------------------------------------------------------------------
void display6 (void)
{
    // Set the object color
    glColor3f (0, 0, 1);
    
    // Set the camera for this subwindow
    eyeX = -1;
    eyeY = 0;
    eyeZ = 0;
    upX = 0;
    upY = 1;
    upZ = 0;
    
    // Display the object
    display (6);
}

//-------------------------------------------------------------------------
//  Draw the object
//-------------------------------------------------------------------------
void drawObject ()
{
    // draw a teapot object
    glutWireTeapot (0.5);
}


// Students can combine the following 'mouse" and "motion" function if needed
// The two fucntions are only a suggestion of your code structure
//-------------------------------------------------------------------------
// Mouse function that lets the user rotate, or translate, or scale the object as required in the HW instruction
//-------------------------------------------------------------------------
void mouse (int button, int state, int x, int y)
{
    // checks if the user presses the left button
    if (button == GLUT_LEFT_BUTTON)
    {
        leftButton = state == GLUT_DOWN;
    }
    // checks if the user presses the right button
    else if(button == GLUT_RIGHT_BUTTON)
    {
        rightButton = state == GLUT_DOWN;
    }
    // checks if the user presses the middle button
    else if(button == GLUT_MIDDLE_BUTTON)
    {
        middleButton = state == GLUT_DOWN;
    }
    
    // Record the current mouse start position in the display window (on the screen)
    // We will use this start position in the motion() function
    //cout << "In fucntion mouse(): "<<endl;
    //cout << "  mouse position is (" << x <<", " << y << ")" << endl;
    previousX = x;
    previousY = y;
    previousZ = y;
}

//-------------------------------------------------------------------------
// Function used when the user is dragging the mouse
// When we drag the mouse, the (x, y) below is the mouse's end position at each stop.
//-------------------------------------------------------------------------
void motion (int x, int y)
{
    // Translation (right button)
    if(rightButton)
    {
        translate_x += (x - previousX) * 0.005;
        translate_y -= (y - previousY) * 0.005;
    }
    
    // scale (middle button)
    if(middleButton)
    {
        scale_x -= (y - previousY) * 0.005;
        scale_y -= (y - previousY) * 0.005;
        scale_z -= (y - previousY) * 0.005;
        //cout << "In function motion: "<<endl;
        //cout << "  mouse end position is (" << x <<", " << y << ")" << endl;
    }
    //  Rotate
    if (leftButton)
    {
        rot_x += y - previousY;
        rot_y += x - previousX;
    }
    
    // reset the previousX, previousY, and previousZ to the current position of the mouse
    previousX = x;
    previousY = y;
    previousZ = y;
    //cout << "In function motion: "<<endl;
    //cout << "  mouse start position is (" << x <<", " << y << ")" << endl;
    
    // Last step - re-display all 6 sub-windows
    redisplayAll ();
}

//-------------------------------------------------------------------------
// Redisplays all 6 subwindows
//-------------------------------------------------------------------------
void redisplayAll ()
{
    // re-display the 1st subwindow in two steps:
    glutSetWindow (subwindow_1);  //step 1: select 1st subwindow as the current window;
    glutPostRedisplay();          //step 2: re-display the current window
    
    // re-display the 2nd subwindow in two steps
    glutSetWindow (subwindow_2);  //step 1: select the 2nd subwindow as the current window;
    glutPostRedisplay();          //step 2: re-display the current window
    
    // re-display the 3rd subwindow in two steps
    glutSetWindow (subwindow_3);  //step 1: select the 2nd subwindow as the current window;
    glutPostRedisplay();          //step 2: re-display the current window
    
    // re-display the 4th subwindow in two steps
    glutSetWindow (subwindow_4);  //step 1: select the 2nd subwindow as the current window;
    glutPostRedisplay();          //step 2: re-display the current window
    
    // re-display the 5th subwindow in two steps
    glutSetWindow (subwindow_5);  //step 1: select the 2nd subwindow as the current window;
    glutPostRedisplay();          //step 2: re-display the current window
    
    // re-display the 6th subwindow in two steps
    glutSetWindow (subwindow_6);  //step 1: select the 2nd subwindow as the current window;
    glutPostRedisplay();          //step 2: re-display the current window
    
}

//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void centerOnScreen ()
{
    window_x = (glutGet (GLUT_SCREEN_WIDTH) - window_width)/2;
    window_y = (glutGet (GLUT_SCREEN_HEIGHT) - window_height)/2;
}

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------
void printw (float x, float y, float z, char* format)
{
    char *id;
    glRasterPos3f(x,y,z);
    for (id = format;*id != '\0'; id++)
    {
        glutBitmapCharacter(font_style, *id);
    }
}
