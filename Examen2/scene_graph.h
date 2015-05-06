#ifndef _SECENE_GRAPH_H_
#define _SECENE_GRAPH_H_

#include "scene_node.h"

class SceneGraph
{
private:
	SceneNode *root;
public:
	SceneGraph();
	SceneGraph(SceneNode *root);
	~SceneGraph();
	void draw();
	void draw(SceneNode *node);
	void draw2(SceneNode *node);
};

#endif