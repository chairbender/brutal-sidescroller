#include "PixelArray.h"
#include <SFML/Config.hpp>

#define byte unsigned char

PixelArray::PixelArray( int width, int height, sf::Color background /*= sf::Color(0,0,0,0)*/ )
{
	//Initialize the pixel array.
	pixels = new int[width*height];

	this->width = width;
	this->height = height;
}


const sf::Image* PixelArray::getImage()
{
	image.create(width,height,(const sf::Uint8*)pixels);
	return &image;
}

void PixelArray::shiftPixels(int pixelsToShift) {
	for (int y = 0; y < height; y++) {
		for (int x = 1; x < width; x++) {
			//TODO: Implement
		}
	}
}

/*
Returns the pixel at the x and y coordinates
*/
int PixelArray::getPixel(int x, int y) {
	return pixels[y*width + x];
}

void PixelArray::setPixel( int x, int y, sf::Color color )
{
	sf::Uint8* bytePointer = (sf::Uint8*) &(pixels[y*width + x]);
	*bytePointer = color.r;
	bytePointer++;
	*bytePointer = color.g;
	bytePointer++;
	*bytePointer = color.b;
	bytePointer++;
	*bytePointer = color.a;
	bytePointer++;
}





