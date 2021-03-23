#pragma once

#include "ofMain.h"
#include "ofxGui.h"
// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//Shape Class
class BaseObject
{
public:
	BaseObject();
	//pos	scale
	glm::vec3 trans, scale;
	
	float rotation = 180.0;
	//glm::vec3 headVector = glm::vec3(0, 1, 0);
	bool bSelected;

	//use for something
	void setPosition(glm::vec3);


	glm::mat4 getMatrix()
	{
		//make sure to make use of pos variable
		glm::mat4 transl = glm::translate(glm::mat4(1.0), glm::vec3(trans));

		//rotate identity matrix
		glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
		//matrix transformation sequence: translate, then rotate
		glm::mat4 T = transl * rot;
		return T;
	}
	glm::vec3 heading() {
		glm::vec3 h = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::vec4(0, 1, 0, 1);
		return glm::normalize(h);
	}






};