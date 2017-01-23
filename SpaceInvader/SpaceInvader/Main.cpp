#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

const int ENEMY_MOVE = 100;

int main()
{
	sf::Clock deltaTimer;

	sf::RenderWindow window(sf::VideoMode(768, 768), "Space Invaders");

	//load our font for score tracking
	sf::Font scoreFont;
	scoreFont.loadFromFile("8-bit pusab.TTF");

	//Set size, color and position of the font
	sf::Text scoreText("Score: ", scoreFont, 16);
	scoreText.setColor(sf::Color::White);
	scoreText.setPosition(20, 20);


	sf::Texture alienTex;
	alienTex.loadFromFile("Alien.png");
	sf::Vector2f startPos(50,50);

restart: //If the enemy collides with the player

	std::vector<Enemy*> enemy;

	Player playerObj(enemy);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//if we recieve a close event
			//close window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//If the last enemy is destroyed create new enemies
		if (enemy.size() == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					enemy.push_back(new Enemy(alienTex, (startPos.x * i) + 50, startPos.y * j + 50));
				}
			}
		}

		sf::Time dt = deltaTimer.restart();
		window.clear();

		playerObj.update(dt);

		playerObj.draw(window);

		for (auto it = enemy.begin(); it != enemy.end(); it++)
		{
			(*it)->update(dt);
			(*it)->draw(window);

			if ((*it)->checkCollision(playerObj.m_Sprite))
			{
				goto restart;
			}
		}

		//Draw the score
		std::stringstream scoreContents;
		scoreContents << "Score: " << Player::score;
		scoreText.setString(scoreContents.str());
		window.draw(scoreText);

		window.display();
	}
}