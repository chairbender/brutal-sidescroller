#include "SoundGraph.h"

/*
SoundGraph will store an array of pixels, and write to it when updates need
to be made. When it needs to display, the pixels will be loaded into an
image using image::create.
http://en.sfml-dev.org/forums/index.php?topic=3543.0
*/

//Control how the graph appears
#define SAMPLES_PER_PIXEL 256

SoundGraph::SoundGraph( AudioListenerRecorder* toGraph,int width, int height,int x, int y )
:	pixels(width,height,sf::Color(255,255,255))
{
	//Set the position by position the sprite
	graphSprite.setPosition(x,y);

	//Set up the Image that we will draw on

	//Save the audioListenerRecorder
	audioListenerRecorder = toGraph;
}

void SoundGraph::update()
{
	//Draw the soundGraph

	//We'll put a dot on the graph on the very right and scroll it left
	//Get last audio buffer and average it
	//TODO: Finish implementing this
	std::list<float> lastAudio = audioListenerRecorder->getInputBuffer();
	for (int i = 0; i < lastAudio.size(); i++) {
		knownMax = max(lastAudio.,knownMax);
	}
	//Figure out y coordinate of pixel by scaling
	int y = 
}


sf::Sprite& SoundGraph::getSprite()
{
	this->graphTexture.loadFromImage(*pixels.getImage());
	this->graphSprite.setTexture(graphTexture);
	return graphSprite;
}

