#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

#include "Cilinder.h"
#include "scene_node.h"

Cilinder::Cilinder() : SceneNode("no-name")
{
	this->radio = 0.2;
	this->altura = 0.3;
}
Cilinder::Cilinder(std::string name) : SceneNode(name)
{
	this->radio = 0.2;
	this->altura = 0.3;
}

Cilinder::~Cilinder()
{
	//delete this;
}

void Cilinder::draw()
{
	glutWireCylinder(this->radio, this->altura, 20, 20);
}