#pragma once
#include<vector>
#include<execution>
#include<GLFW/glfw3.h>
#include"HelpingDataStructs.h"
#include "DrawingHelpingFunc.h"
#include "tables.h"

inline int rez = 20;
inline float isovalue = 0.05;

static std::vector<std::vector<std::vector<point>>> gridPt(rez, std::vector<std::vector<point>>(rez, std::vector<point>(rez)));
inline float halfIncrement = (float)1 / ((float)2 * (float)rez);
inline float fullIncrement = 2 * halfIncrement;

static float function(float x, float y, float z); //example function

static int getCubeIndex(int x, int y, int z);

static point InterpolationPoint(point a, point b);

//function to get coord for the mid points of the edges
static std::vector<point> getCoordForEdgeMidPt(int px, int py, int pz);

void GridIntensityUpdate();

void GridInit();

void MarchingCubes();

