#pragma once
#include "settings.h"
#include "game_object.h"

class Mark : public GameObject
{
public:
	Mark() {
		texture.loadFromFile(MARK_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f{ 175.f, 65.f });
	}

	void update(int currTime) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && currTime - prevTimeMark > MARK_INTERVAL_TIME) {
			setPosition(getPosition() + sf::Vector2f{ 0.f, BLOCK_HEIGHT + 5 });
			prevTimeMark = currTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && currTime - prevTimeMark > MARK_INTERVAL_TIME) {
			setPosition(getPosition() - sf::Vector2f{ 0.f, BLOCK_HEIGHT + 5 });
			prevTimeMark = currTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && currTime - prevTimeMark > MARK_INTERVAL_TIME) {
			setPosition(getPosition() + sf::Vector2f{ BLOCK_WIDTH + 5, 0.f });
			prevTimeMark = currTime;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && currTime - prevTimeMark > MARK_INTERVAL_TIME) {
			setPosition(getPosition() - sf::Vector2f{ BLOCK_WIDTH + 5, 0.f });
			prevTimeMark = currTime;
		}
	}

private:
	int prevTimeMark;
};