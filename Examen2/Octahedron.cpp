#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

#include "Octahedron.h"
#include "scene_node.h"

Octahedron::Octahedron() : SceneNode("no-name")
{
}

Octahedron::Octahedron(std::string name) : SceneNode(name)
{
}

Octahedron::~Octahedron()
{
}

void Octahedron::draw()
{
	glutWireOctahedron();
}