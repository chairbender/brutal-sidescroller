#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
//////////////////////////////////////////////////////////////////////////
//Provides a sequence of textures that can be iterated through
//////////////////////////////////////////////////////////////////////////
class Animation
{
public:
	/*
	Create an animation using the specified prefix,
	so it will look in the sprite folder for prefix_0000.png thru
	prefix_9999.png and create the sequence based on that order.
	The prefix passed should NOT include the trailing _
	*/
	Animation(const std::string & prefixInSpriteFolder);
	~Animation(void);

	/*
	Returns the texture at the specified frame index
	*/
	const sf::Texture* getFrame(int index) const;

	/*
	Returns number of frames
	*/
	const int numFrames() const;

private:
	std::vector<sf::Texture*> frames;

};

