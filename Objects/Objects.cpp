//  CentreRose.cpp
//  Functions that define various models
//
//  Jared Melchers (2026)

// Includes
#include <cmath>
#include <GL/freeglut.h>
#include "Objects.h"
#include "ObjectTools.h"
#include "Characters.h"
#include <cstdio> // !! For debuging, remove later !!


// Centre rose
// The sides of the model that will form the centre of the ride
void centreRose(bool shadow) {
	float white[4] = {1, 1, 1, 1};
	float black[4] = {0, 0, 0, 1};

    float radius;
    float xcoords[41];
    float zcoords[41];
	float normX, normY, normZ; //variables for storing the normals

	// This is not used but it is necesary for GLU objects
    GLUquadric *q;
    q = gluNewQuadric();
    
    for (int i = 0; i <= 40; i++) {
        radius = cos(8 * (i * 0.05 * M_PI)) / 10 + 1 ;
        xcoords[i] = radius * sin(i*0.05*M_PI);
        zcoords[i] = radius * cos(i*0.05*M_PI);
    }

	if (shadow) {
		glColor3f(0, 0, 0);
	} else {
		glColor3f(1, 0, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
	}

	glRotatef(22.5, 0, 1, 0);
	glBegin(GL_QUAD_STRIP); // Base of the rose
	for (int i = 0; i <= 40; i++) {
		if (i == 0 || i == 40) {
			glNormal3f(0, 0, 1); // At the origin the normal is in the z direction
		} else {
			vertexNormal2F(&normX, &normY, &normZ,
						xcoords[i], 0, zcoords[i],
						xcoords[i+1], 0, zcoords[i+1],
						xcoords[i], 1, zcoords[i],
						xcoords[i-1], 0, zcoords[i-1]);
			glNormal3f(normX, normY, normZ);
		}
		glVertex3f(xcoords[i], 0, zcoords[i]);
		glVertex3f(xcoords[i], .9, zcoords[i]);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP); // Bevel edge
		for (int i = 0; i <= 40; i++) {
			if (i == 0 || i == 40) {
				normX = 0, normY = 0, normZ = 1; // At the origin the normal is in the z direction
			} else {
				vertexNormal2F(&normX, &normY, &normZ,
							xcoords[i], 0, zcoords[i],
							xcoords[i+1], 0, zcoords[i+1],
							xcoords[i], 1, zcoords[i],
							xcoords[i-1], 0, zcoords[i-1]);
			}
			glNormal3f(normX, normY, normZ);
			glVertex3f(xcoords[i], .9, zcoords[i]);
			glNormal3f(normX, sqrt(normX*normX + normZ*normZ), normZ); // This is a trick to make the normal point 45 degrees up
			glVertex3f(xcoords[i]*.9707, .9707, zcoords[i]*.9707);
		}
	glEnd();
	glBegin(GL_QUAD_STRIP); // Bevel top
		for (int i = 0; i <= 40; i++) {
			if (i == 0 || i == 40) {
				normX = 0, normY = 0, normZ = 1; // At the origin the normal is in the z direction
			} else {
				vertexNormal2F(&normX, &normY, &normZ,
							xcoords[i], 0, zcoords[i],
							xcoords[i+1], 0, zcoords[i+1],
							xcoords[i], 1, zcoords[i],
							xcoords[i-1], 0, zcoords[i-1]);
			}
			glNormal3f(normX, sqrt(normX*normX + normZ*normZ), normZ); // This is a trick to make the normal point 45 degrees up
			glVertex3f(xcoords[i]*.9707, .9707, zcoords[i]*.9707);
			glNormal3f(0, 1, 0); // The top points strait up
			glVertex3f(xcoords[i]*.9, 1, zcoords[i]*.9);
		}
	glEnd();
	glNormal3f(0, 1, 0); // The top points strait up
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, 1, 0);
		for (int i = 0; i <= 40; i++) {
			glVertex3f(xcoords[i]*.9, 1, zcoords[i]*.9);
		}
	glEnd();

	
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
}

// Passenger pods
// The pods that the passengers ride in.
void passengerPod(bool shadow) {
	if (shadow) {
		glColor3f(0, 0, 0);
	} else {
		glColor3f(.65, .65, .65);
	}
	glPushMatrix(); // Base
		glTranslatef(0, 0.025, 0);
		glScalef(1, .05, 1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix(); // Back wall
		glTranslatef(-.475, .15, 0);
		glScalef(.05, .3, 1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix(); // Inner wall
		glTranslatef(0, .15, -.475);
		glScalef(1, .3, .05);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix(); // Front wall
		glTranslatef(.475, .15, 0);
		glScalef(.05, .3, 1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix(); // Rear outer wall
		glTranslatef(-.25, .15, .475);
		glScalef(.5, .3, .05);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix(); // Front outer wall
		glTranslatef(.4, .15, .475);
		glScalef(.2, .3, .05);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix(); // seat
		glTranslatef(-.35, .1, 0);
		glScalef(.3, .2, 1);
		glutSolidCube(1);
	glPopMatrix();
	glPushMatrix(); // Beam connector
		glTranslatef(0, .15, -.65);
		glScalef(.3, .3, .3);
		glutSolidCube(1);
	glPopMatrix();
}

// Beam
// 
void beam(bool shadow) {
	// This is not used but it is necesary for GLU objects
    GLUquadric *q;
    q = gluNewQuadric();

	if (shadow) {
		glColor3f(0, 0, 0);
	} else {
		glColor3f(.9, .9, .9);
	}
	glScalef(.25, .25, 4.25);
	gluCylinder(q, .5, .5, 1, 12, 1);
}

void arm(float angle, int passengerAnimIndex, bool showPassenger, bool shadow) {
	float angleRad = 2 * M_PI * angle / 360;
	float podYOffset = .2 + 5 * sin(angleRad);
	float podZOffset = .65 + 5 * cos(angleRad);
	glPushMatrix(); // Beam
		glTranslatef(0, .35, 0);
		glRotatef(-angle, 1, 0, 0);
		glTranslatef(0, 0, .75);
		beam(shadow);
	glPopMatrix();
	glPushMatrix(); // Pod
		glTranslatef(0, podYOffset, podZOffset);
		if (showPassenger) {
			glPushMatrix(); // Passenger 1
				glTranslatef(-.3, .2125, .225);
				glRotatef(90, 0, 1, 0);
				glScalef(.5, .5, .5);
				alien(passengerAnimIndex);
			glPopMatrix();
			glPushMatrix(); // Passenger 2
				glTranslatef(-.3, .2125, -.225);
				glRotatef(90, 0, 1, 0);
				glScalef(.5, .5, .5);
				alien(passengerAnimIndex);
			glPopMatrix();
		}
		passengerPod(shadow);
	glPopMatrix();
}

void passengerRamp(bool shadow) {
	if (shadow) {
		glColor3f(0, 0, 0);
	} else {
		glColor3f(1,1,1);
	}
	glBegin(GL_QUADS); // Top
		glTexCoord2f(0, 1);
		glVertex3f(-.5, .25, -.5);
		glTexCoord2f(1, 1);
		glVertex3f(.5, .25, -.5);
		glTexCoord2f(1, 0);
		glVertex3f(.5, .25, .5);
		glTexCoord2f(0, 0);
		glVertex3f(-.5, .25, .5);
	glEnd();
	for (float i = -.5; i <= .5; i++) { // Sides
		glBegin(GL_QUADS);
			glTexCoord2f(.25, 1);
			glVertex3f(i, .25, .5);
			glTexCoord2f(.25, 0);
			glVertex3f(i, .25, -.5);
			glTexCoord2f(0, 0);
			glVertex3f(i, 0, -.5);
			glTexCoord2f(0, 2);
			glVertex3f(i, 0, 1.5);
		glEnd();
	}
	// Back
	glBegin(GL_QUADS);
		glTexCoord2f(.25, 1);
		glVertex3f(-.5, .25, -.5);
		glTexCoord2f(.25, 0);
		glVertex3f(.5, .25, -.5);
		glTexCoord2f(0, 0);
		glVertex3f(.5, 0, -.5);
		glTexCoord2f(0, 1);
		glVertex3f(-.5, 0, -.5);
	glEnd();

	// Ramp
	glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(-.5, .25, .5);
		glTexCoord2f(1, 1);
		glVertex3f(.5, .25, .5);
		glTexCoord2f(1, 0);
		glVertex3f(.5, 0, 1.5);
		glTexCoord2f(0, 0);
		glVertex3f(-.5, 0, 1.5);
	glEnd();
}