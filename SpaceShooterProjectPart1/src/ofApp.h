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
//General Sprite class 
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
	
};

//Manages all Sprites in a system. You can create multiple systems
class SpriteSystem
{
	public:
		void add(Sprite);
		void remove(int);
		void update();
		void draw();
		//dynamic array for storing sprites
		vector<Sprite> sprites;

};
//General purpose Emitter class for emitting sprites
//Works similar to Particle emitter

class Emitter : public BaseObject {
public:
	Emitter(SpriteSystem *);
	void draw();
	void start();
	void stop();
	void setLifeSpan(float);
	void setVelocity(ofVec3f);
	void setChildImage(ofImage);
	void setImage(ofImage);
	void setRate(float);
	void update();
	
	void setHeader(glm::vec3);
	SpriteSystem *sys;
	float rate;
	ofVec3f velocity;
	glm::vec3 headVect;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	bool fireGun;
	float width, height;



};
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void shoot();
		SpriteSystem *sys;
		ofSoundPlayer plasmaRifleSound;
		ofSoundPlayer thrusters;
		ofSoundPlayer backingup;
		ofSoundPlayer recharge;
		Emitter *turret = NULL;
		Sprite *sprite = NULL;
	

		ofImage defaultImage;
		ofImage customImage;
		ofImage background;
		
	
		glm::vec3 mouse_last;
		bool imageLoaded;
		bool soundLoaded;
		bool bHide;

		map<int, bool> keymap;

		ofxFloatSlider rate;
		ofxFloatSlider life;
		ofxVec3Slider velocity;
		ofxLabel screenSize;
		ofxVec3Slider headVect; 


		ofxPanel gui;

		glm::vec3 heading() {
			glm::vec3 h = glm::rotate(glm::mat4(1.0), glm::radians(turret -> rotation), glm::vec3(0, 0, 1)) * glm::vec4(0, 1, 0, 1);
			return glm::normalize(h);
		}
		


};
