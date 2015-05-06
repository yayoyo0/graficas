#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "scene_node.h"

class Sphere : public SceneNode
{
public:
	double radius;
public:
	Sphere();
	Sphere(std::string name);
	~Sphere();
	void draw();
};

#endif