#pragma once
#include "settings.h"
#include "game_object.h"
#include "Text.h"

class Player : public GameObject
{
private:

public:
	Player()
	{
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2, bounds.height / 2);
	}

	void update(std::string name, sf::Vector2f pos)
	{
		texture.loadFromFile(name);
		sprite.setTexture(texture);
		sprite.setPosition(pos);
	}

	sf::Sprite getSprite() { return sprite; }
};