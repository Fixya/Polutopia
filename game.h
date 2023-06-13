#pragma once
#include "settings.h"
#include "player.h"
#include <list>
#include "unit.h"
#include "Text.h"
#include "mark.h"
#include "ban_mark.h"


class Game {
public:
	Game() : text_player_go("Player 1", sf::Vector2f{ 0.f, 0.f }), text_player_unit("walking units", sf::Vector2f{ 175.f, 0.f }),
		text_for_ban("u can do", sf::Vector2f{ 20.f, 460.f })
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
		Ban_mark* bu1 = new Ban_mark(sf::Vector2f{ 175.f, 65.f });
		banMark.push_back(bu1);
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
	void banUnits(Units* unit);
	void playerWhiteUpdate(Player* player);
	void playerBlackUpdate(Player* player);
	void unitWhiteUpdate(Units* unitW);
	void unitBlackUpdate(Units* unitB, Player* player);
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
	int turn, alternate, permission;
	TextObj text_player_go, text_player_unit;
	//TextObj text_point;
	TextObj text_for_ban;
	Mark mark;
	std::list<Ban_mark*> banMark;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && turn == 0) { 
			turn = 1;
			for (auto banMarks : banMark) {
				banMarks->setDel();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && turn == 1) {
			turn = 0;
			for (auto banMarks : banMark) {
				banMarks->setDel();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			alternate = 0;
			text_player_unit.update("walking units");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			alternate = 1;
			text_player_unit.update("Creation of units");
		}
		if (turn == 0) {
			for (auto player : playerWhiteSprites) {
				player->update();
				text_player_go.update("Player 1");
			}
		}
		if (turn == 1) {
			for (auto player : playerBlackSprites) {
				player->update();
				text_player_go.update("Player 2");
			}
		}
		text_for_ban.update("u can do");
		mark.update(currTime);
	}

	void checkCollisions() {
		sf::FloatRect markHitBox = mark.getHitBox();
		for (auto banMarks : banMark) {
			sf::FloatRect banMarkHitBox = banMarks->getHitBox();
			if (markHitBox.intersects(banMarkHitBox)) {
				text_for_ban.update("u can't do");
			}
			else {
				for (auto playerW : playerWhiteSprites) {
					sf::FloatRect playerWhiteHitBox = playerW->getHitBox();
					if (markHitBox.intersects(playerWhiteHitBox) && turn == 0) {
						playerWhiteUpdate(playerW);
					}
					for (auto playerB : playerBlackSprites) {
						sf::FloatRect playerBlackHitBox = playerB->getHitBox();
						if (markHitBox.intersects(playerBlackHitBox) && turn == 0) {
							playerBlackUpdate(playerB);
						}
						for (auto unitW : unitWhiteSprites) {
							sf::FloatRect unitWhiteHitBox = unitW->getHitBox();
							for (auto unitB : unitBlackSprites) {
								sf::FloatRect unitBlackHitBox = unitB->getHitBox();
								if (unitWhiteHitBox.intersects(unitBlackHitBox)) {
									if (turn == 0) { unitB->setDel(); }
									if (turn == 1) { unitW->setDel(); }
								}
								if (markHitBox.intersects(unitBlackHitBox) && turn == 1) {
									unitBlackUpdate(unitB, playerB);
								}
							}
							if (markHitBox.intersects(unitWhiteHitBox) && turn == 0) {
								unitWhiteUpdate(unitW);
							}
						}
					}
				}
			}
		}
		unitWhiteSprites.remove_if([](Units* unitW) {return unitW->isToDel(); });
		unitBlackSprites.remove_if([](Units* unitB) {return unitB->isToDel(); });
		banMark.remove_if([](Ban_mark* banMarks) {return banMarks->isToDel(); });
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

void Game::banUnits(Units* unit) {
	Ban_mark* bu2 = new Ban_mark(unit->getPosition() + sf::Vector2f{ 5.f, -10.f });
	banMark.push_back(bu2);
}

void Game::playerWhiteUpdate(Player* player) {
	if (alternate == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { unitWMade(0, player); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { unitWMade(1, player); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { unitWMade(2, player); }
	}
}

void Game::playerBlackUpdate(Player* player) {
	if (alternate == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { unitBMade(3, player); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { unitBMade(4, player); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { unitBMade(5, player); }
	}
}

void Game::unitWhiteUpdate(Units* unitW) {
	if (alternate == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currTime - prevTimeWhite > INTERVAL_TIME) {
			if (unitW->getPositionY() > 135) {
				unitW->setPosition(unitW->getPosition() - sf::Vector2f{ 0.f, 65.f });
				prevTimeWhite = currTime;
				banUnits(unitW);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currTime - prevTimeWhite > INTERVAL_TIME) {
			if (unitW->getPositionY() < 380) {
				unitW->setPosition(unitW->getPosition() + sf::Vector2f{ 0.f, 65.f });
				prevTimeWhite = currTime;
				banUnits(unitW);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currTime - prevTimeWhite > INTERVAL_TIME) {
			if (unitW->getPositionX() > 90) {
				unitW->setPosition(unitW->getPosition() - sf::Vector2f{ 90.f, 0.f });
				prevTimeWhite = currTime;
				banUnits(unitW);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currTime - prevTimeWhite > INTERVAL_TIME) {
			if (unitW->getPositionX() < 920) {
				unitW->setPosition(unitW->getPosition() + sf::Vector2f{ 90.f, 0.f });
				prevTimeWhite = currTime;
				banUnits(unitW);
			}
		}
	}
}

void Game::unitBlackUpdate(Units* unitB, Player* player) {
	if (alternate == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && currTime - prevTimeBlack > INTERVAL_TIME) {
			if (unitB->getPositionY() > 135) {
				unitB->setPosition(unitB->getPosition() - sf::Vector2f{ 0.f, 65.f });
				prevTimeBlack = currTime;
				banUnits(unitB);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && currTime - prevTimeBlack > INTERVAL_TIME) {
			if (unitB->getPositionY() < 380) {
				unitB->setPosition(unitB->getPosition() + sf::Vector2f{ 0.f, 65.f });
				prevTimeBlack = currTime;
				banUnits(unitB);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && currTime - prevTimeBlack > INTERVAL_TIME) {
			if (unitB->getPositionX() > 90) {
				unitB->setPosition(unitB->getPosition() - sf::Vector2f{ 90.f, 0.f });
				prevTimeBlack = currTime;
				banUnits(unitB);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && currTime - prevTimeBlack > INTERVAL_TIME) {
			if (unitB->getPositionX() < 820) {
				unitB->setPosition(unitB->getPosition() + sf::Vector2f{ 90.f, 0.f });
				prevTimeBlack = currTime;
				banUnits(unitB);
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
	for (auto banMarks : banMark)
		banMarks->draw(window);
	mark.draw(window);
}

void Game::allText(sf::RenderWindow& window) {
	text_player_go.draw(window);
	text_player_unit.draw(window);
	text_for_ban.draw(window);
}