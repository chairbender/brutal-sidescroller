#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <vector>

//My headers
#include "Ground.h"
#include "Hero.h"

using namespace sf;

//Holds the level's game objects
std::vector<GameObject*> gameObjects;

//Reference to our hero
Hero* hero;

//Prototypes
void loadGameObjects();

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Brootal March");

	//Load game objects
	loadGameObjects();

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
		for (int i = 0; i < gameObjects.size(); i++) {
			gameObjects.at(i)->update();
		}

		// Draw everything.
		window.clear();
		for (int i = 0; i < gameObjects.size(); i++) {
			window.draw(gameObjects.at(i)->getSprite());
		}
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

/*
initialize all the game objects in the level
*/
void loadGameObjects() {
	//Load our scrolling background texture
	gameObjects.push_back(new Ground(0,240,640,240,1));
	//Load our hero
	hero = new Hero(0,240);
	hero->getSprite().setPosition(0,240 - hero->getSprite().getLocalBounds().height);
	gameObjects.push_back(hero);
}