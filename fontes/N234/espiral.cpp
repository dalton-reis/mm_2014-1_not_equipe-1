
#include "espiral.h"
#include "gl.h"
#include "n234.h"

void Espiral::draw(int run){
	int i;
	XYZ pmin = {-2,-2,-2},pmax = {2,2,2};
	double mu,x,y,z;
	static double theta = 0;

	glPushMatrix();

	/* Create a rotating knot */
	glPointSize(2.0);
	glColor3f(1.0,0.5,0.5);
	glPushMatrix();
	if(run){
		glRotatef(theta+=1,0.0,0.0,1.0);
	}else{
		glRotatef(theta,0.0,0.0,1.0);
	}
	glBegin(GL_POINTS);
	for (i=0;i<=1000;i++) {
		mu = i * TWOPI * 7 / 1000.0;
		x = cos(mu) * (1 + cos(4*mu/7) / 2.0); 
		y = sin(mu) * (1 + cos(4*mu/7) / 2.0);
		z = 2*sin(4*mu/7) / 2.0;
		glVertex3f(x,y,z);
	}
	glEnd();
	glPopMatrix();
}

