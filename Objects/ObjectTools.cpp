//  ObjectTools.cpp
//  Various tools for creating objects
//
//  Jared Melchers (2026)

#include <cmath>
#include <GL/freeglut.h>
#include "ObjectTools.h"


// Face normals
// Takes three vertices and returns the normal of the face they produce
void faceNormal(float* normX, float* normY, float* normZ,
                float x1, float y1, float z1,
                float x2, float y2, float z2,
                float x3, float y3, float z3) {
    
    *normX = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
    *normY = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
    *normZ = x1 * (y2  - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
}

// Vertex normals
// Takes four vertices (The centre vertex followed by three surrounding vertices in an anti-clockwise direction)
// and returns the normal of the centre vertex.
void vertexNormal2F(float* normX, float* normY, float* normZ,
                    float x1, float y1, float z1,
                    float x2, float y2, float z2,
                    float x3, float y3, float z3,
                    float x4, float y4, float z4) {
    
    float normX1, normY1, normZ1, normX2, normY2, normZ2; // Normals for the two planes
    float unitScaleFactor; // Factor to convert vectors to a unit vector

    faceNormal(&normX1, &normY1, &normZ1,
               x2, y2, z2,
               x3, y3, z3,
               x1, y1, z1);
 
    unitScaleFactor = sqrt(normX1*normX1 + normY1*normY1 + normZ1*normZ1); // These need to be normalised so the result isn't weighted
    normX1 = normX1 * unitScaleFactor;
    normY1 = normY1 * unitScaleFactor;
    normZ1 = normZ1 * unitScaleFactor;


    faceNormal(&normX2, &normY2, &normZ2,
               x3, y3, z3,
               x4, y4, z4,
               x1, y1, z1);

    unitScaleFactor = sqrt(normX2*normX2 + normY2*normY2 + normZ2*normZ2); // These need to be normalised so the result isn't weighted
    normX2 = normX2 * unitScaleFactor;
    normY2 = normY2 * unitScaleFactor;
    normZ2 = normZ2 * unitScaleFactor;

    *normX = normX1 + normX2;
    *normY = normY1 + normY2;
    *normZ = normZ1 + normZ2;
}