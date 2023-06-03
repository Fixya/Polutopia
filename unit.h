#pragma once
#include "settings.h"

class Units : public GameObject
{
public:
	enum UnitType { SWORDSMAN, ARCHER, BUILDER, SWORDSMAN1, ARCHER1, BUILDER1 };
	Units(UnitType type, sf::Vector2f position);
	void draw(sf::RenderWindow& window);
	bool isToDel();
	void setDel();
private:
	UnitType type;
	bool del = false;
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
	case SWORDSMAN1:
		this->type = type;
		texture.loadFromFile(SWORDSMAN1_UNITS_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		break;
	case ARCHER1:
		this->type = type;
		texture.loadFromFile(ARCHER1_UNITS_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		break;
	case BUILDER1:
		this->type = type;
		texture.loadFromFile(BUILDER1_UNITS_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		break;
	}
}

void Units::draw(sf::RenderWindow& window) { window.draw(sprite); }

bool Units::isToDel() { return del; }
void Units::setDel() { del = true; }