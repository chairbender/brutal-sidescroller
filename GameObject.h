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
	The gameobject will draw whatever it needs on the window
	*/
	virtual void draw(sf::RenderWindow &toRenderOn) = 0;


	/*
	Perform all of the object's logic for this step -
	whatever it needs to do
	*/
	virtual void update() = 0;
};

