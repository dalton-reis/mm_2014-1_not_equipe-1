
#include "quadrado.h"
#include "gl.h"
#include "n234.h"

void Quadrado::draw(int run){
	XYZ pmin = {-2,-2,-2},pmax = {2,2,2};

	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_LINE_STRIP);
	glVertex3f(pmin.x,pmin.y,pmin.z);
	glVertex3f(pmax.x,pmin.y,pmin.z);
	glVertex3f(pmax.x,pmin.y,pmax.z);
	glVertex3f(pmin.x,pmin.y,pmax.z);
	glVertex3f(pmin.x,pmin.y,pmin.z);
	glVertex3f(pmin.x,pmax.y,pmin.z);
	glVertex3f(pmax.x,pmax.y,pmin.z);
	glVertex3f(pmax.x,pmax.y,pmax.z);
	glVertex3f(pmin.x,pmax.y,pmax.z);
	glVertex3f(pmin.x,pmax.y,pmin.z);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(pmax.x,pmin.y,pmin.z); 
	glVertex3f(pmax.x,pmax.y,pmin.z);
	glVertex3f(pmax.x,pmin.y,pmax.z); 
	glVertex3f(pmax.x,pmax.y,pmax.z);
	glVertex3f(pmin.x,pmin.y,pmax.z); 
	glVertex3f(pmin.x,pmax.y,pmax.z);
	glEnd();
	glPopMatrix();
}

