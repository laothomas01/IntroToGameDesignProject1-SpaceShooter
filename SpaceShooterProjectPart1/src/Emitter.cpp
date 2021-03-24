//  Create a new Emitter - needs a SpriteSystem
//
#include "SpriteSystem.h"
#include "Emitter.h"
//Emitter takes in a sprite system and draws all the sprites from the sprite system based on its location
Emitter::Emitter(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 3000;    // milliseconds or 3 seconds
	started = false;    //flag for when emitter begins
	lastSpawned = 0;	//last time an object spawned
	rate = 1;    // sprites/sec
	haveChildImage = false; 
	haveImage = true;
	velocity = ofVec3f(0, -400, 0);
	drawable = true;
	width = 50;
	height = 50;
	rotation = 180.0;
	headVect = glm::vec3(0, 0, 0);
	fireGun = false; // firing projectiles
	unleashMinions = true; // have the enemy Emitter send out sprites to chase our player
}
//  Draw the Emitter if it is drawable. In many cases, you would want a hidden emitter.
//When you want to create an Emitter, call draw function to make it appear
void Emitter::draw() {
	//we translate the sprites and emitter after calling the draw() function
	glm::mat4 T = getMatrix();
	ofPushMatrix();
	ofMultMatrix(T);
	if (drawable) {
		if (haveImage) {
			//center of our window
			image.draw(-image.getWidth() / 2.0, -image.getHeight() / 2.0);
		}
		else {
			ofDrawRectangle(-width / 2, -height / 2, width, height);
		}
	}
	// draw sprite system after Emitter has been drawn
	sys->draw();
	ofPopMatrix();
}
//spawned from our emitter, we want to give our sprites some interesting movement
void Emitter::move()
{
	for (int i = 0; i < sys->sprites.size(); i++)
	{
		sys->sprites[i].trans.x = sys->sprites[i].trans.x +40;
		//fluctuate the y value for some spraying action
		sys->sprites[i].trans.y = sys->sprites[i].trans.y + sin(sys->sprites[i].trans.x) * 30;
	}
}
/*

Collision detection

*/

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.

//launch projectiles from Emitter
void Emitter::shoot()
{
	float time = ofGetElapsedTimeMillis();
	//in milliseconds: 1000 ms = 1 sec. 10000 ms = 10 sec
	if ((time - lastSpawned) > (1000.0 / rate)) {
		//cout << "TIME: "<< time - lastSpawned << endl;
		if (fireGun)
		{
			// spawn a new sprite
			Sprite sprite;
			if (haveChildImage) sprite.setImage(childImage);
			sprite.velocity = velocity;
			sprite.lifespan = lifespan;
			sprite.birthtime = time;
			/*sprite.rotation = rotation;*/
			sys->add(sprite);
			lastSpawned = time;
		}

	}
	//helps me get rid extra projectiles so i can save memory
	sys->update();
}
//void Emitter::spawnEnemies()
//{
//	float time = ofGetElapsedTimeMillis();
//	//in milliseconds: 1000 ms = 1 sec. 10000 ms = 10 sec
//	
//		if ((time - lastSpawned) > (5000.0 / rate)) {
//
//			// spawn a new sprite
//
//			Sprite enemy;
//			if (haveChildImage) enemy.setImage(childImage);
//			enemy.velocity = velocity;
//			enemy.lifespan = lifespan;
//			enemy.birthtime = time;
//			/*sprite.rotation = rotation;*/
//			sys->add(enemy);
//			//plasmarifle.play();
//			lastSpawned = time;
//			
//		}
//		sys->update();
//}



void Emitter::update() {
	if (!started) return;
	//when ever use presses spacebar, trigger fireGun flag to shoot
	shoot();
}

// Start/Stop the emitter.
//

void Emitter::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void Emitter::stop() {
	started = false;
}

void Emitter::setLifeSpan(float life) {
	lifespan = life;
}

void Emitter::setVelocity(ofVec3f v) {
	velocity = v;
}

void Emitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
}

void Emitter::setImage(ofImage img) {
	image = img;
	haveImage = false;
}
void Emitter::setRate(float r) {
	rate = r;
}
