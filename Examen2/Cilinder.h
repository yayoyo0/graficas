#ifndef _CILINDER_H_
#define _CILINDER_H_

#include "scene_node.h"

class Cilinder : public SceneNode
{
public:
	double radio;
	double altura;

public:
	Cilinder();
	Cilinder(std::string name);
	~Cilinder();
	void draw();
};

#endif