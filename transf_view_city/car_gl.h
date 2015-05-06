#ifndef _CAR_GL_H_
#define _CAR_GL_H_

#include "point.h"
#include "grid_gl.h"

class CarGL
{
public:
	double size;
	Point *loc;
	GridGL *grid;	// The car's highway
	// Car's Displacement in the grid:
	int iFrom;		// from i-row
	int jFrom;		// from j-column
	int iTo;		// To i-row
	int jTo;		// To j-column
	double deltaT;
	int displacement;	// 0 - along +X, 1 - along -X, 2 - along +Z, 3 - along -Z
public:
	CarGL(double size);
	~CarGL();
	void animate();
	void nextStep();
	void draw();
	void addGrid(GridGL *grid);
	void nextDisplacement();
	int nextDisplacement(int *arr, int n);
};

#endif