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
#define SAMPLES_PER_HORIZONTAL_PIXEL 256

SoundGraph::SoundGraph(int width, int height,int x, int y )
:	pixels(width,height,sf::Color(255,255,255)),
	pixelsHigh(height),
	pixelsWide(width)
{
	//Set the position by position the sprite
	graphSprite.setPosition(x,y);

	//Set up the Image that we will draw on
}

void SoundGraph::update()
{
	//Draw the soundGraph

	//We'll put a dot on the graph on the very right and scroll it left

	int numSamples = unHandledAudio.size();
	//How many pixels should be drawn? For example, if we get 256 samples
	//and do 64 samples per pixel, we should draw 256/64 pixels in this single update.
	int numPixels = numSamples / SAMPLES_PER_HORIZONTAL_PIXEL;

	/*
	Go through the unhandled (unDrawn) audio in one pass. In that, we'll do a few things.
	1. Calculate the current min and max sample values.
	2. Average each group of SAMPLES_PER_HORIZONTAL_PIXEL samples into a single pixel value
	*/

	//In the outer loop, we loop through the number of pixels we have yet to draw
	for (int pixelIndex = 0; pixelIndex < numPixels; pixelIndex++) {
		//In the inner loop, we loop through SAMPLES_PER_HORIZONTAL_PIXEL pixels,
		//update max and min, and come up with an average.
		float total = 0;
		for (int sampleIndex = 0; sampleIndex < SAMPLES_PER_HORIZONTAL_PIXEL; sampleIndex++) {
			knownMax = max<float>(unHandledAudio.front(),knownMax);
			knownMin = min<float>(unHandledAudio.front(),knownMin);
			total += unHandledAudio.front();
			unHandledAudio.pop();
		}
		float average = total / SAMPLES_PER_HORIZONTAL_PIXEL;
		//We now have an average value to output to the graph for this pixel.
		//Shift the pixel grid left and put this as the rightmost pixel
		pixels.shiftPixels(-1);
		//Calculate the y value of this pixel by scaling
		int y = (int) ((average / (knownMax - knownMin)) * pixelsHigh);
		pixels.setPixel(pixelsWide-1,y,sf::Color(122,122,122,122));
	}
}


sf::Sprite& SoundGraph::getSprite()
{
	this->graphTexture.loadFromImage(*pixels.getImage());
	this->graphSprite.setTexture(graphTexture);
	return graphSprite;
}

void SoundGraph::processInput( const float* input, int numSamples )
{
	//Add the samples to the unprocessed audio queue (to be displayed)
	const float * cur = input;
	for (int i = 0; i < numSamples; i++) {
		unHandledAudio.push(cur[i]);
	}	
}

