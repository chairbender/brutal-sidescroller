#include "AudioListenerRecorder.h"
#include <system_error>
#include <iostream>
#include <algorithm>

using namespace std;


#define PA_SAMPLE_TYPE paFloat32
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (paFramesPerBufferUnspecified)

#define PEAK_THRESHOLD

//Our static members
AudioListenerRecorder* AudioListenerRecorder::audioListenerRecorder;
boost::mutex AudioListenerRecorder::bufferMutex;

void AudioListenerRecorder::setFeedbackVolume( float decibels )
{
	feedbackVolume = decibels;
}

void checkForAudioEvents(const void *inputBuffer, size_t numBytes) {
	////We know we are dealing with an inputBuffer
	////full of floats
	//const float * input = (const float *) inputBuffer;
	//AudioListenerRecorder* recorder = AudioListenerRecorder::getAudioListenerRecorder();

	//for (int i = 0; i < numBytes/sizeof(float); i++) {
	//	//Track the current min and max
	//	recorder->knownMax = max<float>(average ,recorder->knownMax);
	//	recorder->knownMin = min<float>(average ,recorder->knownMin);
	//}

	//return;
}

void reportError(PaError err) {
	Pa_Terminate();
	std::cerr << "An error occured while using the portaudio stream\n";
	std::cerr << "Error number: " << err;
	std::cerr << "Error message: " << Pa_GetErrorText(err);
}

void AudioListenerRecorder::startReceivingInput()
{
	//Note: The following code has somewhat C style, which might be the wrong
	//way to do things in C++
	PaStreamParameters inputParameters, outputParameters;
	PaStream *stream;
	PaError err;

	//Start up portaudio and check for errors.
	err = Pa_Initialize();
	if ( err != paNoError ) reportError(err);

	// Get the default input device, complain if there is none
	inputParameters.device = Pa_GetDefaultInputDevice();
	if (inputParameters.device == paNoDevice) {
		std::cerr << "Error: No default input device.\n";
		reportError(err);
	}
	//Set the input device parameters based on our #defines
	inputParameters.channelCount = 1;
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	//Get the default output device, complain if none
	outputParameters.device = Pa_GetDefaultOutputDevice();
	if (outputParameters.device == paNoDevice) {
		std::cerr << "Error: No default output device.\n";
		reportError(err);
	}
	//Set the output parameters based on our #defines
	outputParameters.channelCount = 1;
	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	err = Pa_OpenStream(
		&stream,
		&inputParameters,
		&outputParameters,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		0,
		AudioListenerRecorder::processAudio,
		&(this->lastInputBuffer) );

	if (err != paNoError) reportError(err);

	err = Pa_StartStream(stream);
	if (err != paNoError) reportError(err);
}


void AudioListenerRecorder::stopReceivingInput()
{
	Pa_Terminate();
}

AudioListenerRecorder::~AudioListenerRecorder()
{
	Pa_Terminate();
}

bool AudioListenerRecorder::hasEvents()
{
	return events.size() > 0;
}

/*
Return whatever event was detected
*/
AudioListenerRecorder::AudioEvent AudioListenerRecorder::getEvent()
{
	return NOTHING;
}
using namespace std;

int AudioListenerRecorder::processAudio( const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData )
{
	size_t numBytesToCopy = framesPerBuffer * sizeof(PA_SAMPLE_TYPE);
	float* outputAudio = (float *) outputBuffer;
	const float * inputAudio = (const float *) inputBuffer;

	//Get the mutex for the audio buffer
	bufferMutex.lock();

	//Check if the input buffer is null. If so, write zeros.
	//If not, check for events
	if (inputBuffer == NULL) {
		memset(outputBuffer,0,numBytesToCopy);
	} else {
		//Call our subscriber and have it process audio, if it exists
		if (audioListenerRecorder->subscriber != NULL) {
			audioListenerRecorder->subscriber->processInput(inputAudio,framesPerBuffer);
		}
		//Save the last input buffer and redirect it to the output
		audioListenerRecorder->lastInputBuffer.clear();
		for (int i = 0; i < framesPerBuffer; i++) {
			outputAudio[i] = inputAudio[i];
			audioListenerRecorder->lastInputBuffer.push_back(inputAudio[i]);
		}
		//See if any screams started
		//checkForAudioEvents(inputBuffer,numBytesToCopy);
	}

	bufferMutex.unlock();

	return paContinue;
}

//Just sets the singleton reference
AudioListenerRecorder::AudioListenerRecorder()
{
	AudioListenerRecorder::audioListenerRecorder = this;
	this->subscriber = NULL;
}

AudioListenerRecorder* AudioListenerRecorder::getAudioListenerRecorder()
{
	if (audioListenerRecorder == NULL) {
		audioListenerRecorder = new AudioListenerRecorder();
	}

	return audioListenerRecorder;
}

void AudioListenerRecorder::addSubscriber( UGen* subscriber )
{
	this->subscriber = subscriber;
}
