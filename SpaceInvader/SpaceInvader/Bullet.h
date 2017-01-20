#pragma once
#include <SFML\Graphics.hpp>

class Bullet
{
public:
	Bullet(sf::Vector2f startPos, sf::Texture &tex);
	~Bullet();

	const int MOVE_SPEED = -500;

	void update(sf::Time dt);
	void draw(sf::RenderWindow &win);
	sf::Sprite& getSprite();

private:
	sf::Sprite m_Sprite;
};