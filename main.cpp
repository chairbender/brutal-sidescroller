#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <Windows.h>

//My headers
#include "Hero.h"
#include "BackgroundScroller.h"
#include <AudioListenerRecorder.h>
#include <SoundGraph.h>

using namespace sf;

//Holds the level's game objects
std::vector<GameObject*> gameObjects;

//Reference to our hero
Hero* hero;

//Our audio processing clas
AudioListenerRecorder* input;

//Prototypes
void loadGameObjects();

//TODO: Switch to portaudio. RTAudio isn't working due to some weird concurrency bug.
int main()
{

	//Reopen a console
	AllocConsole();
	freopen("CONIN$", "r",stdin);
	freopen("CONOUT$", "w",stdout);
	freopen("CONOUT$", "w",stderr);

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

	//Start the audio processing
	input = new AudioListenerRecorder();
	input->startReceivingInput();
	//Load the sound graph
	SoundGraph* soundGraph = new SoundGraph(*input,400,400,40,40);
	gameObjects.push_back(soundGraph);

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
		window.clear(sf::Color(224,232,255));
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

	input->stopReceivingInput();

    return EXIT_SUCCESS;
}

/*
initialize all the game objects in the level
*/
void loadGameObjects() {
	//Load our scrolling background texture
	gameObjects.push_back(new BackgroundScroller("sky.png",0,0,640,480,20));
	gameObjects.push_back(new BackgroundScroller("ground.png",0,240,640,240,1));
	//Load our hero
	hero = new Hero(0,240);
	hero->getSprite().setPosition(0,240 - hero->getSprite().getLocalBounds().height);
	gameObjects.push_back(hero);
	
}