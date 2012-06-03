#include "Animation.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <exception>

#include "image_util.h"
#include "TextureManager.h"

Animation::Animation(const std::string & prefixInSpriteFolder)
{
	//Iterate through the images
	std::string prefix = prefixInSpriteFolder + "_";

	//Loop until we run out of images to look through
	int currentFrame = 0;
	while (true) {
		//try to load the next image
		//generate the suffix
		std::ostringstream ending;
		ending << std::setw(4) << std::setfill('0') << currentFrame << ".png";

		//Try loading
		sf::Texture* nextTexture;

		nextTexture = gTextureManager.getResource(prefix + ending.str());
		if (nextTexture != NULL) {
			//It's okay to use copy constructor on textures
			frames.push_back(nextTexture);
		} else {
			//no more images, we are done
			break;
		}

		currentFrame++;
	}
}


Animation::~Animation(void)
{
}

const sf::Texture* Animation::getFrame( int index ) const
{
	return frames.at(index);
}

const int Animation::numFrames() const
{
	return frames.size();
}

void Animation::setSpeed(int _ticksPerFrame) {
	ticksPerFrame = _ticksPerFrame;
}

int Animation::getSpeed() {
	return ticksPerFrame;
}