#include "AudioListenerRecorder.h"
#include "RtAudio.h"

#define PA_SAMPLE_TYPE paFloat32
#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (64)

void AudioListenerRecorder::setFeedbackVolume( float decibels )
{
	feedbackVolume = decibels;
	//TODO: Make it have an effect
}

AudioListenerRecorder::AudioEvent AudioListenerRecorder::getEvent()
{
	return NOTHING;
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
	
	//Check if the input buffer is null. If so, write zeros
	if (inputBuffer == NULL) {
		memset(outputBuffer,0,framesPerBuffer);
	} else {
		memcpy( outputBuffer, inputBuffer, framesPerBuffer);
	}

	return paContinue;
}


void AudioListenerRecorder::startReceivingInput()
{
	//Note: The following code has somewhat C style, which might be the wrong
	//way to do things in C++
	PaStreamParameters inputParameters, outputParameters;
	PaStream *stream;
	PaError err;

	//Start up portaudio and check for errors.
	//TODO: Force it to use DSOUND or some other host api. Not Asio.
	err = Pa_Initialize();
	if ( err != paNoError ) goto error;

	// Get the default input device, complain if there is none
	inputParameters.device = Pa_GetDefaultInputDevice();
	if (inputParameters.device = paNoDevice) {
		std::cerr << "Error: No default input device.\n";
		goto error;
	}
	//Set the input device parameters based on our #defines
	inputParameters.channelCount = 2;
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

	//Get the default output device, complain if none
	outputParameters.device = Pa_GetDefaultOutputDevice();
	if (outputParameters.device = paNoDevice) {
		std::cerr << "Error: No default output device.\n";
		goto error;
	}
	//Set the output parameters based on our #defines
	outputParameters.channelCount = 2;
	outputParameters.sampleFormat = PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
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
	if (err != paNoError) goto error;

	err = Pa_StartStream(stream);
	if (err != paNoError) goto error;



error:
	Pa_Terminate();
	std::cerr << "An error occured while using the portaudio stream\n";
	std::cerr << "Error number: " << err;
	std::cerr << "Error message: " << Pa_GetErrorText(err);
}

void AudioListenerRecorder::stopReceivingInput()
{
	Pa_Terminate();
}

AudioListenerRecorder::~AudioListenerRecorder()
{
	Pa_Terminate();
}
