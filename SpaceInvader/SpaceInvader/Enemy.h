#pragma once
#include <SFML\Graphics.hpp>
#include <math.h>
class Enemy
{
public:
	//texture reference in constructor to save memory
	const int MOVE_SPEED = 30;

	Enemy(sf::Texture &tex, float xpos, float ypos);
	~Enemy();

	void draw(sf::RenderWindow &win);
	void update(sf::Time delta);

private:
	//sprite definitions
	sf::Sprite m_Alien;
	sf::Vector2f startPos;

	int dir;
};