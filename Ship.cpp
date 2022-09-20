#include "pch.h"
#include "Ship.h"
#include "Game.h"

Ship::Ship(sf::Vector2f _initialPosition, sf::Texture* _texture, int _id, sf::Vector2f _velocity, int _radius, int _directionChangeAt, Game* _game)
	: Displayable(_initialPosition, _texture, _id, _velocity, sf::Vector2f(32.f, 32.f), _radius), phase(0), game(_game), directionChangeAt(_directionChangeAt)
{
}

void Ship::action()
{
	switch (phase)
	{
	case 0:
		if (sprite.getPosition().y > 100)
		{
			game->createBullet(sprite.getPosition(), sf::Vector2f(0.f, 12.f));
			phase++;
			shootAfter = sprite.getPosition().y + 200;
		}
		break;
	case 1:
		if (sprite.getPosition().y > directionChangeAt)
		{
			velocity = sf::Vector2f(4.f, 0.f);
			phase++;
			sprite.setRotation(270);
		}
		else if (sprite.getPosition().y > shootAfter) phase--;
		break;
	case 2:
		game->createBullet(sprite.getPosition(), sf::Vector2f(12.f, 0.f));
		phase++;
		shootAfter = sprite.getPosition().x + 100;
		break;
	case 3:
		if (sprite.getPosition().x > shootAfter) phase--;
		break;
	default:
		break;
	}
}

void Ship::action2()
{
	switch (phase)
	{
	case 0:
		if (sprite.getPosition().y > 100)
		{
			game->createBullet(sprite.getPosition(), sf::Vector2f(0.f, 12.f));
			phase++;
			shootAfter = sprite.getPosition().y + 200;
		}
		break;
	case 1:
		if (sprite.getPosition().y > shootAfter) phase--;
		break;
	default:
		break;
	}
}

void Ship::operator[](int whichAction)
{
	switch (whichAction)
	{
	case 0:
		break;
	case 1:
		action();
		break;
	case 2:
		action2();
		break;
	default:
		break;
	}
}
