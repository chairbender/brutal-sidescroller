/*
This gameobject provides a small graph of audio data over time.
*/
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <AudioListenerRecorder.h>
#include "SFML/Config.hpp"
#include "PixelArray.h"
#include <UGen.h>

#include <deque>

using namespace std;

class SoundGraph : public GameObject, public UGen {
public:

	/*
	Create a SoundGraph at the specified location with the specified width,
	graphing the input audio data
	*/
	SoundGraph(int width, int height,int x, int y);

	virtual sf::Sprite& getSprite();
	virtual void update();

	virtual void processInput( const float* input, int numSamples );

private:
	deque<float> unHandledAudio;	
	boost::mutex audioQueueMutex;

	float knownMax;
	float knownMin;

	int pixelsWide;
	int pixelsHigh;
	sf::Sprite graphSprite;
	sf::Image graphImage;
	sf::Texture graphTexture;
	PixelArray pixels;
};

