#pragma once
#include "settings.h"

class Ban_mark : public GameObject
{
public:
	Ban_mark(sf::Vector2f position) {
		texture.loadFromFile(BAN_MARK_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(position);
	}
	bool isToDel() { return del; }
	void setDel() { del = true; }

private:
	bool del = false;
};