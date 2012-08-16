#pragma once
#include "GameObject.h"
/*
Represents a sprite that scrolls its image in place
*/
class BackgroundScroller :
	public GameObject
{
public:
	/*
	Create the background sprite at the specified position.
	Uses the path to find the image to use in the sprite folder
	It will scroll at the specified
	scroll speed (in ticks per pixel)
	It is intended to scroll without moving its rect,
	and take up the whole width of the screen
	*/
	BackgroundScroller(const std::string pathToImageInSpriteFolder, float xPos, float yPos, float width, float height, int scrollSpeed = 0);
	~BackgroundScroller(void);

	virtual void draw(sf::RenderWindow &toRenderOn);
	virtual void update();
private:
	sf::Sprite sprite;
	int scrollSpeed;
	int ticksSinceScroll;
	//The texture that will be shared by all instances
	sf::Texture groundTexture;
	//Whether we have loaded our textures
	static bool loaded;
};
