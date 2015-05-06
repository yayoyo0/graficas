#ifndef _DODECAHEDRON_H_
#define _DODECAHEDRON_H_

#include "scene_node.h"

class Dodecahedron : public SceneNode
{
public:

public:
	Dodecahedron();
	Dodecahedron(std::string name);
	~Dodecahedron();
	void draw();
};

#endif