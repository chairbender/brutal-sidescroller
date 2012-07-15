#include "AudioListenerRecorder.h"
#include <system_error>
#include <iostream>

#define PA_SAMPLE_TYPE paFloat32
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (paFramesPerBufferUnspecified)

#define PEAK_THRESHOLD

void AudioListenerRecorder::setFeedbackVolume( float decibels )
{
	feedbackVolume = decibels;
	//TODO: Make it have an effect
}

void checkForAudioEvents(const void *inputBuffer, size_t numBytes) {

}

/*
Callback function for audio processing
*/
static int inout( const void *inputBuffer, void *outputBuffer, 
	unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags,
	void *userData )
{
	size_t numBytesToCopy = framesPerBuffer * sizeof(PA_SAMPLE_TYPE);

	//Check if the input buffer is null. If so, write zeros.
	//If not, check for events
	if (inputBuffer == NULL) {
		memset(outputBuffer,0,numBytesToCopy);
	} else {
		checkForAudioEvents(inputBuffer,numBytesToCopy);
		memcpy( outputBuffer, inputBuffer, numBytesToCopy);
	}

	return paContinue;
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
		inout,
		NULL );

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
