#pragma once
#include <SFML/Graphics.hpp>

/*
Load the specified image in the image folder
as a texture. Use the pixel at (0,0) for the transparency.
Always returns a new texture, so use sparingly.
*/
sf::Texture* loadImage(const std::string & locationInSpriteFolder);
