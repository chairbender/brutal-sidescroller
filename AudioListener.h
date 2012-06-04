#pragma once
#include <SFML/Audio.hpp>
/*
Acts like a game controller, except it's based on the user's voice
input.
*/
class AudioListener {

public:
	
	/*
	Defines the types of events that we can receive
	*/
	enum AudioEvent {
		NOTHING,
		START_HIGH_SCREAM,
		START_LOW_SCREAM,
		END_SCREAM
	};

	/*
	Starts listening though the mic, also plays audio
	back based on the specified feedback level (default 0)
	*/
	void startListening();
	void stopListening();

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



};

