#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

#include "Torus.h"
#include "scene_node.h"

Torus::Torus() : SceneNode("no-name")
{
	this->radioInt = 0.5;
	this->radioExt = 0.6;
}
Torus::Torus(std::string name) : SceneNode(name)
{
	this->radioInt = 0.5;
	this->radioExt = 0.6;
}

Torus::~Torus()
{
	//delete this;
}

void Torus::draw()
{
	glutWireTorus(this->radioInt, this->radioExt, 20, 20);
}