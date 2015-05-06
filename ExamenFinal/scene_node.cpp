#include "scene_node.h"

SceneNode::SceneNode()
{
	this->name = "no-name";
}
SceneNode::SceneNode(std::string name)
{
	this->name = name;
}
SceneNode::~SceneNode()
{
	std::list<SceneNode *>::iterator it;
	for (it = this->child.begin(); it != this->child.end(); it++)
	{
		delete (*it);
	}
}
void SceneNode::addChild(SceneNode *node)
{
	this->child.push_back(node);
}

void SceneNode::incrementalTranslate(float x, float y, float z)
{
	this->incrTransfMat = glm::translate(this->incrTransfMat, glm::vec3(x, y, z));
}

void SceneNode::incrementalRotate(float angle, float x, float y, float z)
{
	this->incrTransfMat = glm::rotate(this->incrTransfMat, angle, glm::vec3(x, y, z));
}

void SceneNode::instanceRotate(float angle, float x, float y, float z)
{
	this->instTransfMat = glm::rotate(this->instTransfMat, angle, glm::vec3(x, y, z));
}

void SceneNode::instanceTranslate(float x, float y, float z)
{
	this->instTransfMat = glm::translate(this->instTransfMat, glm::vec3(x, y, z));
}

void SceneNode::instanceScale(float sx, float sy, float sz)
{
	this->instTransfMat = glm::scale(this->instTransfMat, glm::vec3(sx, sy, sz));
}

