//  Main.cpp
//  The main program
//
//  Jared Melchers (2026)

#include <cmath>
#include <GL/freeglut.h>
#include "Objects/Objects.h"
#include "Objects/ObjectTools.h"
#include "Objects/Characters.h"
#include "Textures/loadTGA.h"

// Globals
int frame = 0;

float camX = 9.192;
float camY = 7.5;
float camZ = 9.192;
float camYaw =  1.25 * M_PI;
float camElev = -M_PI / 6;

bool wPress = false;
bool aPress = false;
bool sPress = false;
bool dPress = false;
bool upPress = false;
bool downPress = false;
bool leftPress = false;
bool rightPress = false;
bool shiftPress = false;
bool ctrlPress = false;

bool wireframe = false;

GLuint texId[3]; 

// Camera controlls
void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '1': camX = -9.192; camY = 7.5; 	camZ = 9.192; 	camElev = -M_PI / 6; 	camYaw = .75 * M_PI; 	break;
        case '2': camX = 0; 	camY = 7.5; 	camZ = 13; 		camElev = -M_PI / 6; 	camYaw = M_PI; 			break;
        case '3': camX = 9.192; camY = 7.5; 	camZ = 9.192; 	camElev = -M_PI / 6; 	camYaw = 1.25 * M_PI;	break;
        case '4': camX = -13; 	camY = 7.5; 	camZ = 0; 		camElev = -M_PI / 6; 	camYaw = .5 * M_PI;		break;
        case '6': camX = 13; 	camY = 7.5; 	camZ = 0; 		camElev = -M_PI / 6; 	camYaw = 1.5 * M_PI;	break;
        case '7': camX = -9.19; camY = 7.5; 	camZ = -9.19; 	camElev = -M_PI / 6; 	camYaw = .25 * M_PI;	break;
        case '8': camX = 0; 	camY = 7.5; 	camZ = -13; 	camElev = -M_PI / 6; 	camYaw = 0 * M_PI;		break;
        case '9': camX = 9.19; 	camY = 7.5; 	camZ = -9.19; 	camElev = -M_PI / 6; 	camYaw = 1.75 * M_PI;	break;
		case 'w': wPress = true; break;
		case 'a': aPress = true; break;
		case 's': sPress = true; break;
		case 'd': dPress = true; break;
		case 'q': {
			if (wireframe) {
				wireframe = false; break;
			} else {
				wireframe = true; break;
			}
		}
    }
}

void keyboardUp(unsigned char key, int x, int y) {
	switch(key) {
		case 'w': wPress = false; break;
		case 'a': aPress = false; break;
		case 's': sPress = false; break;
		case 'd': dPress = false; break;
	}
}

void special(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP: upPress = true; break;
		case GLUT_KEY_DOWN: downPress = true; break;
		case GLUT_KEY_LEFT: leftPress = true; break;
		case GLUT_KEY_RIGHT: rightPress = true; break;
		case GLUT_KEY_SHIFT_L: shiftPress = true; break;
		case GLUT_KEY_CTRL_L: ctrlPress = true; break;
	}
}

void specialUp(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP: upPress = false; break;
		case GLUT_KEY_DOWN: downPress = false; break;
		case GLUT_KEY_LEFT: leftPress = false; break;
		case GLUT_KEY_RIGHT: rightPress = false; break;
		case GLUT_KEY_SHIFT_L: shiftPress = false; break;
		case GLUT_KEY_CTRL_L: ctrlPress = false; break;
	}
}

void cameraUpdate() {
	// Controlls
	if (wPress) {
		camX += 0.1 * cos(camElev) * sin(camYaw);
		camY += 0.1 * sin(camElev);
		camZ += 0.1 * cos(camElev) * cos(camYaw);
	}
	if (aPress) {
		camX += 0.1 * sin(camYaw + M_PI / 2);
		camZ += 0.1 * cos(camYaw + M_PI / 2);
	}
	if (sPress) {
		camX -= 0.1 * cos(camElev) * sin(camYaw);
		camY -= 0.1 * sin(camElev);
		camZ -= 0.1 * cos(camElev) * cos(camYaw);
	}
	if (dPress) {
		camX += 0.1 * sin(camYaw - M_PI / 2);
		camZ += 0.1 * cos(camYaw - M_PI / 2);
	}
	if (upPress) {camElev += 0.01 * M_PI;}
	if (downPress) {camElev -= 0.01 * M_PI;}
	if (leftPress) {camYaw += 0.01 * M_PI;}
	if (rightPress) {camYaw -= 0.01 * M_PI;}
	if (shiftPress) {camY += 0.1;}
	if (ctrlPress) {camY -= 0.1;}

	// Boundries
	if (camX > 16) {camX = 16;}
	if (camX < -16) {camX = -16;}
	if (camY > 16) {camY = 16;}
	if (camY < .3) {camY = .3;}
	if (camZ > 16) {camZ = 16;}
	if (camZ < -16) {camZ = -16;}
	if (camElev > .49 * M_PI) {camElev = .49 * M_PI;}
	if (camElev < .49 * -M_PI) {camElev = .49 * -M_PI;}
}

void reshape (int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50, (float)width / (float)height, .1, 1000.);

	glViewport(0, 0, width, height);
}

void tick(int value) {
	cameraUpdate();
	glutPostRedisplay();
	frame ++;
	glutTimerFunc(40, tick, 0);
}

// Set scene
// responsible for all the animations and object placement
void setScene() {
	float light[] = {2000, 2000, 0., 1.};
	float shadowMat[16] = {light[1], 0, 0, 0, -light[0], 0, -light[2], -1,
						   0, 0, light[1], 0, 0, 0, 0, light[1]};
	
	

	glLightfv(GL_LIGHT0, GL_POSITION, light);
	
	if (wireframe) {
		glDisable(GL_TEXTURE_2D);
	} else {
		glEnable(GL_TEXTURE_2D);
	}

	// Skybox
	glDisable(GL_LIGHTING);
	GLUquadric *q;
	glPushMatrix();
    	q = gluNewQuadric();
		gluQuadricTexture(q, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, texId[0]);
		glColor3f(1,1,1);
		glRotatef(-90, 1, 0, 0);
		gluSphere(q, 750, 16, 64);
	glPopMatrix();
	if (!wireframe) {
		glEnable(GL_LIGHTING);
	}

	// Ground plane
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texId[1]);
		glColor3f(1, 1, 1);
		glNormal3f(0, 1, 0);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(-750, -0.05, 750);
			glTexCoord2f(200, 0);
			glVertex3f(750, -0.05, 750);
			glTexCoord2f(200, 400);
			glVertex3f(750, -0.05, -750);
			glTexCoord2f(0, 400);
			glVertex3f(-750, -0.05, -750);
		glEnd();
	glPopMatrix();

	// Loading ramp
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texId[2]);
		glTranslatef(0, 0, 6.675);
		passengerRamp();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	int loopLength = 750;
	int loopIndex = frame % loopLength;

	int start = 0; int stop = 750;
	if (start < loopIndex < stop) {// Ride spins
		int animIndex = loopIndex - start;

		float spinAngle = (675. / 750.) * (750. / (2. * M_PI) * sin(2. * M_PI * animIndex / 750. - M_PI) + animIndex);
		
		glPushMatrix();
			glRotatef(spinAngle, 0, 1, 0);
			glPushMatrix(); // Centre Rose
				centreRose();
			glPopMatrix();
			for (int i=0; i < 4; i++) { // Arms
				glPushMatrix();
					glRotatef(i* 90, 0, 1, 0);
					arm(7.5 * (cos(M_PI * (spinAngle) / 135 + M_PI) + 1), frame%10);
				glPopMatrix();
				glPushMatrix();
					glRotatef(i* 90 + 45, 0, 1, 0);
					arm(7.5 * (cos(M_PI * (spinAngle) / 135) + 1), frame%10);
				glPopMatrix();
			}
		glPopMatrix();


		glDisable(GL_LIGHTING);

		glPushMatrix();
			glMultMatrixf(shadowMat);
			glRotatef(spinAngle, 0, 1, 0);
			glPushMatrix(); // Centre Rose
				centreRose(true);
			glPopMatrix();
			for (int i=0; i < 4; i++) { // Arms
				glPushMatrix();
					glRotatef(i* 90, 0, 1, 0);
					arm(0, frame%10, false, true);
				glPopMatrix();
				glPushMatrix();
					glRotatef(i* 90 + 45, 0, 1, 0);
					arm(0, frame%10, false, true);
				glPopMatrix();
			}
		glPopMatrix();

	}

	glPushMatrix();
		glMultMatrixf(shadowMat);
		glTranslatef(0, 0, 6.675);
		passengerRamp(true);
	glPopMatrix();
}

//-- Initialize OpenGL parameters ------------------------------------------
void initialize(void) {
	float white[4]  = {1., 1., 1., 1.};

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

//	Define light's diffuse, specular properties
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);	//Default, only for LIGHT0
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);	//Default, only for LIGHT0
 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	// Load Textures
	glGenTextures(3, texId);
	

	glBindTexture(GL_TEXTURE_2D, texId[0]);
	loadTGA("../Textures/Sky.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glBindTexture(GL_TEXTURE_2D, texId[1]);
	loadTGA("../Textures/Grass.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glBindTexture(GL_TEXTURE_2D, texId[2]);
	loadTGA("../Textures/Wood planks.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);


	// Start frame counter
	glutTimerFunc(0, tick, 0);
}

//-- Display: --------------------------------------------------------------
//-- This is the main display module containing function calls for generating
//-- the scene.
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt (camX, camY, camZ, 
			   camX + cos(camElev) * sin(camYaw), camY + sin(camElev), camZ + cos(camElev) * cos(camYaw), 
			   0., 1., 0.);
	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	setScene();

	glutSwapBuffers();	//Double buffered animation
}

//-- Main: Initialize glut window and register call backs ------------------
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1280, 720); 
	glutInitWindowPosition(0, 0);
	glutCreateWindow("CarnivalRide");
	initialize();

	glutDisplayFunc(display); 
    glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
