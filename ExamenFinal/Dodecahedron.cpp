#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

#include "Dodecahedron.h"
#include "scene_node.h"

Dodecahedron::Dodecahedron() : SceneNode("no-name")
{
}
Dodecahedron::Dodecahedron(std::string name) : SceneNode(name)
{
}

Dodecahedron::~Dodecahedron()
{
	//delete this;
}

void Dodecahedron::draw()
{
	glutWireDodecahedron();
}