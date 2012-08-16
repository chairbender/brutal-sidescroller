#include "Hero.h"


Hero::Hero(int startX, int startY)
	: animationTicks(0)
{
	//Initialize the animations
	if (Hero::walkAnimation == NULL) {
		Hero::walkAnimation = new Animation("hero_walk");
		Hero::walkAnimation->setSpeed(5);
	}
	sprite.setTexture(*(Hero::walkAnimation->getFrame(0)),true);
	sprite.setPosition(startX,startY);
}


Hero::~Hero(void)
{
}

void Hero::draw(sf::RenderWindow &toRenderOn)
{
	toRenderOn.draw(sprite);
}

void Hero::update()
{
	//animate
	//increase the animation ticks
	animationTicks = (animationTicks + 1) % 
		(Hero::walkAnimation->getSpeed() * Hero::walkAnimation->numFrames());
	int frameIndex = animationTicks / Hero::walkAnimation->getSpeed();
	sprite.setTexture(*(Hero::walkAnimation->getFrame(frameIndex)),true);
}

void Hero::setPosition( float x, float y )
{
	//Sets the position of the hero on the screen
	sprite.setPosition(x,y);
}

float Hero::getHeight()
{
	return sprite.getLocalBounds().height;
}

//Static members initialization
Animation* Hero::walkAnimation;
