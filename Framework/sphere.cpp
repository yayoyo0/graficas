#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

#include "sphere.h"
#include "scene_node.h"

Sphere::Sphere() : SceneNode("no-name")
{
	this->radius = 1.;
}
Sphere::Sphere(std::string name) : SceneNode(name)
{
	this->radius = 1.;
}
Sphere::~Sphere()
{

}
void Sphere::draw()
{
	glutWireSphere(this->radius, 20, 20);
}