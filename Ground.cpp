#include "Ground.h"
#include "image_util.h"


//Initialize static members
sf::Texture* Ground::groundTexture = NULL;

Ground::Ground(float xPos, float yPos, float width, float height, int scrollSpeed)
	: 
	GameObject(),
	scrollSpeed(scrollSpeed)
{
	//Check if the texture for ground has already
	//been created. If not, create it.
	if (Ground::groundTexture == NULL)
	{
		Ground::groundTexture = loadImage("ground.png");
		//For looping
		Ground::groundTexture->setRepeated(true);
	}

	//make the sprite use the ground texture, put it in position
	sprite.setTexture(*Ground::groundTexture);
	sprite.setTextureRect(sf::IntRect(0,0,width,height));
	sprite.setPosition(xPos,yPos);	
}


Ground::~Ground(void)
{
}

const sf::Sprite Ground::getSprite() const
{
	return sprite;
}

void Ground::update()
{
	//Advance the scrolling
	int curX = sprite.getTextureRect().left;
	float nextX = curX + scrollSpeed % sprite.getTextureRect().width;
	sprite.setTextureRect(sf::IntRect(nextX,sprite.getTextureRect().top,sprite.getTextureRect().width,sprite.getTextureRect().height));
}
