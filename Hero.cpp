#include "Hero.h"


Hero::Hero(int startX, int startY)
	:frameIndex(0)
{
	//Initialize the animations
	if (Hero::walkAnimation == NULL) {
		Hero::walkAnimation = new Animation("hero_walk");
	}
	sprite.setTexture(*(Hero::walkAnimation->getFrame(0)),true);
	sprite.setPosition(startX,startY);
}


Hero::~Hero(void)
{
}

sf::Sprite& Hero::getSprite()
{
	return sprite;
}

void Hero::update()
{
	//animate
	frameIndex = (frameIndex + 1) % Hero::walkAnimation->numFrames();
	sprite.setTexture(*(Hero::walkAnimation->getFrame(frameIndex)),true);
}

//Static members initialization
Animation* Hero::walkAnimation;
