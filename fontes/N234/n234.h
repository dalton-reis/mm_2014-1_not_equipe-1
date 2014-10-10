
#ifndef n234_h
#define n234_h

#include "math.h"

#define ACTIVESTEREO	1
#define DUALSTEREO		2
#define TOEDIN			3
#define ANAGLYPH		4

#define ESC 27

typedef struct {
	double x,y,z;
} XYZ;

#define CROSSPROD(p1,p2,p3) \
   p3.x = p1.y*p2.z - p1.z*p2.y; \
   p3.y = p1.z*p2.x - p1.x*p2.z; \
   p3.z = p1.x*p2.y - p1.y*p2.x

typedef struct {
	XYZ vp;                /* View position           */
	XYZ vd;                /* View direction vector   */
	XYZ vu;                /* View up direction       */
	XYZ pr;                /* Point to rotate about   */
	double focallength;    /* Focal Length along vd   */
	double aperture;       /* Camera aperture         */
	double eyesep;         /* Eye separation          */
	double nr,fr;		   /* near,far Cutting plane distances */
	int stereo;			   /* Are we in stereo mode   */
	int screenwidth;       /* Screen dimensions       */
	int screenheight;      /*                         */
} CAMERA;
typedef struct {
	int debug;             /* Debug mode              */
	int record;            /* Movie recording mode    */
	int windowdump;        /* Image recording modes   */
	int fullscreen;        /* Game mode or not        */
	double targetfps;      /* Target frame rate       */
} OPTIONS;
typedef struct {
	int button;
	int shift;
	int mouseh;
	int mousev;
} INTERFACESTATE;

/* Normalise a vector */
static void Normalise(XYZ *p)
{
   double length;

   length = p->x * p->x + p->y * p->y + p->z * p->z;
   if (length > 0) {
      length = sqrt(length);
      p->x /= length;
      p->y /= length;
      p->z /= length;
   } else {
      p->x = 0;
      p->y = 0;
      p->z = 0;
   }
}

/** Rotate (ix,iy) or roll (iz) the camera about the focal point */
static void RotateCamera(CAMERA *camera,double ix,double iy,double iz){
   XYZ vp,vu,vd,right;
   XYZ newvp,newr;
   double dx,dy,dz,radius;

   vu = camera->vu;
   Normalise(&vu);
   vp = camera->vp;
   vd = camera->vd;
   Normalise(&vd);
   CROSSPROD(vd,vu,right);
   Normalise(&right);

   /* Handle the roll */
   if (iz != 0) {
      camera->vu.x += iz * right.x;
      camera->vu.y += iz * right.y;
      camera->vu.z += iz * right.z;
      Normalise(&camera->vu);
      return;
   }

   /* Distance from the rotate point */
   dx = camera->vp.x - camera->pr.x;
   dy = camera->vp.y - camera->pr.y;
   dz = camera->vp.z - camera->pr.z;
   radius = sqrt(dx*dx + dy*dy + dz*dz);

   /* Determine the new view point */
   newvp.x = vp.x + ix * right.x + iy * vu.x - camera->pr.x;
   newvp.y = vp.y + ix * right.y + iy * vu.y - camera->pr.y;
   newvp.z = vp.z + ix * right.z + iy * vu.z - camera->pr.z;
   Normalise(&newvp);
   camera->vp.x = camera->pr.x + radius * newvp.x;
   camera->vp.y = camera->pr.y + radius * newvp.y;
   camera->vp.z = camera->pr.z + radius * newvp.z;

   /* Determine the new right vector */
   newr.x = camera->vp.x + right.x - camera->pr.x;
   newr.y = camera->vp.y + right.y - camera->pr.y;
   newr.z = camera->vp.z + right.z - camera->pr.z;
   Normalise(&newr);
   newr.x = camera->pr.x + radius * newr.x - camera->vp.x;
   newr.y = camera->pr.y + radius * newr.y - camera->vp.y;
   newr.z = camera->pr.z + radius * newr.z - camera->vp.z;

   camera->vd.x = camera->pr.x - camera->vp.x;
   camera->vd.y = camera->pr.y - camera->vp.y;
   camera->vd.z = camera->pr.z - camera->vp.z;
   Normalise(&camera->vd);

   /* Determine the new up vector */
   CROSSPROD(newr,camera->vd,camera->vu);
   Normalise(&camera->vu);
}

/** Translate (pan) the camera view point */
static void TranslateCamera(CAMERA *camera,double ix,double iy,double iz){
   XYZ right;

   CROSSPROD(camera->vd,camera->vu,right);
   Normalise(&right);

   camera->vp.x += iy*camera->vu.x + ix*right.x + iz*camera->vd.x;
   camera->vp.y += iy*camera->vu.y + ix*right.y + iz*camera->vd.y;
   camera->vp.z += iy*camera->vu.z + ix*right.z + iz*camera->vd.z;

   camera->pr.x += iy*camera->vu.x + ix*right.x + iz*camera->vd.x;
   camera->pr.y += iy*camera->vu.y + ix*right.y + iz*camera->vd.y;
   camera->pr.z += iy*camera->vu.z + ix*right.z + iz*camera->vd.z;
}

#define TWOPI 6.283185307179586476925287
#define DTOR 0.0174532925
#define RTOD 57.2957795

#define PI 3.14159265

#endif
