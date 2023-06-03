#pragma once
#include "settings.h"
#include "player.h"
#include <list>
#include <vector>
#include "unit.h"
#include "Text.h"


class Game {
public:
	Game() : text_player_go("Player 1", sf::Vector2f{ 0.f, 0.f }), text_player_unit("walking units", sf::Vector2f{ 175.f, 0.f })
	{
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		for (int i = 0; i < 6; i++) {
			Player* pw1 = new Player(PLAYER_FILE_NAME, sf::Vector2f{ 90.f, float(80 + 65 * i) });
			playerWhiteSprites.push_back(pw1);
			Player* pb1 = new Player(PLAYER1_FILE_NAME, sf::Vector2f{ 900.f, float(80 + 65 * i) });
			playerBlackSprites.push_back(pb1);
			Units* uw1 = new Units((Units::UnitType)0, sf::Vector2f{ 170.f, float(75 + 65 * i) });
			unitWhiteSprites.push_back(uw1);
			Units* ub1 = new Units((Units::UnitType)3, sf::Vector2f{ 800.f, float(75 + 65 * i) });
			unitBlackSprites.push_back(ub1);
		}
		timer.restart();
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
	void unitWhiteUpdate(Player* player);
	void unitBlackUpdate(Player* player);
	void playerUnit(sf::RenderWindow& window);
	void allText(sf::RenderWindow& window);
private:
	sf::RenderWindow window;
	sf::RectangleShape block[COL_LINE][COL_ROW];
	std::list<Player*> playerWhiteSprites;
	std::list<Player*> playerBlackSprites;
	int qtyWhite = 1, qtyBlack = 1;
	std::list<Units*> unitWhiteSprites;
	std::list<Units*> unitBlackSprites;
	int partic, doru;
	TextObj text_player_go, text_player_unit;
	//std::list<int> goUnitW, goUnitB;
	sf::Clock timer;
	int currTime, prevTimeBlack, prevTimeWhite;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void update() {
		currTime = timer.getElapsedTime().asMilliseconds();
		land();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && partic == 0) { partic = 1; doru = 0; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && partic == 1) { partic = 0; doru = 0; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			doru = 0;
			text_player_unit.update("walking units");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			doru = 1;
			text_player_unit.update("Creation of units");
		}
		if (partic == 0) {
			for (auto player : playerWhiteSprites) {
				player->update();
				text_player_go.update("Player 1");
				unitWhiteUpdate(player);
			}
		}
		if (partic == 1) {
			for (auto player : playerBlackSprites) {
				player->update();
				text_player_go.update("Player 2");
				unitBlackUpdate(player);
			}
		}
	}

	void checkCollisions() {
		for (auto unitW : unitWhiteSprites) {
			sf::FloatRect unitWhiteHitBox = unitW->getHitBox();
			for (auto unitB : unitBlackSprites) {
				sf::FloatRect unitBlackHitBox = unitB->getHitBox();
				if (unitWhiteHitBox.intersects(unitBlackHitBox)) {
					if (partic == 0) { unitB->setDel(); }
					if (partic == 1) { unitW->setDel(); }
				}
			}
		}
		unitWhiteSprites.remove_if([](Units* unitB) {return unitB->isToDel(); });
		unitBlackSprites.remove_if([](Units* unitB) {return unitB->isToDel(); });
	}

	void draw() {
		window.clear();
		for (int j = 0; j < COL_ROW; j++) {
			for (int i = 0; i < COL_LINE; i++)
				window.draw(block[i][j]);
		}
		playerUnit(window);
		allText(window);
		window.display();
	}
};

void Game::land()
{
	for (int j = 0; j < COL_ROW; j++)
	{
		for (int i = 0; i < COL_LINE; i++)
		{
			block[i][j].setSize(sf::Vector2f{ BLOCK_WIDTH, BLOCK_HEIGHT });
			block[i][j].setFillColor(BLOCK_COLOR);
			block[i][j].setPosition(50 + (BLOCK_WIDTH + 5) * i, BLOCK_HEIGHT + (BLOCK_HEIGHT + 5) * j);
		}
	}
}

void Game::unitWMade(int n, Player* player) {
	Units* uw2 = new Units((Units::UnitType)n, (player->getPosition() + sf::Vector2f{ 80.f, -5.f }));
	unitWhiteSprites.push_back(uw2);
}
void Game::unitBMade(int n, Player* player) {
	Units* ub2 = new Units((Units::UnitType)n, (player->getPosition() - sf::Vector2f{ 100.f, 5.f }));
	unitBlackSprites.push_back(ub2);
}

void Game::unitWhiteUpdate(Player* player) {
	for (auto unit : unitWhiteSprites) {
		if (doru == 1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { unitWMade(0, player); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { unitWMade(1, player); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { unitWMade(2, player); }
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currTime - prevTimeWhite > INTERVAL_TIME) {
				if (unit->getPositionY() > 135) {
					unit->setPosition(unit->getPosition() - sf::Vector2f{ 0.f, 65.f });
					prevTimeWhite = currTime;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currTime - prevTimeWhite > INTERVAL_TIME) {
				if (unit->getPositionY() < 380) {
					unit->setPosition(unit->getPosition() + sf::Vector2f{ 0.f, 65.f });
					prevTimeWhite = currTime;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currTime - prevTimeWhite > INTERVAL_TIME) {
				if (unit->getPositionX() > 90) {
					unit->setPosition(unit->getPosition() - sf::Vector2f{ 90.f, 0.f });
					prevTimeWhite = currTime;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currTime - prevTimeWhite > INTERVAL_TIME) {
				unit->setPosition(unit->getPosition() + sf::Vector2f{ 90.f, 0.f });
				prevTimeWhite = currTime;
			}
		}
	}
}
void Game::unitBlackUpdate(Player* player) {
	for (auto unit : unitBlackSprites) {
		if (doru == 1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { unitBMade(3, player); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { unitBMade(4, player); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { unitBMade(5, player); }

		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currTime - prevTimeBlack > INTERVAL_TIME) {
				if (unit->getPositionY() > 135) {
					unit->setPosition(unit->getPosition() - sf::Vector2f{ 0.f, 65.f });
					prevTimeBlack = currTime;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currTime - prevTimeBlack > INTERVAL_TIME) {
				if (unit->getPositionY() < 380) {
					unit->setPosition(unit->getPosition() + sf::Vector2f{ 0.f, 65.f });
					prevTimeBlack = currTime;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currTime - prevTimeBlack > INTERVAL_TIME) {
				if (unit->getPositionX() > 90) {
					unit->setPosition(unit->getPosition() - sf::Vector2f{ 90.f, 0.f });
					prevTimeBlack = currTime;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currTime - prevTimeBlack > INTERVAL_TIME) {
				if (unit->getPositionX() < 820) {
					unit->setPosition(unit->getPosition() + sf::Vector2f{ 90.f, 0.f });
					prevTimeBlack = currTime;
				}
			}
		}
	}
}

void Game::playerUnit(sf::RenderWindow& window) {
	for (auto player : playerWhiteSprites)
		window.draw(player->getSprite());
	for (auto player : playerBlackSprites)
		window.draw(player->getSprite());
	for (auto unit : unitWhiteSprites)
		unit->draw(window);
	for (auto unit : unitBlackSprites)
		unit->draw(window);
}

void Game::allText(sf::RenderWindow& window) {
	text_player_go.draw(window);
	text_player_unit.draw(window);
}