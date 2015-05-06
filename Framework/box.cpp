#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

#include "box.h"
#include "scene_node.h"

Box::Box() : SceneNode("no-name")
{
	this->size = 1.;
}
Box::Box(std::string name) : SceneNode(name)
{
	this->size = 1.;
}

Box::~Box()
{

}

void Box::draw()
{
	glutWireCube(this->size);
}