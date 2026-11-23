//  ObjectTools.h
//  Header file for ObjectTools.cpp
//
//  Jared Melchers (2026)

void faceNormal(float* normX, float* normY, float* normZ,
                float x1, float y1, float z1,
                float x2, float y2, float z2,
                float x3, float y3, float z3);

void vertexNormal2F(float* normX, float* normY, float* normZ,
                    float x1, float y1, float z1,
                    float x2, float y2, float z2,
                    float x3, float y3, float z3,
                    float x4, float y4, float z4);