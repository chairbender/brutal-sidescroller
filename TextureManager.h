#ifndef IMAGEMANAGER_H_INCLUDED
#define IMAGEMANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "ResourceManager.h"

class TextureManager : public ResourceManager< sf::Texture > {
private:
	bool isInitalized;
protected:
	/*
	Load the image with the specified name in the sprite folder. Uses the top
	left corner color to get the transparency color. Returns a pointer to the allocated
	image. Returns null if not found. This works even if used during static initialization.
	*/
	virtual sf::Texture* load( const std::string& locationInSpriteFolder );
public:
};

extern TextureManager gTextureManager;

#endif // IMAGEMANAGER_H_INCLUDED