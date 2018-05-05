
// Modified from one of the GLUT sample files by Mark Kilgard simple.c

#include <iostream>
#include <fstream>
#include <iomanip>
#include "glut.h"
using namespace std;

struct point
{
	double x;
	double y;
};

const double tstep = 100.0; // # steps from 0 to 1 for t
const int range = 300; // x, y coord are 0 to range
const char sigpnt[120] = "data.txt"; // name of data file

void draw_bezier(point p1, point p2, point p3, point p4)
{
	double t = 0.0;
	double t2, t3, mt, mt2, mt3;
	double xd, yd;

	xd = p1.x; yd = p1.y;
	while (t < 1.0)
	{
		glVertex2f(xd + .3, yd + .3);
		t = t + 1.0 / tstep;
		t2 = t * t;
		t3 = t2 * t;
		mt = 1 - t;
		mt2 = mt * mt;
		mt3 = mt2 * mt;

		xd = p1.x * mt3 + p2.x * 3 * mt2*t + p3.x * 3 * mt*t2 + p4.x * t3;
		yd = p1.y * mt3 + p2.y * 3 * mt2*t + p3.y * 3 * mt*t2 + p4.y * t3;
		glVertex2f(xd + .3, yd + .3);
	}

	return;
}

void read_bezier()
{
	ifstream fin;
	point p1, p2, p3, p4;
	double range2;

	fin.open(sigpnt);
	if (fin.fail())
	{
		cerr << "couldn't open file " << sigpnt << "exiting...\n";
		exit(13);
	}


	while (!fin.eof())
	{
		// read next set of control points
		fin >> p1.x >> p1.y;
		fin >> p2.x >> p2.y;
		fin >> p3.x >> p3.y;
		fin >> p4.x >> p4.y;

		// scale from 0 to 500 to screen (-1 to 1)
		range2 = range / 2;
		p1.x = (p1.x - range2) / range2;
		p2.x = (p2.x - range2) / range2;
		p3.x = (p3.x - range2) / range2;
		p4.x = (p4.x - range2) / range2;
		p1.y = (p1.y - range2) / range2;
		p2.y = (p2.y - range2) / range2;
		p3.y = (p3.y - range2) / range2;
		p4.y = (p4.y - range2) / range2;

		// draw curve
		draw_bezier(p1, p2, p3, p4);
	}
	fin.close();
	return;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 1.0);	// blue
	read_bezier();
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("signature");
	glutReshapeWindow(300,300);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}