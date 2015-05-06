#include <GL\glew.h>
#include <GL\freeglut.h>

#include "grid_gl.h"
#include "point.h"

GridGL::GridGL(int m, int n, double size)
{
	this->m = m;
	this->n = n;
	this->size = size;
	this->e = new Point **[m + 1];
	for (int i = 0; i <= m; i++)
	{
		this->e[i] = new Point *[n + 1];
	}
	double x;
	double z = 0.;
	for (int i = 0; i <= m; i++)
	{
		x = 0.;
		z = (this->m * this->size + this->size) * i;
		for (int j = 0; j <= this->n; j++)
		{
			x = (this->n * this->size + this->size) * j;
			this->e[i][j] = new Point(x, 0., z);
		}
	}
}
GridGL::~GridGL()
{

}
void GridGL::draw()
{
	for (int i = 0; i <= this->m; i++)
	{
		for (int j = 0; j <= this->n; j++)
		{
			glPushMatrix();
			glTranslatef(e[i][j]->x, 0., e[i][j]->z);
			glutSolidSphere(size / 10., 10, 10);
			glPopMatrix();
		}
	}
}