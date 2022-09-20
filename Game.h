#pragma once
#define windowWidth 1920
#define windowHeight 1080
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <time.h>
#include <string>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <sstream>
#include "ship.h"
#include "bullet.h"

using std::map;
using std::vector;

class Game
{
	int scorePoints;
	bool ifPlay;
	int whichLevel;
	Ship* player;
	int playerRadius;
	sf::Texture playerShip;
	sf::Texture enemyShip;
	sf::Texture asteroid;
	sf::Texture enemyBullet;
	sf::Texture laser;
	map<int, Bullet*> enemyBullets;
	map<int, Bullet*> playerBullets;
	map<int, Ship*> ships;
	int id;
	sf::SoundBuffer shoot;
	sf::SoundBuffer enemyShoot;
	sf::SoundBuffer explosion;
	sf::Sound soundShoot;
	sf::Sound soundEnemyShoot;
	sf::Sound soundExplosion;
	sf::Music music;
	sf::Font font;
	void inc();
public:
	Game();
	~Game();
	void play();
	void createShip(sf::Vector2f _initialPosition, sf::Texture* _texture, sf::Vector2f _velocity, int _directionChangeAt = 500);
	void createBullet(sf::Vector2f _initialPosition, sf::Vector2f _velocity, bool _player = false, int _radius = 5, sf::Texture* _texture = nullptr, bool ifSound = true);
	void deleteShips();
	void deleteBullets();
	void shipsActions();
	bool playerCollide();
	void enemyCollision();
	void level();
	void render(sf::RenderWindow& window);
	void restart();
	void createRandomShip(int howMany = 1);
	void saveScore() const;
	void saveHighscore() const;
};

