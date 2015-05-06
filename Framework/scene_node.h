#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include <string>
#include <list>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SceneNode
{
public:
	std::string name;
	glm::mat4 incrTransfMat;
	glm::mat4 instTransfMat;
	std::list<SceneNode *> child;
public:
	SceneNode();
	SceneNode(std::string name);
	~SceneNode();
	void addChild(SceneNode *node);
	virtual void draw() = 0;
	void incrementalTranslate(float x, float y, float z);
	void incrementalRotate(float angle, float x, float y, float z);
	void instanceRotate(float angle, float x, float y, float z);
	void instanceTranslate(float x, float y, float z);
	void instanceScale(float sx, float sy, float sz);
};

#endif