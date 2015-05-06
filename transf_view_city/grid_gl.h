#ifndef _GRID_GL_H_
#define _GRID_GL_H_

#include "point.h"

class GridGL
{
public:
	int m, n;
	double size;
	Point ***e;
public:
	GridGL(int m, int n, double size);
	~GridGL();
	void draw();
};

#endif