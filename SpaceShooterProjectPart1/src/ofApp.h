#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"
#include "SpriteSystem.h"
#include "Emitter.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	SpriteSystem *sys;
	ofSoundPlayer Wobble;
	ofSoundPlayer thrusters;
	ofSoundPlayer backingup;
	ofSoundPlayer recharge;
	Emitter *turret = NULL;
	Emitter *enemySpawner = NULL;
	Sprite *sprite = NULL;


	ofImage defaultImage;
	ofImage customImage;
	ofImage background;
	ofImage Minions;
	ofImage DefaultEnemy;


	glm::vec3 mouse_last;
	bool imageLoaded;
	bool soundLoaded;
	bool bHide;
	bool dead;
	float Distance;
	float ContactDistance;
	map<int, bool> keymap;

	ofxFloatSlider rate;
	ofxFloatSlider life;
	ofxVec3Slider velocity;
	ofxLabel screenSize;
	ofxVec3Slider headVect;


	ofxPanel gui;

	glm::vec3 heading() {
		glm::vec3 h = glm::rotate(glm::mat4(1.0), glm::radians(turret->rotation), glm::vec3(0, 0, 1)) * glm::vec4(0, 1, 0, 1);
		return glm::normalize(h);
	}



};