#include "SoundGraph.h"

/*
SoundGraph will store an array of pixels, and write to it when updates need
to be made. When it needs to display, the pixels will be loaded into an
image using image::create.
http://en.sfml-dev.org/forums/index.php?topic=3543.0
*/
#include <algorithm>

using namespace std;

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

	const list<float>* lastAudio = audioListenerRecorder->getInputBuffer();
 //	for (list<float>::iterator it = lastAudio.begin(); it != lastAudio.end(); it++) {
	//	knownMax = max<float>(*it,knownMax);
	//}
	//Figure out y coordinate of pixel by scaling
}


sf::Sprite& SoundGraph::getSprite()
{
	this->graphTexture.loadFromImage(*pixels.getImage());
	this->graphSprite.setTexture(graphTexture);
	return graphSprite;
}

