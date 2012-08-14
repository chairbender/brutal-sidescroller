#include "PixelArray.h"
#include <SFML/Config.hpp>

#define byte unsigned char


sf::Color intToColor(int color) {
	sf::Color resultColor;
	sf::Uint8* bytePointer = (sf::Uint8*) &color;
	resultColor.r = *bytePointer;
	bytePointer++;
	resultColor.g = *bytePointer;
	bytePointer++;
	resultColor.b = *bytePointer;
	bytePointer++;
	resultColor.a = *bytePointer;
	bytePointer++;

	return resultColor;
}

int colorToInt(sf::Color color) {
	int result;
	sf::Uint8* bytePointer = (sf::Uint8*) &result;
	*bytePointer = color.r;
	bytePointer++;
	*bytePointer = color.g;
	bytePointer++;
	*bytePointer = color.b;
	bytePointer++;
	*bytePointer = color.a;
	bytePointer++;

	return result;
}

PixelArray::PixelArray( int width, int height, sf::Color background /*= sf::Color(0,0,0,0)*/ )
{
	//Initialize the pixel array.
	pixels = new int[width*height];
	for (int i = 0; i < width*height; i++) {
		pixels[i] = colorToInt(background);
	}

	this->width = width;
	this->height = height;
	this->background = background;
}


const sf::Image* PixelArray::getImage()
{
	image.create(width,height,(const sf::Uint8*)pixels);
	return &image;
}


//Note: Only works for negative numbers right now (shifting left)
void PixelArray::shiftPixels(int pixelsToShift) {
	for (int y = 0; y < height; y++) {
		for (int x = -pixelsToShift; x < width; x++) {
			setPixel(x+pixelsToShift,y,intToColor(getPixel(x,y)));
			setPixel(x,y,background);
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
	pixels[y*width + x] = colorToInt(color);
}





