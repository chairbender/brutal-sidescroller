#include "AudioListenerRecorder.h"


void AudioListenerRecord::setFeedbackVolume( float decibels )
{
	feedbackVolume = decibels;
}

AudioEvent AudioListenerRecord::getEvent()
{

}


bool AudioListenerRecord::onStart()
{

}

bool AudioListenerRecord::onProcessSamples( const sf::Int16* samples, std::size_t sampleCount )
{
	//Output this chunk of audio to the output stream.

}

void AudioListenerRecord::onStop()
{

}