#ifndef _CUBE_H_
#define _CUBE_H_

#include "scene_node.h"

class Box : public SceneNode
{
public:
	double size;
public:
	Box();
	Box(std::string name);
	~Box();
	void draw();
};

#endif