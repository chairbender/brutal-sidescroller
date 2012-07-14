#include "SFML/Config.hpp"
#include "portaudio.h"

#ifndef NULL
#define NULL 0
#endif

/*
Provides the functionality for AudioListener.
While recording, plays the audio back at the set
feedback volume, and scans for screams. When it detects a scream,
calling getEvent() will return that.
*/

class AudioListenerRecorder {
public:
	enum AudioEvent { NOTHING, END_SCREAM, START_HIGH_SCREAM, START_LOW_SCREAM };

	AudioListenerRecorder() { };

	~AudioListenerRecorder();

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

	/*
	Begins listening for events.
	*/
	void startReceivingInput();

	void stopReceivingInput();

private:
	float feedbackVolume;
};


