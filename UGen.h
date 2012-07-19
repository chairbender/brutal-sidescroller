/*
This is represents a pluggable audio component.
Each ugen can take input and produce output. This happens when the portaudio callback is called - it passes
on audio to whatever it is connected to.
Here's how it works:

A UGen, UGen1 is instantiated. UGen2 is also. UGen1.addOutput(UGen2).
At some point, UGen1 creates audio data. It then invokes UGen2's processInput method with the audio data
it produced as an argument.

*/
#ifndef H_UGEN
#define H_UGEN
class UGen {
public:
	UGen() { };
	~UGen() { };

	/*
	Handle input buffer. Each sample is a 32 bit floar.
	*/
	virtual void processInput(const float* input, int numSamples) = 0;
};
#endif