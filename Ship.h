#pragma once
#include "Displayable.h"

class Game;
class Ship :
	public Displayable
{
	int phase;
	Game* game;
	int directionChangeAt;
	int shootAfter;
public:
	Ship(sf::Vector2f _initialPosition, sf::Texture* _texture, int _id, sf::Vector2f _velocity, int _radius = 25, int _directionChangeAt = 500, Game* _game = nullptr);
	void action();
	void action2();
	void operator[] (int whichAction);
};

