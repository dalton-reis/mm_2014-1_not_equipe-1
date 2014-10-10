
#include "stereo.h"
#include "gl.h"

#include <stdio.h>

Stereo::Stereo(CAMERA *camera){
	this->camera = camera;

	switch(camera->stereo){
	case ACTIVESTEREO:
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STEREO);
		break;
	case DUALSTEREO:
	case TOEDIN:
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		camera->screenwidth *= 2;
		break;
	case ANAGLYPH:
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		break;
	}
} 

void Stereo::viewPre(){
	XYZ r;
	double ratio,radians,wd2,ndfl;

	switch(camera->stereo){
	case ACTIVESTEREO:
	case DUALSTEREO:
		this->camera->nr = (this->camera->focallength / 10);
		ratio   = camera->screenwidth / (double)camera->screenheight;
		if (camera->stereo != ACTIVESTEREO){
			ratio /= 2;
		}
		radians = DTOR * camera->aperture / 2;
		wd2     = camera->nr * tan(radians);
		ndfl    = camera->nr / camera->focallength;
		CROSSPROD(camera->vd,camera->vu,r);
		Normalise(&r);
		r.x *= camera->eyesep / 2.0;
		r.y *= camera->eyesep / 2.0;
		r.z *= camera->eyesep / 2.0;
		this->top =   wd2;
		this->bottom  = - wd2;
		this->leftR  = - ratio * wd2 - 0.5 * camera->eyesep * ndfl;
		this->rightR =   ratio * wd2 - 0.5 * camera->eyesep * ndfl;
		this->leftL  = - ratio * wd2 + 0.5 * camera->eyesep * ndfl;
		this->rightL =   ratio * wd2 + 0.5 * camera->eyesep * ndfl;
		this->eyexR = camera->vp.x + r.x;
		this->eyeyR = camera->vp.y + r.y;
		this->eyezR = camera->vp.z + r.z;
		this->centerxR = camera->vp.x + r.x + camera->vd.x;
		this->centeryR = camera->vp.y + r.y + camera->vd.y;
		this->centerzR = camera->vp.z + r.z + camera->vd.z;
		this->eyexL = camera->vp.x - r.x;
		this->eyeyL = camera->vp.y - r.y;
		this->eyezL = camera->vp.z - r.z;
		this->centerxL = camera->vp.x - r.x + camera->vd.x;
		this->centeryL = camera->vp.y - r.y + camera->vd.y;
		this->centerzL = camera->vp.z - r.z + camera->vd.z;
		this->upx = camera->vu.x;
		this->upy = camera->vu.y;
		this->upz = camera->vu.z;
		break;
	case TOEDIN:
		this->camera->nr = (this->camera->focallength / 10);
		ratio   = camera->screenwidth / (double)camera->screenheight;
		if (camera->stereo != ACTIVESTEREO){
			ratio /= 2;
		}
		radians = DTOR * camera->aperture / 2;
		wd2     = camera->nr * tan(radians);
		ndfl    = camera->nr / camera->focallength;
		CROSSPROD(camera->vd,camera->vu,r);
		Normalise(&r); 
		r.x *= camera->eyesep / 2.0;
		r.y *= camera->eyesep / 2.0;
		r.z *= camera->eyesep / 2.0;
		this->top =   wd2;
		this->bottom  = - wd2;
		this->leftR  = - ratio * wd2 + 0.5 * camera->eyesep * ndfl;
		this->rightR =   ratio * wd2 + 0.5 * camera->eyesep * ndfl;
		this->leftL  = - ratio * wd2 + 0.5 * camera->eyesep * ndfl;
		this->rightL =   ratio * wd2 + 0.5 * camera->eyesep * ndfl;
		this->eyexR = (camera->vp.x + r.x);
		this->eyeyR = (camera->vp.y + r.y)-0.025;
		this->eyezR = (camera->vp.z + r.z);
		this->centerxR = camera->vp.x + r.x + camera->vd.x;
		this->centeryR = camera->vp.y + r.y + camera->vd.y;
		this->centerzR = camera->vp.z + r.z + camera->vd.z;
		this->eyexL = (camera->vp.x - r.x);
		this->eyeyL = (camera->vp.y - r.y)+0.025;
		this->eyezL = (camera->vp.z - r.z);
		this->centerxL = camera->vp.x - r.x + camera->vd.x;
		this->centeryL = camera->vp.y - r.y + camera->vd.y;
		this->centerzL = camera->vp.z - r.z + camera->vd.z;
		this->upx = camera->vu.x;
		this->upy = camera->vu.y;
		this->upz = camera->vu.z;
		break;
	case ANAGLYPH:
		this->camera->nr = (this->camera->focallength / 5);
		ratio   = camera->screenwidth / (double)camera->screenheight;
		radians = DTOR * camera->aperture / 2;
		wd2     = camera->nr * tan(radians) ;
		ndfl    = camera->nr / camera->focallength + 0.1;
		CROSSPROD(camera->vd,camera->vu,r);
		Normalise(&r);
		r.x *= camera->eyesep / 2.0;
		r.y *= camera->eyesep / 2.0;
		r.z *= camera->eyesep / 2.0;
		this->top =   wd2;
		this->bottom  = - wd2;
		this->leftR  = - ratio * wd2 - 0.5 * camera->eyesep * ndfl;
		this->rightR =   ratio * wd2 - 0.5 * camera->eyesep * ndfl;
		this->leftL  = - ratio * wd2 + 0.5 * camera->eyesep * ndfl;
		this->rightL =   ratio * wd2 + 0.5 * camera->eyesep * ndfl;
		this->eyexR = camera->vp.x + r.x;
		this->eyeyR = camera->vp.y + r.y;
		this->eyezR = camera->vp.z + r.z;
		this->centerxR = camera->vp.x + r.x + camera->vd.x;
		this->centeryR = camera->vp.y + r.y + camera->vd.y;
		this->centerzR = camera->vp.z + r.z + camera->vd.z;
		this->eyexL = camera->vp.x - r.x;
		this->eyeyL = camera->vp.y - r.y;
		this->eyezL = camera->vp.z - r.z;
		this->centerxL = camera->vp.x - r.x + camera->vd.x;
		this->centeryL = camera->vp.y - r.y + camera->vd.y;
		this->centerzL = camera->vp.z - r.z + camera->vd.z;
		this->upx = camera->vu.x;
		this->upy = camera->vu.y;
		this->upz = camera->vu.z;
		break;
	}

	
}

void Stereo::viewRight(){
	switch(camera->stereo){
	case ACTIVESTEREO:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(leftR,rightR,bottom,top,camera->nr,camera->fr);
		glViewport(0,0,camera->screenwidth,camera->screenheight);
		glMatrixMode(GL_MODELVIEW);
		glDrawBuffer(GL_BACK_RIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(eyexR,eyeyR,eyezR,centerxR,centeryR,centerzR,upx,upy,upz);
		break;
	case DUALSTEREO:
		glDrawBuffer(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(leftR,rightR,bottom,top,camera->nr,camera->fr);
		glViewport(camera->screenwidth/2,0,camera->screenwidth/2,camera->screenheight);
		glMatrixMode(GL_MODELVIEW);
		glDrawBuffer(GL_BACK_RIGHT);
		glLoadIdentity();
		gluLookAt(eyexR,eyeyR,eyezR,centerxR,centeryR,centerzR,upx,upy,upz);
		break;
	case TOEDIN:
		glDrawBuffer(GL_BACK);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(leftR,rightR,bottom,top,camera->nr,camera->fr);
		glViewport(camera->screenwidth/2,0,camera->screenwidth/2,camera->screenheight);
		glMatrixMode(GL_MODELVIEW);
		glDrawBuffer(GL_BACK_RIGHT);
		glLoadIdentity();
		gluLookAt(eyexL,eyeyL,eyezL,centerxL,centeryL,centerzL,upx,upy,upz);
		break;
	case ANAGLYPH:
		glDrawBuffer(GL_BACK);
		glReadBuffer(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_ACCUM_BUFFER_BIT); /* Not strictly necessary */
		glViewport(0,0,camera->screenwidth,camera->screenheight);
		glColorMask(GL_TRUE,GL_FALSE,GL_FALSE,GL_TRUE);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(leftR,rightR,bottom,top,camera->nr,camera->fr);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eyexR,eyeyR,eyezR,centerxR,centeryR,centerzR,upx,upy,upz);
		break;
	}
}

void Stereo::viewLeft(){
	switch(camera->stereo){
	case ACTIVESTEREO:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(leftL,rightL,bottom,top,camera->nr,camera->fr);
		glViewport(0,0,camera->screenwidth,camera->screenheight);
		glMatrixMode(GL_MODELVIEW);
		glDrawBuffer(GL_BACK_LEFT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(eyexL,eyeyL,eyezL,centerxL,centeryL,centerzL,upx,upy,upz);
		break;
	case DUALSTEREO:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(leftL,rightL,bottom,top,camera->nr,camera->fr);
		glViewport(0,0,camera->screenwidth/2,camera->screenheight);
		glMatrixMode(GL_MODELVIEW);
		glDrawBuffer(GL_BACK_LEFT);
		glLoadIdentity();
		gluLookAt(eyexL,eyeyL,eyezL,centerxL,centeryL,centerzL,upx,upy,upz);
		break;
	case TOEDIN:
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(leftL,rightL,bottom,top,camera->nr,camera->fr);
		glViewport(0,0,camera->screenwidth/2,camera->screenheight);
		glMatrixMode(GL_MODELVIEW);
		glDrawBuffer(GL_BACK_LEFT);
		glLoadIdentity();
		gluLookAt(eyexR,eyeyR,eyezR,centerxR,centeryR,centerzR,upx,upy,upz);
		break;
	case ANAGLYPH:
		glFlush();
		glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE); 
		glAccum(GL_LOAD,1.0);
		glDrawBuffer(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(leftL,rightL,bottom,top,camera->nr,camera->fr);
		glColorMask(GL_FALSE,GL_TRUE,GL_TRUE,GL_TRUE);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eyexL,eyeyL,eyezL,centerxL,centeryL,centerzL,upx,upy,upz);
		break;
	}
}

void Stereo::viewPost(){
	switch(camera->stereo){
	case ACTIVESTEREO:break;
	case DUALSTEREO:break;
	case TOEDIN:break;
	case ANAGLYPH:
		glFlush();
		glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE); 
		glAccum(GL_ACCUM,1.0);
		glAccum(GL_RETURN,1.0);
		break;
	}
}



