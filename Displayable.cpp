#include "pch.h"
#include "Displayable.h"


Displayable::Displayable(sf::Vector2f _position, sf::Texture* _texture, int _id, sf::Vector2f _velocity, sf::Vector2f _origin, int _radius)
	: velocity(_velocity), id(_id), radius(_radius)
{
	sprite.setTexture(*_texture);
	//if ((_position.x > 0) && (_position.y > 0)) sprite.setPosition(_position);
	sprite.setPosition(_position);
	sprite.setOrigin(_origin);
	//sprite.setScale(sf::Vector2f(3, 3));
}