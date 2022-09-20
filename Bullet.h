#pragma once
#include "Displayable.h"
class Bullet :
	public Displayable
{
	int radius;
public:
	Bullet(sf::Vector2f _initialPosition, sf::Texture* _texture, int _id, sf::Vector2f _velocity, int _radius);
};

