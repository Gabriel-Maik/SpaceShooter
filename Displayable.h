#pragma once
#include <SFML/Graphics.hpp>

class Displayable
{
protected:
	sf::Sprite sprite;
	sf::Vector2f velocity;
	int id;
	int radius;
public:
	Displayable() { ; }
	Displayable(sf::Vector2f _position, sf::Texture* _texture, int _id, sf::Vector2f _velocity = sf::Vector2f(0.f, 0.f), sf::Vector2f _origin = sf::Vector2f(32.f, 32.f), int _radius = 0);
	sf::Sprite getSprite() const { return sprite; }
	void setPosition(sf::Vector2f _newPosition) { sprite.setPosition(_newPosition); }
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	sf::Vector2f getVelocity() const { return velocity; }
	int getRadius() { return radius; }
	int getId() const { return id; }
};

