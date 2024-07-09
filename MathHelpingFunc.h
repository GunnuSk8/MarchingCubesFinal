#pragma once

#include<cmath>
#include<iostream>
#include "HelpingDataStructs.h"


constexpr static float Max(float a, float b);

constexpr static float Min(float a, float b);

float Magnitude(Vector3D& a);//again i do not know why static does not work here

constexpr static float SquareMagnitude(Vector3D& a, Vector3D& b);

static float DistanceBetweenPoints(Vector3D& a, Vector3D& b);

constexpr static float Power(float a, int b);
