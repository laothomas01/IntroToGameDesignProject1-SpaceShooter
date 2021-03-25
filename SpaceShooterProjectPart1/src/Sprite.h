#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "BaseObject.h"
class Sprite : public BaseObject
{
public:
	float speed; // pixels/sec
	float birthtime; // elapsed time in ms
	float lifespan; //time in ms
	float width, height;
	float rotation = 0.0;
	
	glm::vec3 velocity; // pixels/sec
	ofImage image;
	bool haveImage;
	string name;
	Sprite();
	void draw();
	float age();
	void setImage(ofImage);
	/*
	all other attributes belong to BaseObject
	*/

	glm::vec3 Spriteheading() {
		glm::vec3 h = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::vec4(0, 1, 0, 1);
		return glm::normalize(h);
	}
	
};