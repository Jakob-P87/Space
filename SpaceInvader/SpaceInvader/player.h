#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Bullet.h"
#include "Enemy.h"

class Player
{
public:
	Player(std::vector<Enemy*> &alien);
	~Player();

	void draw(sf::RenderWindow &win);
	void update(sf::Time delta);
	sf::Sprite& getSprite();

private:
	sf::SoundBuffer m_SFX;
	sf::Sound m_Sound;

	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

	sf::Texture m_BulletTex;

	std::vector<Bullet*> m_Bullet;
	std::vector<Enemy*> &enemy;

	float shootDelay;
	bool m_ShootPressed;
};