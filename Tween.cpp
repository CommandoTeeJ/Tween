#include <iostream>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\glut.h>
using namespace std;

//points is how many points are in the images
const int points = 8;

//frameDelay is the amount of time between frames
const int frameDelay = 10;

//level is the where in the image translation that you are, max level determines how many levels
//will be traversed
float level = 1, maxLevel = 500;

//forwardC tells whether we are moving forward or backward
bool forwardC = true;

//Points of the 2 images
//T
float Point1x[] = {2,8,8,6,6,4,4,2};
float Point1y[] = {8,8,6,6,2,2,6,6};
//House
float Point2x[] = {2,5,5,8,6,6,4,4};
float Point2y[] = {4,8,8,4,4,2,2,4};

/*
//Square
float Point1x[] = {2,5,8,8,8,5,2,2};
float Point1y[] = {2,2,2,5,8,8,8,5};
//Cross
float Point2x[] = {2,5,8,5,8,5,2,5};
float Point2y[] = {2,5,2,5,8,5,8,5};
*/

//Points determined based on the transformation of the 2 images
float tempX[points];
float tempY[points];

//tween function which displays the tween
void tween(int t) {
	glClear(GL_COLOR_BUFFER_BIT);

	//ensure that the tween is going in the correct direction
	if (level < maxLevel && forwardC) {
		level++;
	}
	else if (level > 1) {
		forwardC = false;
		level--;
	}
	else {
		forwardC = true;
		level++;
	}

	//Generate the points of the tween
	for (int i = 0; i < points; i++) {
		tempX[i] = Point1x[i]*(level / maxLevel);
		tempX[i] += Point2x[i] * (1-(level / maxLevel));
		tempY[i] = Point1y[i] * (level / maxLevel);
		tempY[i] += Point2y[i] * (1 - (level / maxLevel));
	}

	//Draw lines based on tween points
	for (int i = 0; i < points-1; i++) {
		glBegin(GL_LINES);
		glVertex2f(tempX[i], tempY[i]);
		glVertex2f(tempX[i + 1], tempY[i + 1]);
		glEnd();
	}

	//Draw line from last point to first point
	glBegin(GL_LINES);
	glVertex2f(tempX[points-1], tempY[points-1]);
	glVertex2f(tempX[0], tempY[0]);
	glEnd();
	//Swap the drawing and display buffers
	glFlush();
	glutSwapBuffers();

	//Call tween again in [frameDelay] ms
	glutTimerFunc(frameDelay, tween, 1);
}

//initiate values
void initialDraw() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 10, 0, 10);
	glColor3f(1, 0, 0);
	
}

//main//
int main(int argc,char * argv) {
	//double buffer with RGB colorscale
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//Window begins at 200x200
	glutInitWindowPosition(200, 200);
	//Window Size is 640x480
	glutInitWindowSize(640, 480);
	//Create window with title "Tweening"
	glutCreateWindow("Tweening");
	//Initiate values
	glutDisplayFunc(initialDraw);
	//Call tween
	glutTimerFunc(100, tween, 1);
	//main loop
	glutMainLoop();
}