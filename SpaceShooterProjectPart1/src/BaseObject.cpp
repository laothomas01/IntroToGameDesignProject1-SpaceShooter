#include "ofApp.h"
BaseObject::BaseObject()
{
	//trans = initial position
	trans = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	rotation = 0.0;
}
void BaseObject::setPosition(glm::vec3 pos)
{
	trans = pos;
}

