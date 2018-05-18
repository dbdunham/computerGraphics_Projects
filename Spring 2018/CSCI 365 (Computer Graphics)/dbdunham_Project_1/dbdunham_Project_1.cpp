//////////////////////////////////////////////////////////////          
// File name: lineSegment.cpp
//
// What: An OpenGL program that draws a line segment.
// 
// Original: Chapter03 example code ("ch3OGLexample.txt") from 
//   "Computer Graphics with OpenGL" by Hearn, 4th ed
//
// Modified by Xuwei Liang @ USCB
//   For CSCI B365 classroom use only
//
// Author: Darryl Dunham
// Date: 2/14/2018
//
/////////////////////////////////////////////////////////////

#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

//Function prototypes
void init(void) ;
void lineSegment(void);


//Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main (int argc, char** argv)
{
	//Initialize GLUT
	//Allow cmd line arguments to be passed to the glut
	glutInit (&argc, argv);
	
	// GLUT Window Initialization
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   //Set display mode.
	glutInitWindowPosition (50, 100);				//Set top-left display-window position.
	glutInitWindowSize (400, 300);					//Set display-window width and height.
	glutCreateWindow ("CSCI B365 - First OpenGL Program"); // Create display window.

	//Initialize OpenGL graphics state
	init ( );

	//Register callback functions
	glutDisplayFunc (lineSegment); //Send graphics to display window
	//glutReshapeFunc(resize);     //sets the reshape callback for the current window
	//glutKeyboardFunc(keyInput);  //sets the keyboard callback for the current window

	//Turn the flow of control over to GLUT and enter the main loop
	//Display everything and wait.
	glutMainLoop ();
	
	//We will never be able to reach here
	return 0;
}

//********************* Function implementations *************************
//Input: None
//Process: Initialize OpenGL graphics state.
//Output None
void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);  //Set display-window color to white.

	glMatrixMode (GL_PROJECTION);       //Set projection parameters.
	//glLoadIdentity();						//Clear current projection matrix to identity.
	gluOrtho2D (0.0, 200.0, 0.0, 150.0);
}


//Input: None
//Process: Callback function handling picture drawing
//         It draws a single linesegment with hardcoded two end points
//Output: None
void lineSegment (void)
{
	const int circle_points=360; // number of points in circle
    const float cx=50, cy=95, r=20; // center point (x,y) and radius
    const float pi = 3.14159f; // pi

	glClear (GL_COLOR_BUFFER_BIT);  //Clear display window.
	glColor3f (1.0, 0.0, 0.0);      //Set line segment color to green.

	glBegin (GL_LINES);
		glVertex2i (50, 75);       //Specify line-segment geometry.
		glVertex2i (25, 50);
	glEnd();

	glBegin (GL_LINES);
		glVertex2i (50, 75);       //Specify line-segment geometry.
		glVertex2i (75, 50);
	glEnd();

	glBegin (GL_LINES);
		glVertex2i (50, 75);       //Specify line-segment geometry.
		glVertex2i (50, 50);
	glEnd();

	glBegin (GL_LINES);
		glVertex2i (50, 50);       //Specify line-segment geometry.
		glVertex2i (25, 25);
	glEnd();

	glBegin (GL_LINES);
		glVertex2i (50, 50);       //Specify line-segment geometry.
		glVertex2i (75, 25);
	glEnd();

	glBegin(GL_LINE_LOOP);			// draws circle
	for (int i = 0; i < circle_points; i++) // for loop that goes through all the points in the circle
	{
		const float theta = (2*pi*i)/circle_points; // finds theta which is used for the calculations of the circle shape
		glVertex2i(cx + r * cos(theta), cy + r * sin(theta)); // does math for each point
	}
	glEnd ( );

	glFlush ( );     //Process all OpenGL routines as quickly as possible.
}