#include "image_util.h"
#include <exception>


bool loadImage(const std::string & locationInSpriteFolder, 
	sf::Texture& destTexture)
{
	sf::Image resultImage;
	if (resultImage.loadFromFile("sprites/" + locationInSpriteFolder)) {
		resultImage.createMaskFromColor(resultImage.getPixel(0,0));

		destTexture.loadFromImage(resultImage);

		return true;
	} else {
		//no image found
		return false;
	}

}