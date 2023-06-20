#pragma once
#include "settings.h"

class Units : public GameObject
{
public:
	enum UnitType { SWORDSMAN, SWORDSMAN1 };
	Units(UnitType type, sf::Vector2f position);
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
	case SWORDSMAN1:
		this->type = type;
		texture.loadFromFile(SWORDSMAN1_UNITS_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		break;
	}
}

bool Units::isToDel() { return del; }
void Units::setDel() { del = true; }