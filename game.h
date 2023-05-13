#pragma once
#include "settings.h"
#include "player.h"
#include <list>

class Game {
public:
	Game() {
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		Player* pw1 = new Player(PLAYER_FILE_NAME, sf::Vector2f{ 50,  60});
		playerWhiteSprites.push_back(pw1);
		Player* pb1 = new Player(PLAYER1_FILE_NAME, sf::Vector2f{ 500, 450});
		playerBlackSprites.push_back(pb1);
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
private:
	sf::RenderWindow window;
	sf::RectangleShape block[COL_LINE][COL_ROW];
	std::list<Player*> playerWhiteSprites;
	std::list<Player*> playerBlackSprites;
	int qtyWhite = 1, qtyBlack = 1;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void update() {
		land();
		for (auto player : playerWhiteSprites) {
			player->update();
		}
		for (auto player : playerBlackSprites) {
			player->update();
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