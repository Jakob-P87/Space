#include "Enemy.h"
#include "Bullet.h"
#include<iostream>


Enemy::Enemy(sf::Texture &tex, float xpos, float ypos) :
	//use member initializers to set texture
	m_Alien(tex), startPos(xpos, ypos)
{
	//get size in order to center origin
	sf::Vector2u topSize = tex.getSize();

	//center origin on x-axis only!
	m_Alien.setOrigin(topSize.x / 2, 0);

	//set startpos offscreen to the right
	float startPos = 100;
	dir = 1;

	m_Alien.setPosition(xpos , ypos);

}


Enemy::~Enemy()
{
}

void Enemy::draw(sf::RenderWindow &win) 
{
	win.draw(m_Alien);
}

void Enemy::update(sf::Time delta)
{
	float dt = delta.asSeconds();
	
	m_Alien.move(MOVE_SPEED * dt *dir, 0);

	if (abs(m_Alien.getPosition().x - startPos.x) > 200)
	{
		m_Alien.move(0, 30);
		startPos = m_Alien.getPosition();
		dir = -dir;
	}
}