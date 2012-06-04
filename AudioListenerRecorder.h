#pragma once
#include <SFML/Audio.hpp>
#include "SFML/Config.hpp"
#include "AudioListener.h"

/*
Provides the functionality for AudioListener.
While recording, plays the audio back at the set
feedback volume, and scans for screams. When it detects a scream,
calling getEvent() will return that.
*/

class AudioListenerRecord : public sf::SoundRecorder {
public:

	AudioListenerRecord();

	~AudioListenerRecord();

	/*
	Sets the volume (in decibels) of the fed-back audio from
	the microphone
	*/
	void setFeedbackVolume(float decibels);

	/*
	Returns whatever has happened this tick.
	Only returns transients - on and off events, not sustained ones.
	*/
	AudioEvent getEvent();

protected:
	virtual bool onStart();

	virtual bool onProcessSamples( const sf::Int16* samples, std::size_t sampleCount );

	virtual void onStop();

private:
	float feedbackVolume;
};


