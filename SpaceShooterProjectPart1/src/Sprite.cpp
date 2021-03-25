#include "ofApp.h"
Sprite::Sprite()
{
	speed = 0;
	velocity = glm::vec3(0, 0, 0);
	lifespan = -1;
	birthtime = 0;
	bSelected = false;
	haveImage = false;
	name = "UnamedSprite";
	width = 60;
	height = 80;
	
	
}
// Return a sprite's age in milliseconds
float Sprite::age() {
	//in-game time - sprite's birthtime
	return (ofGetElapsedTimeMillis() - birthtime);
}
//  Set an image for the sprite. If you don't set one, a rectangle
//  gets drawn.
/*
Set the image before calling Sprite::draw
*/

void Sprite::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = image.getWidth();
	height = image.getHeight();
}
//  Render the sprite
//
void Sprite::draw() {

	ofSetColor(255, 255, 255, 255);

	// draw image centered and add in translation amount
	if (haveImage) {
		image.draw(-width / 2.0 + trans.x, -height / 2.0 + trans.y);
	}
	else {
		// in case no image is supplied, draw something.
		ofSetColor(255, 0, 0);
		ofDrawRectangle(-width / 2.0 + trans.x, -height / 2.0 + trans.y, width, height);
	}
}


