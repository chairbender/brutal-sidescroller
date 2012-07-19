/*
PixelArray represents an array of pixels. It is
fast to update and display (as an image).
*/
#include "SFML/Graphics.hpp"

class PixelArray {
public:
	/*
	Creates the pixelarray with the specified dimensions and set
	to the specified color background.
	*/
	PixelArray(int width, int height, sf::Color background = sf::Color(0,0,0,0));

	//TODO: Finish implementing the PixelArray

	/*
	Sets the pixel at the specified x and y position
	*/
	void setPixel(int x, int y, sf::Color color);

	/*
	Get the Image that represents the display of this PixelArray
	*/
	const sf::Image* getImage();

	/*
	Shifts all of the pixels horizontally by the specified amount.
	Negative means shift left.
	*/
	void shiftPixels(int pixelsToShift);

private:
	sf::Image image;
	int* pixels;
	int width, height;

	int getPixel(int x, int y);
};