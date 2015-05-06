#ifndef _ROOT_H_
#define _ROOT_H_

#include "scene_node.h"

class Root : public SceneNode
{
public:
	Root();
	Root(std::string name);
	~Root();
	void draw();
};

#endif