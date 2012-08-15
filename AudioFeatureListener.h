/*
An AudioFeatureListener can be hooked up to the AudioListenerRecorder.
When AudioListenerRecorder gets new input data, it will pass that 
data to the AudioFeatureListener subscribed to it. The data passed includes
a pointer to the buffer (which is safe to modify in the current thread only)
and some audio features that AudioListenerRecorder can track.

*/
#ifndef H_UGEN
#define H_UGEN
class AudioFeatureListener {
public:
	AudioFeatureListener() { };
	~AudioFeatureListener() { };

	/*
	Handle input buffer. Each sample is a 32 bit floar.
	*/
	virtual void processInput(const float* input, int numSamples) = 0;
};
#endif