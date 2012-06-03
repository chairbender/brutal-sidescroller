#pragma once
#include "gameobject.h"
#include "Animation.h"
class Hero :
	public GameObject
{
public:
	Hero(int startX, int startY);
	~Hero(void);

	virtual sf::Sprite& getSprite();

	virtual void update();

private:
	//Our own sprite
	sf::Sprite sprite;
	//Our current frame index in the animation
	int frameIndex;

	//The shared animation, must be a pointer, otherwise, the resource manager
	//might not be initialized when the initializer for the animation gets called. So
	//we need to do initialization for the animation in the constructor
	static Animation* walkAnimation;
};

