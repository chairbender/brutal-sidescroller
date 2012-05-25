#include <iostream>

#include "TextureManager.h"

using namespace std;

TextureManager gTextureManager;

sf::Texture* TextureManager::load( const std::string& strId ) {
	sf::Image image;
	sf::Texture* texture = new sf::Texture();
	if( !image.loadFromFile( "sprites/" + strId ) ) {
		cout << "[WARN] ImageManager failed to load: " << strId << endl;
		delete texture;
		texture = NULL;
	} else {
		image.createMaskFromColor(image.getPixel(0,0));
		texture->loadFromImage(image);
	}

	return texture;
}