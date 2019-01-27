#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace sf;

enum ItemType
{
	Cherry, Heart
};

class Item : public Entity
{
private:
	ItemType type;
public:
	Item();
	Item(const ItemType &type, const Texture &texture, const Vector2u &size, const Collider &col);

	ItemType getType() const;

	bool operator==(const Entity &rhs) const;
};