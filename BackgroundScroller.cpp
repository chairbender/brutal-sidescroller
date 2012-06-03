#include "BackgroundScroller.h"
#include "image_util.h"
#include "TextureManager.h"


bool BackgroundScroller::loaded = false;

BackgroundScroller::BackgroundScroller(const std::string pathToImageInSpriteFolder, float xPos, float yPos, float width, float height, int scrollSpeed)
	: 
GameObject(),
	scrollSpeed(scrollSpeed)
{
	//Check if the texture for ground has already
	//been created. If not, create it.
	if (!loaded)
	{
		groundTexture = *(gTextureManager.getResource(pathToImageInSpriteFolder));
		//For looping
		groundTexture.setRepeated(true);
	}

	//make the sprite use the ground texture, put it in position
	sprite.setTexture(BackgroundScroller::groundTexture);
	sprite.setTextureRect(sf::IntRect(0,0,width,height));
	sprite.setPosition(xPos,yPos);	
}


BackgroundScroller::~BackgroundScroller(void)
{
}

sf::Sprite& BackgroundScroller::getSprite()
{
	return sprite;
}

void BackgroundScroller::update()
{
	//Advance the scrolling
	int curX = sprite.getTextureRect().left;
	float nextX = curX + scrollSpeed % sprite.getTextureRect().width;
	sprite.setTextureRect(sf::IntRect(nextX,sprite.getTextureRect().top,sprite.getTextureRect().width,sprite.getTextureRect().height));
}
