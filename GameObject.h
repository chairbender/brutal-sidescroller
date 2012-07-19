#pragma once

#include <SFML/Graphics.hpp>

/*
The abstract base class for every separate thing in the game state
*/
class GameObject
{
public:
	GameObject() { };
	~GameObject() { };

	/*
	Returns the sprite representing this game object,
	transformed to global level coordinates. SetPosition
	is probably safe for you to do, but you might get errors
	if you do stuff to this sprite other than that.
	*/
	virtual sf::Sprite& getSprite() = 0;
	/*
	Perform all of the object's logic for this step -
	whatever it needs to do
	*/
	virtual void update() = 0;

};

