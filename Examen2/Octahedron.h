#ifndef _OCTAHEDRON_H_
#define _OCTAHEDRON_H_

#include "scene_node.h"

class Octahedron : public SceneNode
{
public:
	Octahedron();
	Octahedron(std::string name);
	~Octahedron();
	void draw();
};

#endif