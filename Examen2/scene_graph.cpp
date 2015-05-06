#include <iostream>
#include <GL\freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "scene_graph.h"

SceneGraph::SceneGraph()
{
	this->root = 0;
}
SceneGraph::SceneGraph(SceneNode *root)
{
	this->root = root;
}
SceneGraph::~SceneGraph()
{
	delete this->root;
}

void SceneGraph::draw()
{
	glPushMatrix();
		this->draw(this->root);
	glPopMatrix();
}

void SceneGraph::draw(SceneNode *node)
{
	glPushMatrix();
		glMultMatrixf(glm::value_ptr(node->incrTransfMat));
		glPushMatrix();
			glMultMatrixf(glm::value_ptr(node->instTransfMat));
			node->draw();
		glPopMatrix();
		std::list<SceneNode *>::iterator it;
		for (it = node->child.begin(); it != node->child.end(); it++)
		{
			this->draw((*it));
		}
	glPopMatrix();
}