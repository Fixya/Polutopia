#pragma once
#include "settings.h"

class TextObj {
private:
	sf::Font font;
	sf::Text text;

public:
	TextObj(sf::Vector2f pos) {
		font.loadFromFile(FONT_FILE_NAME);
		text.setFont(font);
		text.setCharacterSize(FONT_SIZE);
		text.setPosition(pos);
	}

	void update(std::string str) { text.setString(str); }

	void draw(sf::RenderWindow& window) { window.draw(text); }

};