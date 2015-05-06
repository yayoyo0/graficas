#ifndef _CONE_H_
#define _CONE_H_

#include "scene_node.h"

class Cone : public SceneNode
{
public:
	double base;
	double altura;

public:
	Cone();
	Cone(std::string name);
	~Cone();
	void draw();
};

#endif