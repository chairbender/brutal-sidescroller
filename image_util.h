#pragma once
#include <SFML/Graphics.hpp>

/*
Load the specified image in the image folder
into the passed texture. Use the pixel at (0,0) for the transparency.
Returns true if success, false otherwise. Creates a new image with each call,
so use sparingly or improve implementation of this method.
*/
bool loadImage(const std::string & locationInSpriteFolder, 
	sf::Texture& destTexture);
