#include "SFML/Config.hpp"
#include "portaudio.h"
#include <queue>
#include <list>
#include <boost/thread.hpp>

#ifndef NULL
#define NULL 0
#endif

/*
Provides the functionality for AudioListener.
While recording, plays the audio back at the set
feedback volume, and scans for screams. When it detects a scream,
calling getEvent() will return that.
*/
#ifndef AUDIOLISTENERRECORDER_H
#define AUDIOLISTENERRECORDER_H
class AudioListenerRecorder {
public:
	enum AudioEvent { NOTHING, END_SCREAM, START_HIGH_SCREAM, START_LOW_SCREAM };

	AudioListenerRecorder();

	~AudioListenerRecorder();

	/*
	Sets the volume (in decibels) of the fed-back audio from
	the microphone
	*/
	void setFeedbackVolume(float decibels);

	/*
	Returns whatever has happened that hasn;t been gotten yet
	Only returns transients - on and off events, not sustained ones.
	*/
	AudioEvent getEvent();
	/*
	Are there still events to be processed?
	*/
	bool hasEvents();

	/*
	Begins listening for events.
	*/
	void startReceivingInput();

	void stopReceivingInput();

	/*
	Gets the last buffer of audio data that was processed
	by this audio listener recorder
	*/
	const std::list<float>* getInputBuffer();

private:

	//Callback for processing audio
	static int processAudio( const void *inputBuffer, void *outputBuffer, 
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData );

	//Singleton reference
	static AudioListenerRecorder* audioListenerRecorder;
	static boost::mutex bufferMutex;

	float feedbackVolume;
	std::queue<AudioEvent> events;
	std::list<float> lastInputBuffer;


};
#endif

