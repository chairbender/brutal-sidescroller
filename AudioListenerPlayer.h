#pragma once
#include <SFML/Audio.hpp>
#include "SFML/Config.hpp"
#include "AudioListener.h"
#include "SFML/Audio/SoundStream.hpp"

//TODO: Implement this system
/*
Handles playing an audio buffer that is fed into it
by calling addChunk.
*/
public AudioListenerPlayer : public sf::SoundStream {

public:
	AudioListenerPlayer();
	~AudioListenerPlayer();

	/*
	Copies the audio data pointed to by the chunk into
	the queue of audio to play.
	*/
	void addChunk(sf::Chunk newData);


protected:
	virtual bool onGetData(sf::Chunk &data);

}