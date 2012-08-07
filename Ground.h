#pragma once
#include <gameobject.h>
/*
Represents the ground the hero walks on. It
scrolls through the ground image and is intended to 
stay fixed in the level coordinates. The game gives
the illusion of movement, everything just scrolls in.
*/
class Ground :
	public GameObject
{
public:
	/*
	Create the ground at the specified location on screen, having
	the specified dimensions. The ground will scroll at the specified
	scroll speed (in pixels per tick)
	The ground is intended to scroll without moving its rect,
	and take up the whole width of the screen
	*/
	Ground(float xPos, float yPos, float width, float height, int scrollSpeed = 0);
	~Ground(void);

	virtual sf::Sprite& getSprite();
	virtual void update();
private:
	sf::Sprite sprite;
	int scrollSpeed;
	//The texture that will be shared by all instances
	static sf::Texture groundTexture;
	//Whether we have loaded our textures
	static bool loaded;
};
