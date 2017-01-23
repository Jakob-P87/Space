#pragma once
#include <SFML\Graphics.hpp>
#include <math.h>
class Enemy
{
public:
	int MOVE_SPEED = 60;

	Enemy(sf::Texture &tex, float xpos, float ypos); //Variables for the sprite position
	~Enemy();

	void draw(sf::RenderWindow &win);
	void update(sf::Time delta);
	bool checkCollision(sf::Sprite& spr);

private:
	//sprite definitions
	sf::Sprite m_Alien;
	sf::Vector2f startPos;

	int dir;
};