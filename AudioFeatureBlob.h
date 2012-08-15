/*
AudioFeatureBlob is a container for 
data that is passed to AudioFeatureListeners when
their processInput method is called. It contains a pointer
to the buffer holding the new input, and some
audio features.
*/
class AudioFeatureBlob {
public:
	AudioFeatureBlob(const float * pInputBuffer) { };
	~AudioFeatureBlob() { };

	//The audio data
	const float * inputBuffer;

	//Some handy audio features
	float max

};