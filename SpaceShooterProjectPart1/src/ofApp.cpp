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

//initialize your objects
void ofApp::setup() {

	Distance = 0.0;
	ContactDistance = 0.0;
	ofSetVerticalSync(true);
	/*
	
		load all images I want to use
	
	*/
	if (defaultImage.load("images/Spaceship.png")) {
		imageLoaded = true;
	}
	else
	{
		cout << "IMAGE CANNOT BE LOADED\n";
	}
	if (fireBall.load("images/Projectile.png"))
	{
		imageLoaded = true;
	}
	else
	{
		cout << "IMAGE CANNOT BE LOADED\n";
	}
	if (background.load("images/background.png")) {
		imageLoaded = true;
	}
	else
	{
		cout << "IMAGE CANNOT BE LOADED\n";
	}
	if (Minions.load("images/RajTheParasite"))
	{
		imageLoaded = true;
	}
	else
	{
		cout << "IMAGE CANNOT BE LOADED\n";
	}
	if (DefaultEnemy.load("images/Eyeball.png"))
	{
		imageLoaded = true;
	}
	else
	{
		cout << "IMAGE CANNOT BE LOADED";
	}
	//load sound effects
	if (Wobble.load("soundEffects/Wobble.mp3"))
	{
		soundLoaded = true;
	}
	else
	{
		cout << "CANNOT LOAD SOUND\n";
	}

	turret = new Emitter(new SpriteSystem);
	turret->rotation = 0.0;
	turret->setPosition(ofVec3f(ofGetWindowWidth() / 2.0, 2000 / 2.0, 0));
	turret->drawable = true;
	//Emitter image
	turret->setImage(defaultImage);
	//Emitter's sprite images
	turret->setChildImage(fireBall);
	//do not start yet!
	enemySpawner = new Emitter(new SpriteSystem);
	enemySpawner->setPosition(ofVec3f(ofGetWindowWidth() / 2.0, 2000 / 2.0, 0));
	enemySpawner->drawable = true;
	enemySpawner->setImage(DefaultEnemy);
	enemySpawner->setChildImage(Minions);

	

	//do not start yet!

	//start
	turret->start();
	enemySpawner->start();
	turret->haveImage = true;
	//emitter sprites
	turret->haveChildImage = true;
	enemySpawner->haveImage = true;
	//emitter sprites
	/*enemySpawner->haveChildImage = true;
	*/
	gui.setup();
	gui.add(rate.setup("rate", 1, 1, 10));
	gui.add(life.setup("life", 5, .1, 10));
	gui.add(velocity.setup("velocity", ofVec3f(0, -400,0 ), ofVec3f(0, 0, 0), ofVec3f(0, 0, 1000)));
	bHide = false;
}

//--------------------------------------------------------------
void ofApp::update() {

	
	turret->setRate(rate);
	turret->setLifeSpan(life * 1000); // convert to milliseconds
	turret->setVelocity(glm::vec3(velocity->x, velocity->y, velocity->z));

	
	////look for updates on enemy sprites
	//glm::vec3 initialVelocity = glm::vec3(velocity->x, velocity->y, velocity->z);
	//enemySpawner->setRate(rate);
	//enemySpawner->setLifeSpan(life * 1000); // convert to milliseconds
	//enemySpawner->setVelocity(initialVelocity);
	//enemySpawner->spawnEnemies();
	//enemySpawner->move();

	//look for updates on projectile position
	//Collision detection
	//if player's position goes beyond the coordinates of the right border
	if (turret->trans.x > 3900)
	{
		//player's position will be set at the left side border's position
		turret->setPosition(ofVec3f(-60, 1000, 0));
	}
	//if player's position goes beyond the coordinates of the left border
	if (turret->trans.x < -96)
	{
		//player's position coordinates will be set to the coordinates of the right border
		turret->setPosition(ofVec3f(3864,1000,0));
	}
	//if player goes beyond the top border's coordinates
	if (turret->trans.y < -83)
	{
		//player's coordinates will be set above the bottom border's coordinates
		turret->setPosition(ofVec3f(878, 2077, 0));
	}
	//if player goes beyond the bottom border's coordinates
	if (turret->trans.y > 2149)
	{
		//player's position will be set to slightly below the top border's coordinates
		turret->setPosition(ofVec3f(878.771, -34.9648, 0));
	}
	 /*else if (turret->trans.x < 65)
	 {
		 turret->setPosition(ofVec3f(, 1000, 0));
	 }*/
	/* if(turret->trans.y < -58.0)
	 {
	 
		 turret->setPosition(ofVec3f(2000, 2089, 0));
	 }*/
	/* if (turret->trans.y > 2100)
	 {
		 turret->setPosition(ofVec3f(2000, 2100, 0));
	 }*/


	if (keyisDown['w'])
	{
		
			turret->trans += 12 * turret->heading();
		
			cout << turret->trans << endl;
	}
	if (keyisDown['s'])
	{
		turret->trans -= 12 * turret->heading();
		cout << turret->trans << endl;
	}
	if (keyisDown['a'])
	{
		turret->rotation -= 10;
		cout << "TURRET ROTATION:" << turret->rotation << endl;
	}
	
	if (keyisDown['d'])
	{
		turret->rotation += 10;
		cout << "TURRET ROTATION:" << turret->rotation << endl;
	}
	
	if (keyisDown[' '])
	{
		turret->fireGun = true;
	}
	
	turret->update();
	
}
//--------------------------------------------------------------
void ofApp::draw()
{
	turret->draw();
	background.draw(0, 0, ofGetWidth(), ofGetHeight());
	enemySpawner->draw();	
	//background.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	//turret->draw();
	//enemySpawner->draw();
	ofDrawLine(turret->trans, turret->trans + 1000 * turret->heading());
	////if not hide, draw the gui
	//if (!bHide)
	//{
	//	gui.draw();
	//}
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	keyisDown[key] = true;
	//switch (key)
	//{
	//case OF_KEY_UP:

	//	//if ((turret->trans.x < ofGetWindowWidth() - 50 and turret->trans.x >= 0) and (turret->trans.y < ofGetWindowHeight() - 50 and turret->trans.y >= 0))
	//	//{	//pos = pos + heading * 20 <- velocity
	//	/*turret->trans += heading() * 20; cout << turret->trans << endl;*/
	//	//thrusters.play();
	////}

	//	break;
	//	//have a diagonal movement when two keys are pressed
	//case OF_KEY_DOWN:
	//	/*if ((turret->trans.x <= ofGetWindowWidth() and turret->trans.x >= 0) and (turret->trans.y <= ofGetWindowHeight() and turret->trans.y >= 0))
	//	{*/
	//	//turret->trans -= heading() * 20; cout << turret->trans << endl;
	//	/*	backingup.play();*/
	//	//}
	//	break;

	//case OF_KEY_LEFT:
	//	//turret->rotation -= 6;	   cout << turret->rotation << endl;
	//	break;
	//case OF_KEY_RIGHT:
	//	//turret->rotation += 6;	cout << turret->rotation << endl;
	//	break;
	//case 'b':
	//	bHide = true;
	//	break;
	//case OF_KEY_TAB:
	//	bHide = false;
	//	break;
	//case ' ':
	//	//for starting the game
	//	//turret->haveImage = true;
	//	//turret->fireGun = true;
	//	////cout << "Space bar is being pressed" << endl;
	//	//float time = ofGetElapsedTimeMillis();
	//	//if ((time - turret->lastSpawned) > (1000.0 / rate))
	//	//{
	//	//	Wobble.play();
	//	//}

	//	//	/*case OF_KEY_CONTROL:*/
	//}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	turret->fireGun = false;
	keyisDown[key] = false;
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
what did I fix?
	-
3-22-2021
Journal Log:
-I am going crazy
-Created a second emitter
-no score GUI
-fancy sprite movements implemented
-need to update my player movement to something better
-update that header so my bullets can move freely.
-working on collision detection. DOESNT WORK!
-organized all my code so I can properly work
-I am tired, frustrated and annoyed.
-whatever you cannot do anything about it. no god, no prayers, no extra brain cells. you know it or you fail.
-accept failure and move on. 

What did I learn and do today?
-I created a UML diagram to organize my thoughts
-I got so overwhelmed by the code I had to take a large step back
		-I commented all the functioning code out and started from square 1 again
-I implemented multiple key inputs
Here is an interesting discovery: 
								-if I put the head vector function in my ofApp.h where rotation takes an Emitter->rotation, I can drag around my ship like a dog but my Emitter's sprite cannot rotate. I have a line to show where my 
head vector is pointing. 
								-if I put my head vector function in my Emitter.h where rotation is defined in the Emitter.h, I can move in the direction of the Emitter's head vector but I cannot rotate. 
								Can this problem be solved?
								Yes
My pictures did not load last time because I forgot to set haveImage and have childImage booleans to true for my Emitter objects.



3-

*/

