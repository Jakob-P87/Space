#include "player.h"
#include "Enemy.h"
#include <iostream>

int Player::score = 0;

Player::Player(std::vector<Enemy*> &alien) :
	enemy(alien)
{
	score = 0;

	//load the texture from disk
	m_Texture.loadFromFile("SpaceShip.png");

	m_Sprite.setTexture(m_Texture, true);

	//Set the center to middle of sprite
	sf::Vector2u size = m_Texture.getSize();
	m_Sprite.setOrigin(size.x / 2, size.y / 2);

	//set player start position
	m_Sprite.setPosition(384, 700);

	m_BulletTex.loadFromFile("Bullet.png");

	//Create a delay for the bullet to spawn
	shootDelay = 0;
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
	
	//check if shootbutton is held down
	bool shootWasPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	
	if (shootWasPressed && shootDelay < 0)
	{
		shootDelay = 0.5;
		//instansiate bullet
		m_Bullet.push_back(new Bullet(m_Sprite.getPosition(), m_BulletTex));
	}

	else
	{
		shootDelay -= dt;
	}
	
	for (auto it = m_Bullet.begin(); it < m_Bullet.end(); )
	{
		bool destroyBullet = false;

		//Destroy bullet if it's offscreen
		if ((*it)->getSprite().getPosition().y <= 0)
			destroyBullet = true;

		//Kill the enemies
		for (auto  it2 = enemy.begin(); it2 < enemy.end(); )
		{
			if ((*it2)->checkCollision((*it)->getSprite()))
			{
				destroyBullet = true;
				delete((*it2));
				it2 = enemy.erase(it2);

				score += 10; //Add to the score
			}
			else {
				it2++;
			}
		}

		if (destroyBullet) 
		{
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
//Checks for collision with enemy
bool Player::checkCollision(sf::Sprite &spr)
{
	return m_Sprite.getGlobalBounds().intersects(spr.getGlobalBounds());
}

