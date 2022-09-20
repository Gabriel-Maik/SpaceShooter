#include "pch.h"
#include "Bullet.h"


Bullet::Bullet(sf::Vector2f _initialPosition, sf::Texture* _texture, int _id, sf::Vector2f _velocity, int _radius)
	:Displayable(_initialPosition, _texture, _id, _velocity, sf::Vector2f(_radius, _radius), _radius)
{
	if (_radius < 0) radius = 0;
	else radius = _radius;
}
