#include "image_util.h"


sf::Texture* loadImage(const std::string & locationInSpriteFolder)
{
	sf::Image resultImage;
	resultImage.loadFromFile("sprites/" + locationInSpriteFolder);
	resultImage.createMaskFromColor(resultImage.getPixel(0,0));

	sf::Texture* result = new sf::Texture;
	result->loadFromImage(resultImage);

	return result;
}