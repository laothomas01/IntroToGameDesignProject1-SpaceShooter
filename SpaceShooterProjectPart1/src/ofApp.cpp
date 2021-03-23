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

	// create an image for sprites being spawned by emitter
	//
	/*if (defaultImage.load("images/Eyeball.png"))
	{
		imageLoaded = true;
	}
	if (customImage.load("images/Alien.png"))
	{
		imageLoaded = true;
	}
	
	if (DefaultEnemy.load("images/SpaceShip.png"))
	{
		imageLoaded = true;
	}

	if (Minions.load("images/Projectile.png"))
	{
		imageLoaded = true;
	}*/
	if (defaultImage.load("images/Eyeball.png")) {
		imageLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/SpaceShip.png");
		ofExit();
	}


	if (customImage.load("images/Alien.png")) {
		imageLoaded = true;
	}
	else {
		ofLogFatalError("can't load image: images/Projectile.png");
		ofExit();
	}


	if (DefaultEnemy.load("images/SpaceShip.png"))
	{
		imageLoaded = true;
	}
	else
	{
		cout << "ERROR" << endl;
	}
	if (Minions.load("images/Projectile.png"))
	{
		imageLoaded = true;
	}
	else
	{
		ofExit();
	}

	if (background.load("images/background.jpg"))
	{
		imageLoaded = true;
	}
	if (Wobble.load("soundEffects/Wobble.mp3"))
	{
		soundLoaded = true;
	}
	


	turret = new Emitter(new SpriteSystem());

	turret->setPosition(ofVec3f(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0));
	turret->drawable = true;
	turret->setImage(defaultImage);
	turret->setChildImage(customImage);
	turret->start();

	enemySpawner = new Emitter(new SpriteSystem());
	enemySpawner-> setPosition(ofVec3f(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0));
	enemySpawner-> drawable = true;
	enemySpawner-> setImage(DefaultEnemy);
	enemySpawner-> setChildImage(Minions);
	enemySpawner-> start();


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
	turret->update();
	//look for updates on enemy sprites
	glm::vec3 initialVelocity = glm::vec3(velocity->x, velocity->y, velocity->z);
	enemySpawner->setRate(rate);
	enemySpawner->setLifeSpan(life * 1000); // convert to milliseconds
	enemySpawner->setVelocity(initialVelocity);
	enemySpawner->spawnEnemies();
	enemySpawner->move();

	//look for updates on projectile position
	//Collision detection

	//BUSTED
	for (int i = 0; i < turret->sys->sprites.size(); i++)
	{
		cout << "SPRITE POSITION:" << turret->sys->sprites[i].trans << endl;
		for (int i = 0; i < enemySpawner->sys->sprites.size(); i++)
		{
			Distance = glm::distance(turret->sys->sprites[i].trans, enemySpawner->sys->sprites[i].trans);
			ContactDistance = turret->sys->sprites[i].height / 2 - enemySpawner->sys->sprites[i].height / 2;
			cout << "DISTANCE:" << Distance << endl;
			cout << "\nCONTACT DISTANCE:" << ContactDistance << endl;
			if (Distance < ContactDistance)
			{
				turret->sys->sprites[i].lifespan = -1;
				cout << "LIFESPAN OF TURRET SPRITE:" << turret->sys->sprites[i].lifespan << endl;
				enemySpawner->sys->sprites[i].lifespan = -1;
				cout << "\nLIFESPAN OF ENEMY SPAWN SPRITE:" << enemySpawner->sys->sprites[i].lifespan << endl;
			}
		}
	}
}
//--------------------------------------------------------------
void ofApp::draw()
{
	background.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	turret->draw();
	enemySpawner->draw();
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
		//cout << "Space bar is being pressed" << endl;
		float time = ofGetElapsedTimeMillis();
		if ((time - turret->lastSpawned) > (1000.0 / rate))
		{
			Wobble.play();
		}

		//	/*case OF_KEY_CONTROL:*/
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	turret->fireGun = false;
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
*/

