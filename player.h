#pragma once
#include "settings.h"
#include "game_object.h"

class Player : public GameObject
{
public:
	Player(std::string player_file_name, sf::Vector2f pos) {
		texture.loadFromFile(player_file_name);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
		sprite.setPosition(pos);
	}

	void update() {}
private:

};