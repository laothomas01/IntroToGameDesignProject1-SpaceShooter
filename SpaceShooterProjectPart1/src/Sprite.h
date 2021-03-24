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
};