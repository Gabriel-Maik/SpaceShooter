//#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include <SFML/Audio.hpp>
#include "Game.h"

using std::cout;
using std::endl;
using std::vector;

int main()
{
	Game SpaceShooter;
	SpaceShooter.play();
	/*
	//vector<>
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window", sf::Style::Fullscreen);
	//sf::Window window(sf::VideoMode(800, 600), "My window");
	sf::Texture texture;
	if (!texture.loadFromFile("gfx/Spaceship5_64px.png"))
	{
		cout << "Critical error!" << endl;
		system("pause");
		return 0;
		// error...
	}
	sf::Font font;
	if (!font.loadFromFile("verdana.ttf"))
	{
		// error...
	}
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("sound/laser4.wav"))
		return -1;
	sf::Sound shoot;
	shoot.setBuffer(buffer);

	sf::Text tytul;
	tytul.setFillColor(sf::Color::White);
	tytul.setString("Space Shooter");
	tytul.setFont(font);
	tytul.setCharacterSize(50);
	tytul.setPosition(200.f, 100.f);

	sf::Sprite sprite;
	texture.setSmooth(false);
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(32.f, 32.f));
	sprite.setScale(sf::Vector2f(2.f, 2.f));

	window.setMouseCursorVisible(false);
	// inside the main loop, between window.clear() and window.display()
	// run the program as long as the window is open
	sprite.setPosition(sf::Vector2f(400.f, 500.f));
	while (window.isOpen())
	{
		//Sleep(1);
		//tytul.setPosition(tytul.getPosition() + sf::Vector2f(1, 0));
		 // absolute position
		window.draw(tytul);
		window.draw(sprite);
		
		window.display();
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::MouseMoved)
			{
				std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
				std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
				//sprite.move(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
				sprite.setPosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
			}
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				shoot.play();
			}
		}
		window.clear();
	}*/
	return 0;
}