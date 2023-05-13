#pragma once
#include <iostream>
#include "settings.h"

class GameObject
{
public:
	GameObject();
	virtual void update() = 0;
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
protected:
	sf::Sprite sprite;
	sf::Texture texture;
};