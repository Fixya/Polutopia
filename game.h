#pragma once
#include "settings.h"
#include "player.h"
#include <list>
#include <vector>
#include "unit.h"
#include "Text.h"
#include <iostream>

class Game {
public:
	Game() : text_player_go("Player 1", sf::Vector2f{0.f, 0.f})
	{
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		Player* pw1 = new Player(PLAYER_FILE_NAME, sf::Vector2f{ 360, 145 });
		playerWhiteSprites.push_back(pw1);
		Player* pb1 = new Player(PLAYER1_FILE_NAME, sf::Vector2f{ 633, 540 });
		playerBlackSprites.push_back(pb1);
		Units* uw1 = new Units((Units::UnitType)0, sf::Vector2f{ 0.f, -100.f });
		unitWhiteSprites.push_back(uw1);

		Units* ub1 = new Units((Units::UnitType)0, sf::Vector2f{ 0.f, -100.f });
		unitBlackSprites.push_back(ub1);
	}

	void play() {
		while (window.isOpen()) {
			checkEvents();
			update();
			checkCollisions();
			draw();
		}
	}

	void land();
	void unitWMade(int n, Player* player);
	void unitBMade(int n, Player* player);
private:
	sf::RenderWindow window;
	sf::RectangleShape block[COL_LINE][COL_ROW];
	std::list<Player*> playerWhiteSprites;
	std::list<Player*> playerBlackSprites;
	int qtyWhite = 1, qtyBlack = 1;
	std::list<Units*> unitWhiteSprites;
	std::list<Units*> unitBlackSprites;
	int partic = 0;
	TextObj text_player_go;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void update() {
		land();
		if (partic == 0) {
			for (auto player : playerWhiteSprites) {
				player->update();
				for (auto unit : unitWhiteSprites) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { unitWMade(0, player); }
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { unitWMade(1, player); }
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { unitWMade(2, player); }
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) partic = 1;
		}
		if (partic == 1) {
			for (auto player : playerBlackSprites) {
				player->update();
				for (auto unit : unitBlackSprites) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { unitBMade(0, player); }
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { unitBMade(1, player); }
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { unitBMade(2, player); }
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) partic = 0; 
		}
		
	}

	void checkCollisions() {}

	void draw() {
		window.clear();
		for (int j = 0; j < COL_ROW; j++) {
			for (int i = 0; i < COL_LINE; i++)
				window.draw(block[i][j]);
		}
		for (auto player : playerWhiteSprites)
			window.draw(player->getSprite());
		for (auto player : playerBlackSprites)
			window.draw(player->getSprite());
		for (auto unit : unitWhiteSprites)
			unit->draw(window);
		for (auto unit : unitBlackSprites)
			unit->draw(window);
		window.display();
	}
};

void Game::land()
{
	float k = BLOCK_HEIGHT, f = 50;
	for (int j = 0; j < COL_ROW; j++)
	{
		for (int i = 0; i < COL_LINE; i++)
		{
			block[i][j].setSize(sf::Vector2f{ BLOCK_WIDTH, BLOCK_HEIGHT });
			block[i][j].setFillColor(BLOCK_COLOR);
			block[i][j].setPosition(f, k);
			f += BLOCK_WIDTH + 5;
		}
		f = 50;
		k += BLOCK_HEIGHT + 5;
	}
}

void Game::unitWMade(int n, Player* player) {
	Units* uw2 = new Units((Units::UnitType)n, player->getPosition());
	unitWhiteSprites.push_back(uw2);
}
void Game::unitBMade(int n, Player* player) {
	Units* ub2 = new Units((Units::UnitType)n, player->getPosition());
	unitBlackSprites.push_back(ub2);
}