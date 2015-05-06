#include <GL\glew.h>
#include <GL\freeglut.h>
#include "car_gl.h"
#include "point.h"

CarGL::CarGL(double size)
{
	this->size = size;
	this->loc = new Point();
	this->iFrom = 0;
	this->jFrom = 0;
	this->iTo = 0;
	this->jTo = 1;
	this->deltaT = 0.05;
	this->displacement = 0;	// displacement in +X
}

CarGL::~CarGL()
{

}

void CarGL::addGrid(GridGL *grid)
{
	this->grid = grid;
}

void CarGL::animate()
{
	Point *p = this->grid->e[this->iTo][this->jTo];
	if (this->displacement == 0)
	{
		if (this->loc->x < p->x)
		{
			this->loc->x = this->loc->x + this->deltaT;
		}
		else
		{
			this->nextDisplacement();
		}
	}
	else if (this->displacement == 1)
	{
		if (this->loc->x > p->x)
		{
			this->loc->x = this->loc->x - this->deltaT;
		}
		else
		{
			this->nextDisplacement();
		}
	}
	else if (this->displacement == 2)
	{
		if (this->loc->z < p->z)
		{
			this->loc->z = this->loc->z + this->deltaT;
		}
		else
		{
			this->nextDisplacement();
		}
	}
	else if (this->displacement == 3)
	{
		if (this->loc->z > p->z)
		{
			this->loc->z = this->loc->z - this->deltaT;
		}
		else
		{
			this->nextDisplacement();
		}
	}
}

void CarGL::draw()
{
	glPushMatrix();
	glTranslatef(this->loc->x, this->loc->y, this->loc->z);
	glutSolidCube(this->size);
	glPopMatrix();
}

void CarGL::nextDisplacement()
{
	int disp;
	int *arr = new int[2];
	if (this->displacement == 0)
	{
		if (this->jTo == this->grid->n)
		{
			if (this->iTo == 0)
			{
				disp = 2;
				this->iFrom = this->iTo;
				this->jFrom = this->jTo;
				this->iTo = this->iTo + 1;
				this->jTo = this->jTo;
			}
			else if (this->iTo == this->grid->m)
			{
				disp = 3;
				this->iFrom = this->iTo;
				this->jFrom = this->jTo;
				this->iTo = this->iTo - 1;
				this->jTo = this->jTo;
			}
			else
			{
				arr[0] = 0;
				arr[1] = 1;
				disp = nextDisplacement(arr, 2);
				if (disp == 2)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo + 1;
					this->jTo = this->jTo;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo - 1;
					this->jTo = this->jTo;
				}
			}
		}
		else
		{
			if (this->iTo == 0)
			{
				arr[0] = 1;
				arr[1] = 3;
				disp = nextDisplacement(arr, 2);
				if (disp == 0)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo + 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo + 1;
					this->jTo = this->jTo;
				}
			}
			else if (this->iTo == this->grid->m)
			{
				arr[0] = 1;
				arr[1] = 2;
				disp = nextDisplacement(arr, 2);
				if (disp == 0)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo + 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo - 1;
					this->jTo = this->jTo;
				}
			}
			else
			{
				arr[0] = 1;
				disp = nextDisplacement(arr, 1);
				if (disp == 0)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo + 1;
				}
				else if (disp == 2)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo + 1;
					this->jTo = this->jTo;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo - 1;
					this->jTo = this->jTo;
				}
			}
		}
	}
	else if (this->displacement == 1)
	{
		if (this->jTo == 0)
		{
			if (this->iTo == 0)
			{
				disp = 2;
				this->iFrom = this->iTo;
				this->jFrom = this->jTo;
				this->iTo = this->iTo + 1;
				this->jTo = this->jTo;
			}
			else if (this->iTo == this->grid->m)
			{
				disp = 3;
				this->iFrom = this->iTo;
				this->jFrom = this->jTo;
				this->iTo = this->iTo - 1;
				this->jTo = this->jTo;
			}
			else
			{
				arr[0] = 0;
				arr[1] = 1;
				disp = nextDisplacement(arr, 2);
				if (disp == 2)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo + 1;
					this->jTo = this->jTo;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo - 1;
					this->jTo = this->jTo;
				}
			}
		}
		else
		{
			if (this->iTo == 0)
			{
				arr[0] = 0;
				arr[1] = 3;
				disp = nextDisplacement(arr, 2);
				if (disp == 1)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo - 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo + 1;
					this->jTo = this->jTo;
				}
			}
			else if (this->iTo == this->grid->m)
			{
				arr[0] = 0;
				arr[1] = 2;
				disp = nextDisplacement(arr, 2);
				if (disp == 1)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo - 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo - 1;
					this->jTo = this->jTo;
				}
			}
			else
			{
				arr[0] = 0;
				disp = nextDisplacement(arr, 1);
				if (disp == 1)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo - 1;
				}
				else if (disp == 2)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo + 1;
					this->jTo = this->jTo;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo - 1;
					this->jTo = this->jTo;
				}
			}
		}
	}
	else if (this->displacement == 2)
	{
		if (this->iTo == this->grid->m)
		{
			if (this->jTo == 0)
			{
				disp = 0;
				this->iFrom = this->iTo;
				this->jFrom = this->jTo;
				this->iTo = this->iTo;
				this->jTo = this->jTo + 1;
			}
			else if (this->jTo == this->grid->n)
			{
				disp = 1;
				this->iFrom = this->iTo;
				this->jFrom = this->jTo;
				this->iTo = this->iTo;
				this->jTo = this->jTo - 1;
			}
			else
			{
				arr[0] = 2;
				arr[1] = 3;
				disp = nextDisplacement(arr, 2);
				if (disp == 0)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo + 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo - 1;
				}
			}
		}
		else
		{
			if (this->jTo == 0)
			{
				arr[0] = 1;
				arr[1] = 3;
				disp = nextDisplacement(arr, 2);
				if (disp == 0)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo + 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo + 1;
					this->jTo = this->jTo;
				}
			}
			else if (this->jTo == this->grid->n)
			{
				arr[0] = 0;
				arr[1] = 2;
				disp = nextDisplacement(arr, 2);
				if (disp == 1)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo - 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo - 1;
					this->jTo = this->jTo;
				}
			}
			else
			{
				arr[0] = 3;
				disp = nextDisplacement(arr, 1);
				if (disp == 0)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo + 1;
				}
				else if (disp == 1)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo - 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo + 1;
					this->jTo = this->jTo;
				}
			}
		}
	}
	else if (this->displacement == 3)
	{
		if (this->iTo == 0)
		{
			if (this->jTo == 0)
			{
				disp = 0;
				this->iFrom = this->iTo;
				this->jFrom = this->jTo;
				this->iTo = this->iTo;
				this->jTo = this->jTo + 1;
			}
			else if (this->jTo == this->grid->n)
			{
				disp = 1;
				this->iFrom = this->iTo;
				this->jFrom = this->jTo;
				this->iTo = this->iTo;
				this->jTo = this->jTo - 1;
			}
			else
			{
				arr[0] = 2;
				arr[1] = 3;
				disp = nextDisplacement(arr, 2);
				if (disp == 0)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo + 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo - 1;
				}
			}
		}
		else
		{
			if (this->jTo == 0)
			{
				arr[0] = 1;
				arr[1] = 2;
				disp = nextDisplacement(arr, 2);
				if (disp == 0)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo + 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo - 1;
					this->jTo = this->jTo;
				}
			}
			else if (this->jTo == this->grid->n)
			{
				arr[0] = 0;
				arr[1] = 2;
				disp = nextDisplacement(arr, 2);
				if (disp == 1)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo - 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo - 1;
					this->jTo = this->jTo;
				}
			}
			else
			{
				arr[0] = 2;
				disp = nextDisplacement(arr, 1);
				if (disp == 0)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo + 1;
				}
				else if (disp == 1)
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo;
					this->jTo = this->jTo - 1;
				}
				else
				{
					this->iFrom = this->iTo;
					this->jFrom = this->jTo;
					this->iTo = this->iTo - 1;
					this->jTo = this->jTo;
				}
			}
		}
	}
	this->displacement = disp;
}

int CarGL::nextDisplacement(int *arr, int n)
{
	int disp;
	bool flag;
	while (true)
	{
		flag = true;
		disp = rand() % 4;
		for (int i = 0; i < n; i++)
		{
			if (disp == arr[i])
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			break;
		}
		else
		{

		}
	}
	return disp;
}
