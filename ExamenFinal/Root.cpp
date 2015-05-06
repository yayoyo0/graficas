#include <iostream>
#include <cmath>
#include <GL\freeglut.h>

#include "Root.h"
#include "scene_node.h"

Root::Root() : SceneNode("no-name")
{
}

Root::Root(std::string name) : SceneNode(name)
{
}

Root::~Root()
{
}

void Root::draw()
{

}