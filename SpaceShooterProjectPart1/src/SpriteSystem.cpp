//  Add a Sprite to the Sprite System
#include "Sprite.h"
#include "SpriteSystem.h"
//add sprite to sprite system
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
//  lifespan (and deleting). 
//	Also the sprite is moved to it's next location based on velocity and direction.
void SpriteSystem::update() {

	if (sprites.size() == 0) return;
	//iterator to loop through sprites array
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;

	//initial sprite movement
	for (int i = 0; i < sprites.size(); i++)
	{
	

		//new position	=	old position 	- position based on rotation,matrix transformation		how many pixels to move per frame
		
												//possibly a problem with our sprite's header
		sprites[i].trans = sprites[i].trans - sprites[i].heading() * sprites[i].velocity / ofGetFrameRate();

		
	
	}

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
void SpriteSystem::draw() {

	for (int i = 0; i < sprites.size(); i++)
	{
		/*cout << sprites.size() << endl;*/
		
		sprites[i].draw();

		//Apply this interpolation somewhere else
		/*sprites[i].trans.x -= cos(180) * 50 / ofGetFrameRate();
		sprites[i].trans.y -= sin(-180) * 50 / ofGetFrameRate();*/


		//this is the initial direction and speed our projectiles will be moving 
		
	}
}

