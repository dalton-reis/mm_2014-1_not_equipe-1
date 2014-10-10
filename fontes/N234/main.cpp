#include <stdio.h>
#include "n234.h"
#include "gl.h"
#include "world.h"

#include "espiral.h"
#include "chaleira.h"
#include "quadrado.h"
#include "sru.h"

World *world;

OPTIONS options;
CAMERA  camera;
INTERFACESTATE interfacestate;

int run = 1;

/*
   Move the camera to the home position 
*/
void CameraHome(int position)
{
   XYZ origin = {0,0,0};
   XYZ up = {0.0,0.0,1.0},x = {1.0,0.0,0.0};

   switch (position) {
   case 0:
      camera.aperture = 60;
      camera.focallength = 6;
      camera.eyesep = camera.focallength / 25;
      camera.nr = camera.focallength / 10;
      camera.fr = camera.focallength * 10;
      camera.vp.x = -camera.focallength;
      camera.vp.y = 0; 
      camera.vp.z = 0;
      camera.vd.x = 1;
      camera.vd.y = 0;
      camera.vd.z = 0;
      camera.vu = up;
      break;
   case 1: /* Front */
      camera.vp.x = -camera.focallength;
      camera.vp.y = 0;
      camera.vp.z = 0;
      camera.vd.x = 1;
      camera.vd.y = 0;
      camera.vd.z = 0;
      camera.vu = up;
      break;
   case 2: /* Back */
      camera.vp.x = camera.focallength;
      camera.vp.y = 0;
      camera.vp.z = 0;
      camera.vd.x = -1;
      camera.vd.y = 0;
      camera.vd.z = 0;
      camera.vu = up;
      break;
   case 3: /* Left */
      camera.vp.x = 0;
      camera.vp.y = camera.focallength;
      camera.vp.z = 0;
      camera.vd.x = 0;
      camera.vd.y = -1;
      camera.vd.z = 0;
      camera.vu = up;
      break;
   case 4: /* Right */
      camera.vp.x = 0;
      camera.vp.y = -camera.focallength;
      camera.vp.z = 0;
      camera.vd.x = 0;
      camera.vd.y = 1;
      camera.vd.z = 0;
      camera.vu = up;
      break;
   case 5: /* Top */
      camera.vp.x = 0;
      camera.vp.y = 0;
      camera.vp.z = camera.focallength;
      camera.vd.x = 0;
      camera.vd.y = 0;
      camera.vd.z = -1;
      camera.vu = x;
      break;
   case 6: /* Bottom */
      camera.vp.x = 0;
      camera.vp.y = 0;
      camera.vp.z = -camera.focallength;
      camera.vd.x = 0;
      camera.vd.y = 0;
      camera.vd.z = 1;
      camera.vu = x;
      break;
   }

   camera.pr = origin;
   Normalise(&camera.vd);
   Normalise(&camera.vu);
}

/** Deal with plain key strokes */
void keyboard(unsigned char key,int x, int y)
{
   if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
      interfacestate.shift = TRUE;
   else
      interfacestate.shift = FALSE;

   /* Handle keyboard commands */
   switch (key) {
   case ESC:                            /* Quit */
   case 'Q':
   case 'q': 
      exit(0);
      break;
   case 'h':                           /* Go home     */
   case 'H':
      CameraHome(0);
      break;
   case '[':                           /* Roll anti clockwise */
      RotateCamera(&camera,0.0,0.0,-0.1);
      break;
   case ']':                           /* Roll clockwise */
      RotateCamera(&camera,0.0,0.0,0.1);
      break;
   case '<':                           /* Move forward */
   case ',':
      TranslateCamera(&camera,0.0,0.0,camera.focallength/50);
      break;
   case '>':                           /* Move backward */
   case '.':
      TranslateCamera(&camera,0.0,0.0,-camera.focallength/50);
      break;
   case '-':                           /* Zoom in */
   case '_':
      if (camera.aperture < 90)
         camera.aperture *= 1.05;
      break;
   case '+':                           /* Zoom out */
   case '=':
      if (camera.aperture > 5)
         camera.aperture /= 1.05;
      break;
	case 'P':                           /* Zoom out */
    case 'p':
      if (run){
        run = 0;
	  }else{
		run = 1;
	  }
      break;
	case 'm':
	   if(options.targetfps > 1){
		options.targetfps--;
	   }
	   break;
	case 'n':
		options.targetfps++;
		break;
	case 'f':
		glutFullScreen();
		break;
	case 'z':
		camera.eyesep += 0.01;
		break;
	case 'x':
		//if(camera.eyesep > 0){
			camera.eyesep -= 0.01;
		//}
		break;
	case '1':
		camera.stereo = ACTIVESTEREO;
		break;
	case '2':
		camera.stereo = DUALSTEREO;
		break;
	case '3':
		camera.stereo = TOEDIN;
		break;
	case '4':
		camera.stereo = ANAGLYPH;
		break;
   }
}

/** Deal with special key strokes */
void specialKeyboard(int key,int x, int y){
   if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
      interfacestate.shift = TRUE;
   else
      interfacestate.shift = FALSE;

   switch (key) {
   case GLUT_KEY_LEFT:  
      if (interfacestate.shift)
         TranslateCamera(&camera,-1.0,0.0,0.0);
      else
         RotateCamera(&camera,-1.0,0.0,0.0); 
      break;
   case GLUT_KEY_RIGHT: 
      if (interfacestate.shift)
         TranslateCamera(&camera,1.0,0.0,0.0);
      else
         RotateCamera(&camera,1.0,0.0,0.0);  
      break;
   case GLUT_KEY_UP:    
      if (interfacestate.shift)
         TranslateCamera(&camera,0.0,1.0,0.0);
      else
         RotateCamera(&camera,0.0,1.0,0.0);  
      break;
   case GLUT_KEY_DOWN:  
      if (interfacestate.shift)
         TranslateCamera(&camera,0.0,-1.0,0.0);
      else
         RotateCamera(&camera,0.0,-1.0,0.0); 
      break;
   case GLUT_KEY_F1:
      CameraHome(1);
      break;
   case GLUT_KEY_F2:
      CameraHome(2);
      break;
   case GLUT_KEY_F3:
      CameraHome(3);
      break;
   case GLUT_KEY_F4:
      CameraHome(4);
      break;
   case GLUT_KEY_F5:
      CameraHome(5);
      break;
   case GLUT_KEY_F6:
      CameraHome(6);
      break;
   }
}


/**
 * Handle mouse events.
 * Do nothing special, just remember the state.
 */
void mouse(int button,int state,int x,int y){
   if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
      interfacestate.shift = TRUE;
   else
      interfacestate.shift = FALSE;

   if (state == GLUT_DOWN) {
      if (button == GLUT_LEFT_BUTTON) {
         interfacestate.button = GLUT_LEFT_BUTTON;
      } else if (button == GLUT_MIDDLE_BUTTON) {
         interfacestate.button = GLUT_MIDDLE_BUTTON;
      } else {
         /* Assigned to menus */
      }
   }
   interfacestate.mouseh = x;
   interfacestate.mousev = y;
}

/** Handle mouse motion */
void mouseMotion(int x,int y){
   double dx,dy;

   dx = x - interfacestate.mouseh;
   dy = y - interfacestate.mousev;

   if (interfacestate.button == GLUT_LEFT_BUTTON) {
      if (interfacestate.shift)
         TranslateCamera(&camera,-dx/25,dy/25,0.0);
      else
         RotateCamera(&camera,-dx/25,dy/25,0.0);
   } else if (interfacestate.button == GLUT_MIDDLE_BUTTON) {
      if (interfacestate.shift)
         TranslateCamera(&camera,0.0,0.0,camera.focallength*dx/50);
      else
         RotateCamera(&camera,0.0,0.0,dx/50);
   }

   interfacestate.mouseh = x;
   interfacestate.mousev = y;
}

/** What to do on moviing nouse, the button isn't down. */
void passiveMotion(int x,int y){
   interfacestate.mouseh = x;
   interfacestate.mousev = y;
}


/** Função de inicializacao */
void init(){
	glClearColor( 0, 0, 0, 0 );					// Pinta o fundo do canvas com cinza (204,204,204)	
}

/** Função de renderização */
void display(){
	world->draw(run);
	glutSwapBuffers();		// Swap buffers
}

/** 
 * Função para remodelar
 * @param width Largura
 * @param heigth Altura
 */
void reshape(int width,int heigth){
	camera.screenwidth = width;
	camera.screenheight = heigth;
	glutPostRedisplay();
}

/** Função para quando ocioso */
void idle(){	
}

void timer(int value){
	glutPostRedisplay();
	glutTimerFunc(options.targetfps,timer,0);
}


void visibility(int v){
	if(v == GLUT_VISIBLE){
		timer(0);
	}
}

/**
 * Main da aplicacao
 * @author Gustavo Rufino Feltrin
 * @author Leonardo Fernandes
 */
int main(int argc, char *argv[]){
	GLfloat	lightpos[4] = { -10.0, 15.0, 10.0, 1.0 }; 	

	CameraHome(0);
	camera.stereo       = DUALSTEREO;
	camera.screenwidth  = 300;
	camera.screenheight = 300;

	/* Default options */
	options.debug        = FALSE;
	options.fullscreen   = FALSE;
	options.windowdump   = FALSE;
	options.record       = FALSE;
	options.targetfps    = 30;

	/* State of the input device, mouse in this case */
	interfacestate.button = -1;
	interfacestate.shift  = FALSE;
	interfacestate.mouseh = 0;
	interfacestate.mousev = 0;

	
	/* Set things up and go */
	glutInit(&argc,argv);
	world = new World(&camera);
	world->pushObject(new Espiral());
	world->pushObject(new Chaleira());
	world->pushObject(new Quadrado());
	world->pushObject(new Sru());

	/* Create the window and handlers */
	glutCreateWindow("N234");
	glutReshapeWindow(camera.screenwidth,camera.screenheight);

	init();

	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutIdleFunc( idle );
	glutVisibilityFunc( visibility );

	glutKeyboardFunc( keyboard );
	glutSpecialFunc( specialKeyboard );
	glutMouseFunc( mouse );
	glutMotionFunc( mouseMotion );
	glutPassiveMotionFunc( passiveMotion );

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable( GL_COLOR_MATERIAL );
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glutMainLoop();
	return 0;
}
