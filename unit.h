#pragma once
#include "settings.h"

class Units : public GameObject
{
public:
	enum UnitType { SWORDSMAN, ARCHER, BUILDER, UNITS_TYPE_QTY };
	Units(UnitType type, sf::Vector2f position);
	void draw(sf::RenderWindow& window);
private:
	UnitType type;
};
Units::Units(UnitType type, sf::Vector2f position)
{
	switch (type)
	{
	case SWORDSMAN:
		this->type = type;
		texture.loadFromFile(SWORDSMAN_UNITS_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		break;
	case ARCHER:
		this->type = type;
		texture.loadFromFile(ARCHER_UNITS_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		break;
	case BUILDER:
		this->type = type;
		texture.loadFromFile(BUILDER_UNITS_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		break;
	}
}

void Units::draw(sf::RenderWindow& window) { window.draw(sprite); }

//void Bonus::update() { sprite.move(0.f, UNITS_SPEED); }
/*void Units::act()
{
	switch (type)
	{
	case SWORDSMAN:
		
		break;
	case ARCHER:
		
		break;
	case BUILDER:
		
		break;
	}
}*/

/*
void Player::activateSwordman() { swordman = SWORDSMAN_MARGIN; }
void Player::activateArcher() { archer = ARCHER_MARGIN; }
void Player::activateBuilder() { builder = BUILDER_MARGIN; }
void Player::decreaseSwordmanMargin() { swordmanMargin--; }
void Player::decreaseArcherMargin() { archerMargin--; }
void Player::decreaseBuilderMargin() { shieldMargin--; }*/