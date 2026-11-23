//  Characters.h
//  Header file for Characters.cpp
//
//  Jared Melchers (2026)

#include <cmath>
#include <GL/freeglut.h>
#include "Characters.h"

// Eye stalk
// The eye stalk of the alien.
void eyeStalk(float angle) {
    // This is not used but it is necesary for GLU objects
    GLUquadric *q;
    q = gluNewQuadric();

    glRotatef(angle, 0, 0, 1);
    glTranslatef(0, .25, 0);
    glPushMatrix();
        // Whites
        glColor3f(1, 1, 1);
        glScalef(.1, .1, .1);
        gluSphere(q, .5, 12, 12);
    glPopMatrix();
        // Pupil
    glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(0, .0, .05);
        glScalef(.03, .03, .03);
        gluSphere(q, .5, 8, 8);
    glPopMatrix();

    glPushMatrix();
        // Stalk
        glColor3f(0, 1, 0);
        glScalef(.05, .3, .05);
        glRotatef(90, 1, 0, 0);
        gluCylinder(q, .5, .5, 1, 12, 1);
    glPopMatrix();
}

// Alien
// A small green alien with params for animations, by default the animations are set to 0
void alien(int eyeAnimIndex) {
    // This is not used but it is necesary for GLU objects
    GLUquadric *q;
    q = gluNewQuadric();
    
    glPushMatrix();
        // Left eye
        glTranslatef(.0388, .7449, 0);
        eyeStalk(-30 + 10 * sin(eyeAnimIndex * .1 * M_PI));
    glPopMatrix(); 

    glPushMatrix();
        // Right eye
        glTranslatef(-.0388, .7449, 0);
        eyeStalk(30 - 10 * sin(eyeAnimIndex * .1 * M_PI));
    glPopMatrix(); 


    glColor3f(0, 1, 0);
    glPushMatrix();
        // Head
        glTranslatef(0, .6, 0);
        glScalef(.3, .3, .3);
        gluSphere(q, .5, 16, 16);
    glPopMatrix();

    glPushMatrix();
        // Body
        glTranslatef(0, .25, 0);
        glScalef(.5, .5, .5);
        gluSphere(q, .5, 16, 16);
    glPopMatrix();
}