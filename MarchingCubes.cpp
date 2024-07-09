#include"MarchingCubes.h"

static float function(float x, float y, float z) {
	return ((x * x + y * y + z * z ));
}

static int getCubeIndex(int x, int y, int z) {
	int cubeIndex = 0;
	if (gridPt[x][y][z].intensity > isovalue) cubeIndex |= 1;
	if (gridPt[x + 1][y][z].intensity > isovalue) cubeIndex |= 2;
	if (gridPt[x + 1][y][z + 1].intensity > isovalue) cubeIndex |= 4;
	if (gridPt[x][y][z + 1].intensity > isovalue) cubeIndex |= 8;
	if (gridPt[x][y + 1][z].intensity > isovalue) cubeIndex |= 16;
	if (gridPt[x + 1][y + 1][z].intensity > isovalue) cubeIndex |= 32;
	if (gridPt[x + 1][y + 1][z + 1].intensity > isovalue) cubeIndex |= 64;
	if (gridPt[x][y + 1][z + 1].intensity > isovalue) cubeIndex |= 128;

	return cubeIndex;
}

static point InterpolationPoint(point a, point b) {
	point ip;
	ip.x = a.x + (isovalue - a.intensity) * (b.x - a.x) / (b.intensity - a.intensity);
	ip.y = a.y + (isovalue - a.intensity) * (b.y - a.y) / (b.intensity - a.intensity);
	ip.z = a.z + (isovalue - a.intensity) * (b.z - a.z) / (b.intensity - a.intensity);

	return ip;
}

//function to get coord for the mid points of the edges
static std::vector<point> getCoordForEdgeMidPt(int px, int py, int pz) {
	std::vector<point> midPts;
	point temp;
	float x = gridPt[px][py][pz].x;
	float y = gridPt[px][py][pz].y;
	float z = gridPt[px][py][pz].z;
	//0 edge
	temp = InterpolationPoint(gridPt[px][py][pz], gridPt[px + 1][py][pz]);
	midPts.push_back(temp);

	//1 edge
	temp = InterpolationPoint(gridPt[px + 1][py][pz], gridPt[px + 1][py][pz + 1]);
	midPts.push_back(temp);

	//2 edge
	temp = InterpolationPoint(gridPt[px + 1][py][pz + 1], gridPt[px][py][pz + 1]);
	midPts.push_back(temp);

	//3 edge
	temp = InterpolationPoint(gridPt[px][py][pz], gridPt[px][py][pz + 1]);
	midPts.push_back(temp);

	//4 edge
	temp = InterpolationPoint(gridPt[px][py + 1][pz], gridPt[px + 1][py + 1][pz]);
	midPts.push_back(temp);

	//5 edge
	temp = InterpolationPoint(gridPt[px + 1][py + 1][pz], gridPt[px + 1][py + 1][pz + 1]);
	midPts.push_back(temp);

	//6 edge
	temp = InterpolationPoint(gridPt[px + 1][py + 1][pz + 1], gridPt[px][py + 1][pz + 1]);
	midPts.push_back(temp);

	//7 edge
	temp = InterpolationPoint(gridPt[px][py + 1][pz], gridPt[px][py + 1][pz + 1]);
	midPts.push_back(temp);

	//8 edge
	temp = InterpolationPoint(gridPt[px][py][pz], gridPt[px][py + 1][pz]);
	midPts.push_back(temp);

	//9 edge
	temp = InterpolationPoint(gridPt[px + 1][py][pz], gridPt[px + 1][py + 1][pz]);
	midPts.push_back(temp);

	//10 edge
	temp = InterpolationPoint(gridPt[px + 1][py][pz + 1], gridPt[px + 1][py + 1][pz + 1]);
	midPts.push_back(temp);

	//11 edge
	temp = InterpolationPoint(gridPt[px][py][pz + 1], gridPt[px][py + 1][pz + 1]);
	midPts.push_back(temp);

	return midPts;
}

void GridIntensityUpdate() {

	std::for_each(std::execution::par, gridPt.begin(), gridPt.end(), [](std::vector<std::vector<point>>& ptPlane) {

		std::for_each(std::execution::par, ptPlane.begin(), ptPlane.end(), [](std::vector<point>& ptLine) {

			std::for_each(std::execution::par, ptLine.begin(), ptLine.end(), [](point& pt)
				{
					pt.intensity = function(pt.x, pt.y, pt.z);

				});
			});
		});
}

void GridInit() {
	for (int x = 0; x < rez; x++) {
		for (int y = 0; y < rez; y++) {
			for (int z = 0; z < rez; z++) {

				//transforming [0,0,0 to 1,1,1] to [-1,-1,-1 to 1,1,1]
				gridPt[x][y][z].x = ((float)x / (float)rez - 0.5f) * 2 * halfBoundSizeX3D;
				gridPt[x][y][z].y = ((float)y / (float)rez - 0.5f) * 2 * halfBoundSizeY3D;
				gridPt[x][y][z].z = ((float)z / (float)rez - 0.5f) * 2 * halfBoundSizeZ3D;

			}
		}

	}
}

void MarchingCubes() {

	//print the grid points according to their intensity

	for (int x = 0; x < rez; x++) {
		for (int y = 0; y < rez; y++) {
			for (int z = 0; z < rez; z++) {
				glPointSize(4.0f);
				float scale = 0.001;
				//glColor4f();
				//if (gridPt[x][y][z].intensity > isovalue)
					//DrawPoint(gridPt[x][y][z], gridPt[x][y][z].intensity * scale, 0.8, gridPt[x][y][z].intensity * scale, 0.41,4);
			}
			//drawing the grid lines
			glLineWidth(1.0f);
			DrawLine(gridPt[x][y][0], gridPt[x][y][rez - 1],0.1,0.1,0.1,0.51);
			DrawLine(gridPt[x][0][y], gridPt[x][rez - 1][y], 0.1, 0.1, 0.1, 0.51);
			DrawLine(gridPt[0][y][x], gridPt[rez - 1][y][x], 0.1, 0.1, 0.1, 0.51);
		}
	}

	//Marching Cubes
	for (int x = 0; x < rez - 1; x++) {
		for (int y = 0; y < rez - 1; y++) {
			for (int z = 0; z < rez - 1; z++) {


				int cbi = 0;

				//getting the cube index for the particular cube
				cbi = getCubeIndex(x, y, z);

				//getting the midpoints for edges for that cube
				std::vector<point> midPts = getCoordForEdgeMidPt(x, y, z);

				//connecting the edges according to the triTable
				for (int i = 0; triTable[cbi][i] != -1; i += 3) {


					glLineWidth(1.0);

					DrawLine(midPts[triTable[cbi][i]], midPts[triTable[cbi][i + 1]], 1, 1, 0, 0.2f);
					DrawLine(midPts[triTable[cbi][i + 2]], midPts[triTable[cbi][i + 1]], 1, 1, 0, 0.2f);
					DrawLine(midPts[triTable[cbi][i]], midPts[triTable[cbi][i + 2]], 1, 1, 0, 0.2f);

					glColor4f(255.0 / 256.0, 192.0 / 256.0, 203.0 / 256.0, 0.2f);
					glBegin(GL_TRIANGLES);
					glVertex3f(midPts[triTable[cbi][i]].x, midPts[triTable[cbi][i]].y, midPts[triTable[cbi][i]].z);
					glVertex3f(midPts[triTable[cbi][i + 1]].x, midPts[triTable[cbi][i + 1]].y, midPts[triTable[cbi][i + 1]].z);
					glVertex3f(midPts[triTable[cbi][i + 2]].x, midPts[triTable[cbi][i + 2]].y, midPts[triTable[cbi][i + 2]].z);
					glEnd();
				}

			}
		}
	}
	
}

