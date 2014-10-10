
#include "chaleira.h"
#include "gl.h"
#include "n234.h"

double RetornaX(double angulo, double raio) {
	return (raio * cos(PI * angulo / 180.0));
}

double RetornaY(double angulo, double raio) {
	return (raio * sin(PI * angulo / 180.0));
}


void Chaleira::draw(int run){
	static int teapotPos = 0;
	glPushMatrix();
	glTranslated(RetornaX(teapotPos,2.0) ,RetornaY(teapotPos,2.0),0);
	glRotated(90.0,0.0,1.0,1.0);
	//glColor3f(0.3,0.3,0.1);
	glColor3f(1.0,1.0,1.0);
	//glutSolidTeapot(0.4f);
	glutWireTeapot(0.4f);
	if(run){
		if(teapotPos < 360){
			teapotPos++;
		}else{
			teapotPos=0;
		}
	}
	glPopMatrix();
}

