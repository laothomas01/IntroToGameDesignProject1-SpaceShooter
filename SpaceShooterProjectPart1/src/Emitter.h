#pragma once
#include "BaseObject.h"
#include "SpriteSystem.h"
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
	void shoot();
	void setHeader(glm::vec3);
	void spawnEnemies();
	void move();
	



	SpriteSystem *sys;
	SpriteSystem *enemySpawnerSys;
	float rate;
	//float contactDistance;
	ofVec3f velocity;
	glm::vec3 headVect;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	/*ofSoundPlayer plasmarifle;*/
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	bool fireGun;
	bool soundLoaded;

	bool unleashMinions;
	float width, height;

};