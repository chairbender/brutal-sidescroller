#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>

//My headers
#include "Ground.h"

using namespace sf;
int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Brootal March");

	//Load our scrolling background texture into a sprite
	Ground ground(0,240,640,240,1);

	//Main loop
	const int FRAMES_PER_SECOND = 60;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	double skippedTime = 0;
	sf::Clock timer;
	timer.restart();
	
	double gameTick = timer.getElapsedTime().asMilliseconds();
	int sleepTime = 0;
    while (window.isOpen())
    {
		//Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Check for close event
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//update everything
		ground.update();

		// Draw everything.
		window.clear();
		window.draw(ground.getSprite());
		window.display();

		//handle FPS fixing
		gameTick += SKIP_TICKS;
		sleepTime = gameTick - timer.getElapsedTime().asMilliseconds();

		if (sleepTime >= 0)
		{
			sf::sleep(sf::milliseconds(sleepTime));
		}
		else {
			//Running behind for some reason
		}
    }

    return EXIT_SUCCESS;
}