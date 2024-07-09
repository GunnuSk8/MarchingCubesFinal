#pragma once
#include<GLFW/glfw3.h>
#include "HelpingDataStructs.h"
#include "MathHelpingFunc.h"
#include<iostream>

static void DrawPoint(Vector3D position, float r , float g , float b , float a , float particleSize );

void DrawPoint(point position, float r , float g , float b , float a , float particleSize );


static void DrawLine(Vector3D& p1, Vector3D& p2, float r , float g , float b , float a );

void DrawLine(point& p1, point& p2, float r, float g, float b, float a); //i dont know why this does not work with static

static float halfBoundSizeX = 0.8f;
static float halfBoundSizeY = 0.8f;
static void DrawBoundingBox();

static float halfBoundSizeX3D = 0.5;
static float halfBoundSizeY3D = 0.5;
static float halfBoundSizeZ3D = 0.5;
void DrawBoundingBox3D();

static void DrawCircle(Vector3D p, float radius , int mode );

static void DrawCircleBoundary(Vector3D p, float radius, float r, float g, float b, float a);

static void DrawArrow(Vector3D& p, Vector3D& gradient);



