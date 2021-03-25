#pragma once
//Manages all Sprites in a system. You can create multiple systems
#include "Sprite.h"
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
