#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

#include "Cone.h"
#include "scene_node.h"

Cone::Cone() : SceneNode("no-name")
{
	this->base = 0.2;
	this->altura = 0.3;
}
Cone::Cone(std::string name) : SceneNode(name)
{
	this->base = 0.2;
	this->altura = 0.3;
}

Cone::~Cone()
{
	//delete this;
}

void Cone::draw()
{
	glutWireCone(this->base, this->altura, 20, 20);
}