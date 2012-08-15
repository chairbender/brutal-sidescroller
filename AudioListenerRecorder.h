#include "SFML/Config.hpp"
#include "portaudio.h"
#include <queue>
#include <list>
#include <boost/thread.hpp>
#include "UGen.h"

#ifndef NULL
#define NULL 0
#endif

/*
While recording, plays the audio back at the set
feedback volume, and scans for screams. Can also
have subscriber ugens which will recieve audio data as it
comes in, and can do what they want with it. When it detects a scream,
calling getEvent() will return that.
*/
#ifndef AUDIOLISTENERRECORDER_H
#define AUDIOLISTENERRECORDER_H
class AudioListenerRecorder {
public:
	enum AudioEvent { NOTHING, END_SCREAM, START_SCREAM };

	/*
	Returns the single audio listener recorder
	*/
	static AudioListenerRecorder* getAudioListenerRecorder();

	/*
	Adds a UGen whose processInput will be called with input data
	whenever the audiolistenerrecorder receives input data
	*/
	void addSubscriber(UGen* subscriber);

	/*
	Sets the volume (in decibels) of the fed-back audio from
	the microphone
	*/
	void setFeedbackVolume(float decibels);

	/*
	Returns whatever has happened that hasn't been getEvent'd() yet
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
	std::list<float>* getInputBuffer();

	/*TODO: Finish adding in scream detection thresholding
	Will provide a method that SoundGraph can use to get the currently set
	threshold for detecting screams.
	*/
	void checkForAudioEvents(const void *inputBuffer, size_t numBytes);


private:
	AudioListenerRecorder();

	~AudioListenerRecorder();

	//Callback for processing audio
	static int processAudio( const void *inputBuffer, void *outputBuffer, 
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData );

	//Various utility variables
	bool inScream; //When we are in a scream, we will need to ignore peak events
	float screamStartLevel; // what level where we at (LPF'd) when the scream started (so we
							//know when it is over)
	float smoothedValue; //For tracking the LPF'd value between input buffers
	float knownMin; //current min and max audio values recorded
	float knownMax;

	//Singleton reference
	static AudioListenerRecorder* audioListenerRecorder;
	static boost::mutex bufferMutex;

	float feedbackVolume;
	std::queue<AudioEvent> events;
	std::list<float> lastInputBuffer;
	UGen* subscriber;


};
#endif

