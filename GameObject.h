#pragma once

#include <SFML/Graphics.hpp>

/*
The abstract base class for every separate thing in the game state
*/
class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	/*
	Returns the sprite representing this game object,
	transformed to global level coordinates
	*/
	virtual const sf::Sprite getSprite() const = 0;
	/*
	Perform all of the object's logic for this step -
	whatever it needs to do
	*/
	virtual void update() = 0;
};

