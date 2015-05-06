#ifndef _TORUS_H_
#define _TORUS_H_

#include "scene_node.h"

class Torus : public SceneNode
{
public:
	double radioInt;
	double radioExt;

public:
	Torus();
	Torus(std::string name);
	~Torus();
	void draw();
};

#endif