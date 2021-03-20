#include "ofApp.h"
//----------------------------------------------------------------------------------
//
// This example code demonstrates the use of an "Emitter" class to emit Sprites
// and set them in motion. The concept of an "Emitter" is taken from particle
// systems (which we will cover next week).
//
// The Sprite class has also been upgraded to include lifespan, velocity and age
// members.   The emitter can control rate of emission and the current velocity
// of the particles. In this example, there is no acceleration or physics, the
// sprites just move simple frame-based animation.
//
// The code shows a way to attach images to the sprites and optional the
// emitter (which is a point source) can also have an image.  If there are
// no images attached, a placeholder rectangle is drawn.
// Emitters  can be placed anywhere in the window. In this example, you can drag
// it around with the mouse.
//
// OF has an add-in called ofxGUI which is a very simple UI that is useful for
// creating sliders, buttons and fields. It is not recommended for commercial 
// game development, but it is useful for testing.  The "h" key will hide the GUI
// 
// If you want to run this example, you need to use the ofxGUI add-in in your
// setup.
//
//
//  Kevin M. Smith - CS 134 SJSU

//BaseObject::BaseObject() {
//	
//	trans = ofVec3f(0, 0, 0);
//	scale = ofVec3f(1, 1, 1);
//
//	
//}
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
//
// Basic Sprite Object
//
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
//
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

//  Add a Sprite to the Sprite System
void SpriteSystem::add(Sprite s) {
	sprites.push_back(s);
}

// Remove a sprite from the sprite system. Note that this function is not currently
// used. The typical case is that sprites automatically get removed when the reach
// their lifespan.
//
void SpriteSystem::remove(int i) {
	sprites.erase(sprites.begin() + i);
}


//  Update the SpriteSystem by checking which sprites have exceeded their
//  lifespan (and deleting).  Also the sprite is moved to it's next
//  location based on velocity and direction.
//
void SpriteSystem::update() {

	if (sprites.size() == 0) return;
	//iterator to loop through sprites array
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;

	// check which sprites have exceed their lifespan and delete
	// from list.  When deleting multiple objects from a vector while
	// traversing at the same time, use an iterator.
	//
	while (s != sprites.end()) {
		if (s->lifespan != -1 && s->age() > s->lifespan) {
			//			cout << "deleting sprite: " << s->name << endl;
			tmp = sprites.erase(s);
			s = tmp;
		}
		else s++;
	}
}

//  Render all the sprites
//Sprites can be created and move along a heading vector
void SpriteSystem::draw() {

	for (int i = 0; i < sprites.size(); i++)
	{
		cout << sprites.size() << endl;
		sprites[i].draw();
		sprites[i].trans -= sprites[i].heading() * sprites[i].velocity / ofGetFrameRate();
		
	}
}

//  Create a new Emitter - needs a SpriteSystem
//
Emitter::Emitter(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 3000;    // milliseconds
	started = false;
	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	/*haveImage = true;*/
	velocity = ofVec3f(100, 100, 0);
	drawable = true;
	width = 50;
	height = 50;
	headVect = glm::vec3(0, 0, 0);
	fireGun = false;
}

//  Draw the Emitter if it is drawable. In many cases you would want a hidden emitter
//
//
void Emitter::draw() {
	glm::mat4 T = getMatrix();
	ofPushMatrix();
	ofMultMatrix(T);
	if (drawable) {

		if (haveImage) {
			image.draw(-image.getWidth() / 2.0 , -image.getHeight() / 2.0);
		}
		else {
			ofDrawRectangle(-width / 2, -height / 2, width, height);
		}
		
	}

	// draw sprite system
	
	sys->draw();

	ofPopMatrix();
}

//  Update the Emitter. If it has been started, spawn new sprites with
//  initial velocity, lifespan, birthtime.
//

void Emitter::update() {
	if (!started) return;

	float time = ofGetElapsedTimeMillis();
	//in milliseconds: 1000 ms = 1 sec. 10000 ms = 10 sec
	if ((time - lastSpawned) > (1000.0 / rate)) {
		if (fireGun)
		{
			// spawn a new sprite
			Sprite sprite;
			if (haveChildImage) sprite.setImage(childImage);
			sprite.velocity = velocity;
			sprite.lifespan = lifespan;
			sprite.setPosition(heading());
			sprite.birthtime = time;
			/*sprite.rotation = rotation;*/
			sys->add(sprite);
			lastSpawned = time;

		}
		
	}
	//helps me get rid extra projectiles so i can save memory
	sys->update();
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
void Emitter::setHeader(glm::vec3 v)
{
	headVect = v;
}

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetVerticalSync(true);

	// create an image for sprites being spawned by emitter
	//
	if (defaultImage.load("images/SpaceShip.png")) {
		imageLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/SpaceShip.png");
		ofExit();
	}

	if (customImage.load("images/Projectile.png")) {
		imageLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/Projectile.png");
		ofExit();
	}
	if (background.load("images/background.jpg"))
	{
		imageLoaded = true;
	}
	if (plasmaRifleSound.load("soundEffects/PlasmaRifle.mp3"))
	{
		soundLoaded = true;
	}

	//if (thrusters.load("soundEffects/thrusters.mp3"))
	//{
	//	soundLoaded = true;
	//}
	//if (backingup.load("soundEffects/backingup.mp3"))
	//{
	//	soundLoaded = true;
	//}
	//if (recharge.load("soundEffects/recharge.mp3"))
	//{
	//	soundLoaded = true;
	//}
	
	





	// create an array of emitters and set their position;
	//



	turret = new Emitter(new SpriteSystem());

	turret->setPosition(ofVec3f(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0));
	turret->drawable = true;
	turret->setImage(defaultImage);
	turret->setChildImage(customImage);
	turret->start();


	gui.setup();
	gui.add(rate.setup("rate", 1, 1, 10));
	gui.add(life.setup("life", 5, .1, 10));
	gui.add(velocity.setup("velocity", ofVec3f(0, -200, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
	bHide = false;
}

//--------------------------------------------------------------
void ofApp::update() {
	turret->setRate(rate);
	turret->setLifeSpan(life * 1000); // convert to milliseconds
	turret->setVelocity(glm::vec3(velocity->x, velocity->y, velocity->z));
	turret->update();
}


//--------------------------------------------------------------
void ofApp::draw()
{
	background.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	turret->draw();
	ofDrawLine(turret->trans, turret->trans + 1000 * heading());
	//if not hide, draw the gui
	if (!bHide)
	{
		gui.draw();
	}
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	switch (key)
	{
	case OF_KEY_UP:
		
		//if ((turret->trans.x < ofGetWindowWidth() - 50 and turret->trans.x >= 0) and (turret->trans.y < ofGetWindowHeight() - 50 and turret->trans.y >= 0))
		//{	//pos = pos + heading * 20 <- velocity
			turret->trans += heading() * 20; cout << turret->trans << endl;
			//thrusters.play();
		//}
		
		break;
		//have a diagonal movement when two keys are pressed
	case OF_KEY_DOWN:
		/*if ((turret->trans.x <= ofGetWindowWidth() and turret->trans.x >= 0) and (turret->trans.y <= ofGetWindowHeight() and turret->trans.y >= 0))
		{*/
			turret->trans -= heading() * 20; cout << turret->trans << endl;
		/*	backingup.play();*/
		//}
		break;

	case OF_KEY_LEFT:
		turret->rotation -= 6;	   cout << turret->rotation << endl;
		break;
	case OF_KEY_RIGHT:
		turret->rotation += 6;	cout << turret->rotation << endl;
		break;
	case 'b':
		bHide = true;
		break;
	case OF_KEY_TAB:
		bHide = false;
		break;
	case ' ':
		//for starting the game
		turret->haveImage = true;
		turret->fireGun = true;
		cout << "Space bar is being pressed" << endl;
		float time = ofGetElapsedTimeMillis();
		if ((time - turret->lastSpawned) > (1000.0 / rate))
		{
			//plasmaRifleSound.play();
		}
		
	//	/*case OF_KEY_CONTROL:*/
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	turret ->fireGun = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	/*turret->trans.x = x;
	turret->trans.y = y;*/
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
/*

3-11-2021
Journal Log:
I am so stupid that I did not consider the rate of fire.
Current problem: ship is firing 1 projectile per second
Updated: after changing the rate of fire to 0.1, our time = 1000milliseconds / 0.1 = 10000 milliseconds or 10 seconds. so we get 1 bullet every 10 seconds
My emitter update's first if statement controlls the rate of fire per second. so leaving the code alone causes the player to auto fire. how do I fix this? 
put in A NESTED BOOLEAN IF STATEMENT! If(rateoffire) if( firegun) { do something }
To shoot, hit space bar, and change fireGun logic to TRUE
On release of space bar, change fireGun logic to false. 

What did I learn today?
	-people suck at writing help description. like seriously wtf???
	-I stink at analyzing code and testing
	-I dont think Ill ever designs games
	-No but seriously, FUCK OPEN FRAME WORKS!.
	-

what did I fix?
	-



*/
