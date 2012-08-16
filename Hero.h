#pragma once
#include "GameObject.h"
#include "Animation.h"
class Hero :
	public GameObject
{
public:
	Hero(int startX, int startY);
	~Hero(void);

	virtual void draw(sf::RenderWindow &toRenderOn);

	virtual void update();

	/*
	Set the position of the hero
	*/
	void setPosition(float x, float y);

	/*
	Returns the height in pixels of the hero
	*/
	float getHeight();

private:
	//Our own sprite
	sf::Sprite sprite;
	//Timer for our animation; the ticks since the start of the current loop
	int animationTicks;

	//The shared animation, must be a pointer, otherwise, the resource manager
	//might not be initialized when the initializer for the animation gets called. So
	//we need to do initialization for the animation in the constructor
	static Animation* walkAnimation;
};

