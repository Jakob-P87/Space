#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include"Enemy.h"

const int ENEMY_MOVE = 100;

int main()
{
	sf::Clock deltaTimer;

	sf::RenderWindow window(sf::VideoMode(768, 768), "Space Invaders");

	sf::Texture alienTex;
	alienTex.loadFromFile("Alien.png");
	sf::Vector2f startPos(50,50);

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
		}

		window.display();
	}
}