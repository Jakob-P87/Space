#include "Bullet.h"

//Set the sprite position and center the sprite
Bullet::Bullet(sf::Vector2f startPos, sf::Texture &tex) :
	m_Sprite(tex)
{
	m_Sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
	m_Sprite.setPosition(startPos);
}


Bullet::~Bullet()
{
}

void Bullet::update(sf::Time dt) 
{
	float delta = dt.asSeconds();
	m_Sprite.move(0, MOVE_SPEED * delta); //Multiplies the movespeed with delta on Y axis
}

void Bullet::draw(sf::RenderWindow &win)
{
	win.draw(m_Sprite);
}

sf::Sprite& Bullet::getSprite() 
{
	return m_Sprite;
}
