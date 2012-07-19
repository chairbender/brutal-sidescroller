/*
This gameobject provides a small graph of audio data over time.
*/
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <AudioListenerRecorder.h>
#include "SFML/Config.hpp"
#include "PixelArray.h"

class SoundGraph : public GameObject {
public:

	/*
	Create a SoundGraph at the specified location with the specified width,
	graphing the passed AudioListenerRecorder
	*/
	SoundGraph(AudioListenerRecorder* toGraph,int width, int height,int x, int y);

	virtual sf::Sprite& getSprite();
	virtual void update();

private:
	AudioListenerRecorder* audioListenerRecorder;
	float knownMax;
	float knownMin;
	sf::Sprite graphSprite;
	sf::Image graphImage;
	sf::Texture graphTexture;
	PixelArray pixels;
};

