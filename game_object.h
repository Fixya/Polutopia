#pragma once
#include <iostream>
#include "settings.h"

class GameObject
{
public:
	sf::Vector2f getPosition() { return sprite.getPosition(); }
	float getPositionY() { return sprite.getPosition().y; }
	float getPositionX() { return sprite.getPosition().x; }
	void setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	sf::Sprite getSprite() { return sprite; }
	void draw(sf::RenderWindow& window) { window.draw(sprite); }
protected:
	sf::Sprite sprite;
	sf::Texture texture;
};