#include "Game.h"

Game::Game()
	: id(0), playerRadius(23), ifPlay(false), whichLevel(0), scorePoints(0)
{
	srand(time(NULL));
	playerShip.loadFromFile("gfx/Spaceship5_64px.png");
	player = new Ship(sf::Vector2f(windowWidth/2, windowHeight - 200), &playerShip, id, sf::Vector2f(0.f, 0.f));
	inc();
	enemyShip.loadFromFile("gfx/Enemy4.0.0_64px.png");
	asteroid.loadFromFile("gfx/Asteroid.png");
	enemyBullet.loadFromFile("gfx/bullet.png");
	laser.loadFromFile("gfx/laser.png");
	font.loadFromFile("fonts/verdana.ttf");
	shoot.loadFromFile("sound/laser4.wav");
	soundShoot.setBuffer(shoot);
	soundShoot.setVolume(60);
	enemyShoot.loadFromFile("sound/old/laser1.wav");
	soundEnemyShoot.setBuffer(enemyShoot);
	soundEnemyShoot.setVolume(35);
	explosion.loadFromFile("sound/wybuch od Kuby.wav");
	soundExplosion.setBuffer(explosion);
	music.openFromFile("sound/music4.wav");
	music.setLoop(1);
	music.setVolume(80);
}

Game::~Game()
{
	ships.clear();
	enemyBullets.clear();
	playerBullets.clear();
	delete player;
}

void Game::inc()
{
	if (id < 10000) id++;
	else id = 0;
}

void Game::play()
{
	clock_t time = clock();
	sf::RenderWindow window(sf::VideoMode(windowWidth-10, windowHeight-10), "Space Shooter", sf::Style::Fullscreen/*sf::Style::Default*/);
	music.play();
	sf::Text title;
	title.setString("Space Shooter");
	title.setFillColor(sf::Color::Green);
	title.setFont(font);
	title.setCharacterSize(87);
	title.setPosition(windowWidth/2 - 350, 50);
	window.draw(title);
	sf::Text instruction;
	instruction.setString("Press any key to start");
	instruction.setFillColor(sf::Color::Green);
	instruction.setFont(font);
	instruction.setCharacterSize(24);
	instruction.setPosition(windowWidth/2 - 150, windowHeight - 100);
	window.draw(instruction);
	sf::Text score;
	score.setString("Score: 0");
	score.setFillColor(sf::Color::Green);
	score.setFont(font);
	score.setCharacterSize(24);
	score.setPosition(windowWidth - 170, 30);
	window.setMouseCursorVisible(false);
	while (window.isOpen())
	{
		if (ships.size() == 0) level();

		//Sleep(20);
		if ((time - clock()) / CLOCKS_PER_SEC < 20) Sleep(20 - (time - clock()) / CLOCKS_PER_SEC);
		time = clock();

		deleteShips();
		render(window);
		window.draw(player->getSprite());
		if (playerCollide())
		{
			saveScore();
			try
			{
				saveHighscore();
			}
			catch (std::exception e)
			{
				std::ofstream file;
				file.open("scores/highscore.txt", std::ofstream::out);
				file << 0;
				file.close();
				saveHighscore();
			}
			score.setString(std::string("Score: ").append(std::to_string(scorePoints)));
			if (ifPlay) window.draw(score);
			soundExplosion.play();
			sf::Text gameOver;
			gameOver.setString("Game Over");
			gameOver.setFillColor(sf::Color::Red);
			gameOver.setFont(font);
			gameOver.setCharacterSize(115);
			gameOver.setPosition(-375 + (windowWidth / 2), windowHeight / 2 - 100);
			ifPlay = false;
			window.draw(gameOver);
			window.draw(instruction);
		}
		window.display();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseMoved)
			{
				player->setPosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
			}
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				/**
				if (event.key.code == sf::Keyboard::Enter)
				{
					
				}*/
			}
			if (event.type == sf::Event::TextEntered)
			{
				if ((event.text.unicode == 'p') || (event.text.unicode == 'P'))
				{
					while (true)
					{
						sf::Event event2;
						window.pollEvent(event2);
						if (event2.key.code == sf::Event::TextEntered) break;
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				createBullet(player->getPosition() + sf::Vector2f(0.f, -10.f), sf::Vector2f(0.f, -20.f), 1, 4, &laser);
			}
		}
		while ((ifPlay == false) && (window.isOpen()))
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				//render(window);
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						window.close();
					}
					if (event.key.code == sf::Keyboard::Enter)
					{
						scorePoints = 0;
						restart();
					}
				}
				if (event.type == sf::Event::TextEntered)
				{
					restart();
				}
			}
		}
		window.clear();
		shipsActions();
		enemyCollision();
		deleteBullets();
		score.setString(std::string("Score: ").append(std::to_string(scorePoints)));
		if (ifPlay) window.draw(score);
	}
}

void Game::createShip(sf::Vector2f _initialPosition, sf::Texture * _texture, sf::Vector2f _velocity, int _directionChangeAt)
{
	ships[id] = new Ship(_initialPosition, _texture, id, _velocity, 25, _directionChangeAt, this);
	inc();
}

void Game::createBullet(sf::Vector2f _initialPosition, sf::Vector2f _velocity, bool _player, int _radius, sf::Texture * _texture, bool ifSound)
{
	if (_texture == nullptr) _texture = &enemyBullet;
	if (_player == true)
	{
		playerBullets[id] = new Bullet(_initialPosition, _texture, id, _velocity, _radius);
		if (ifSound) soundShoot.play();
	}
	else
	{
		enemyBullets[id] = new Bullet(_initialPosition, _texture, id, _velocity, _radius);
		if (ifSound) soundEnemyShoot.play();
	}
	inc();
}

void Game::level()
{
	//if (whichLevel == 0) createBullet(sf::Vector2f(400.f, 500.f), sf::Vector2f(0.f, 0.5f), false, 16, &asteroid, false);
	//createShip(sf::Vector2f(100.f, -100.f), &enemyShip, sf::Vector2f(0.f, 2.f), 510);
	//createShip(sf::Vector2f(200.f, -100.f), &enemyShip, sf::Vector2f(0.f, 2.f), 400);
	//createShip(sf::Vector2f(300.f, -100.f), &enemyShip, sf::Vector2f(0.f, 2.f), 320);
	createRandomShip(3);
	if (whichLevel >= 1)
	{
		//createShip(sf::Vector2f(300.f, -100.f), &enemyShip, sf::Vector2f(0.f, 3.f), 535);
		//createShip(sf::Vector2f(500.f, -300.f), &enemyShip, sf::Vector2f(0.f, 3.f), 455);
		//createShip(sf::Vector2f(200.f, -400.f), &enemyShip, sf::Vector2f(0.f, 3.f), 290);
		createRandomShip(3);
	}
	if (whichLevel >= 2)
	{
		for (int i = 0; i < whichLevel; i++)
		{
			float vX = ((float)(((rand() % 101) - 50))) / 200;
			createBullet(sf::Vector2f((rand() % (windowWidth - 127) + 64), -100.f - (float)(i * 30)), sf::Vector2f(2*vX, 1.f), false, 16, &asteroid, false);
		}
	}
	if (whichLevel >= 4)
	{
		createRandomShip(whichLevel - 3);
	}
	whichLevel++;
}

void Game::render(sf::RenderWindow & window)
{
	for (std::map<int, Ship*>::iterator it = ships.begin(); it != ships.end(); ++it)
	{
		it->second->setPosition(it->second->getSprite().getPosition() + it->second->getVelocity());
		window.draw(it->second->getSprite());
	}
	for (std::map<int, Bullet*>::iterator it = playerBullets.begin(); it != playerBullets.end(); ++it)
	{
		it->second->setPosition(it->second->getSprite().getPosition() + it->second->getVelocity());
		window.draw(it->second->getSprite());
	}
	for (std::map<int, Bullet*>::iterator it = enemyBullets.begin(); it != enemyBullets.end(); ++it)
	{
		it->second->setPosition(it->second->getSprite().getPosition() + it->second->getVelocity());
		window.draw(it->second->getSprite());
	}
}

void Game::deleteShips()
{
	std::vector<int> toDelete;
	for (std::map<int, Ship*>::iterator it = ships.begin(); it != ships.end(); ++it)
	{
		if ((it->second->getPosition().x > windowWidth + 32) && (it->second->getVelocity().x >= 0)) toDelete.push_back(it->first);
		else if ((it->second->getPosition().y > windowHeight + 32) && (it->second->getVelocity().y >= 0)) toDelete.push_back(it->first);
		else if ((it->second->getPosition().x < -32) && (it->second->getVelocity().x <= 0)) toDelete.push_back(it->first);
		else if ((it->second->getPosition().y < -32) && (it->second->getVelocity().y <= 0)) toDelete.push_back(it->first);
	}
	for (int i = 0; i < toDelete.size(); i++)
	{
		ships.erase(toDelete[i]);
	}
}

void Game::deleteBullets()
{
	std::vector<int> toDelete;
	for (std::map<int, Bullet*>::iterator it = playerBullets.begin(); it != playerBullets.end(); ++it)
	{
		if ((it->second->getPosition().x > windowWidth + 32) && (it->second->getVelocity().x > 0)) toDelete.push_back(it->first);
		else if ((it->second->getPosition().y > windowHeight + 32) && (it->second->getVelocity().y > 0)) toDelete.push_back(it->first);
		else if ((it->second->getPosition().x < -32) && (it->second->getVelocity().x < 0)) toDelete.push_back(it->first);
		else if ((it->second->getPosition().y < -32) && (it->second->getVelocity().y < 0)) toDelete.push_back(it->first);
	}
	for (int i = 0; i < toDelete.size(); i++)
	{
		playerBullets.erase(toDelete[i]);
	}
	toDelete.clear();
	for (std::map<int, Bullet*>::iterator it = enemyBullets.begin(); it != enemyBullets.end(); ++it)
	{
		if ((it->second->getPosition().x > windowWidth + 32) && (it->second->getVelocity().x > 0)) toDelete.push_back(it->first);
		else if ((it->second->getPosition().y > windowHeight + 32) && (it->second->getVelocity().y > 0)) toDelete.push_back(it->first);
		else if ((it->second->getPosition().x < -32) && (it->second->getVelocity().x < 0)) toDelete.push_back(it->first);
		else if ((it->second->getPosition().y < -32) && (it->second->getVelocity().y < 0)) toDelete.push_back(it->first);
	}
	for (int i = 0; i < toDelete.size(); i++)
	{
		enemyBullets.erase(toDelete[i]);
	}
}

void Game::shipsActions()
{
	for (std::map<int, Ship*>::iterator it = ships.begin(); it != ships.end(); ++it)
	{
		//it->second->action();
		(*(it->second))[1];
	}
}

bool Game::playerCollide()
{
	for (std::map<int, Bullet*>::iterator it = enemyBullets.begin(); it != enemyBullets.end(); ++it)
	{
		if (sqrt(pow(it->second->getSprite().getPosition().x - player->getPosition().x, 2) + pow(it->second->getSprite().getPosition().y - player->getPosition().y, 2)) < playerRadius + it->second->getRadius()) return true;
	}
	return false;
}

void Game::enemyCollision()
{
	vector<int> toDelete;
	vector<int> bulletsToDelete;
	for (std::map<int, Ship*>::iterator itS = ships.begin(); itS != ships.end(); ++itS)
	{
		for (std::map<int, Bullet*>::iterator it = playerBullets.begin(); it != playerBullets.end(); ++it)
		{
			if (sqrt(pow(it->second->getPosition().x - itS->second->getPosition().x, 2) + pow(it->second->getPosition().y - itS->second->getPosition().y, 2)) < (itS->second->getRadius() + it->second->getRadius()))
			{
				soundExplosion.play();
				toDelete.push_back(itS->first);
				scorePoints++;
				bulletsToDelete.push_back(it->first);
			}
		}
	}
	for (int i = 0; i < toDelete.size(); i++) ships.erase(toDelete[i]);
	for (int i = 0; i < bulletsToDelete.size(); i++) playerBullets.erase(bulletsToDelete[i]);
}
// kd tree
void Game::restart()
{
	scorePoints = 0;
	ships.clear();
	playerBullets.clear();
	enemyBullets.clear();
	whichLevel = 0;
	ifPlay = true;
}

void Game::createRandomShip(int howMany)
{
	if (howMany < 0) howMany = 0;
	int directionChangeAt;
	for (int i = 0; i < howMany; i++)
	{
		do
		{
			directionChangeAt = rand() % ((int)(windowHeight * 2));
		} while ((directionChangeAt < (windowHeight + 32)) && (directionChangeAt > (windowHeight - 32)));
		createShip(sf::Vector2f((float)(rand() % (windowWidth - 127) + 64), (float)(0 - 64 - rand() % 251)), &enemyShip, sf::Vector2f(0.f, ((float)(rand() % 41)) / 5.f + 2.f), directionChangeAt);
	}
}

void Game::saveScore() const
{
	std::ofstream file;
	file.open("scores/scores.txt", std::ofstream::app);
	file << std::to_string(scorePoints) << std::endl;
	file.close();
}

void Game::saveHighscore() const
{
	int oldHighscore;
	std::fstream file;
	file.open("scores/highscore.txt", std::ifstream::in);
	if (file.good() != true) throw std::exception("File highscore.txt not found");
	std::string line;
	std::getline(file, line);
	std::istringstream lineStream(line);
	lineStream >> oldHighscore;
	file.close();
	if (scorePoints > oldHighscore)
	{
		file.open("scores/highscore.txt", std::ofstream::out);
		file << std::string(line.length(), ' ');
		file.close();
		file.open("scores/highscore.txt", std::ofstream::out);
		file << scorePoints;
		file.close();
	}
}
