
#include "sru.h"
#include "gl.h"
#include "n234.h"

void Sru::draw(int run){
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(1.0,0.0,0.0);
	glColor3f(0.0,1.0,0.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,1.0,0.0);
	glColor3f(0.0,0.0,1.0);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,0.0,1.0);
	glEnd();
	glPopMatrix();
}

