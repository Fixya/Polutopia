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
	int add = 0;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void update() {
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

	void checkCollisions() {}

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

void Game::unitWhiteUpdate(Player* player) {
	for (auto unit : unitWhiteSprites) {
		if (doru == 1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { unitWMade(0, player); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { unitWMade(1, player); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { unitWMade(2, player); }
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && add == 0) { unit->setPosition(unit->getPosition() - sf::Vector2f{ 0.f, 65.f }); add++; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && add == 0) { unit->setPosition(unit->getPosition() + sf::Vector2f{ 0.f, 65.f }); add++; }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { unit->setPosition(unit->getPosition() - sf::Vector2f{ 90.f, 0.f }); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { unit->setPosition(unit->getPosition() + sf::Vector2f{ 90.f, 0.f }); }
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { unit->setPosition(unit->getPosition() - sf::Vector2f{ 0.f, 65.f }); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { unit->setPosition(unit->getPosition() + sf::Vector2f{ 0.f, 65.f }); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { unit->setPosition(unit->getPosition() - sf::Vector2f{ 90.f, 0.f }); }
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { unit->setPosition(unit->getPosition() + sf::Vector2f{ 90.f, 0.f }); }
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