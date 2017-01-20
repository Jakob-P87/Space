#include "player.h"
#include <iostream>


Player::Player()
{
	//load the texture from disk
	m_Texture.loadFromFile("SpaceShip.png");

	m_Sprite.setTexture(m_Texture, true);

	sf::Vector2u size = m_Texture.getSize();
	m_Sprite.setOrigin(size.x / 2, size.y / 2);

	//set player start position
	m_Sprite.setPosition(384, 700);

	m_BulletTex.loadFromFile("Bullet.png");
}


Player::~Player()
{
}

void Player::draw(sf::RenderWindow &win) 
{
	//itreate bullet vector and draw all instances
	for (auto it = m_Bullet.begin(); it < m_Bullet.end(); it++)
	{
		(*it)->draw(win);
	}

	win.draw(m_Sprite);
}

//Inputs for player movement
void Player::update(sf::Time delta)
{
	//convert sf::Time to seconds
	float dt = delta.asSeconds();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		// move left
		m_Sprite.move(-200 * dt, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// move right
		m_Sprite.move(200 * dt, 0);
	}

	float xPos = m_Sprite.getPosition().x;
	
	//Collision with window border
	if (m_Sprite.getPosition().x < m_Sprite.getLocalBounds().width / 2)
	{
		m_Sprite.move((m_Sprite.getLocalBounds().width / 2) - xPos, 0);
	}

	//Collision with window border
	if (m_Sprite.getPosition().x > 768 - (m_Sprite.getLocalBounds().width / 2))
	{
		m_Sprite.move(768 - (m_Sprite.getLocalBounds().width / 2) - xPos, 0);
	}
	
	//check if shootbutton was pressed
	bool shootWasPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	
	if (shootWasPressed && !m_ShootPressed)
	{
		//set flag to true for debounce
		m_ShootPressed = true;
		//instansiate bullet
		m_Bullet.push_back(new Bullet(m_Sprite.getPosition(), m_BulletTex));
	}
	
	//reset flag if shootbutton is not pressed
	else if (!shootWasPressed && m_ShootPressed)
	{
		m_ShootPressed = false;
	}
	for (auto it = m_Bullet.begin(); it < m_Bullet.end(); )
	{
		bool destroyBullet = false;

		//also destroy bullet if it's offscreen
		if ((*it)->getSprite().getPosition().y <= 0)
			destroyBullet = true;

		if (destroyBullet) {
			//clean up and destroy bullet
			delete((*it));
			it = m_Bullet.erase(it);
		}
		//if not destroy bullet
		else {
			//update and increment iterator
			(*it)->update(delta);
			it++;
		}
	}



}

sf::Sprite& Player::getSprite()
{
	return m_Sprite;
}
