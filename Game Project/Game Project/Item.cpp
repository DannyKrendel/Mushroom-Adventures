#include "pch.h"
#include "Item.h"

Item::Item()
{
}

Item::Item(const ItemType &type, const Texture &texture, const Vector2u &size, const Collider &col) : Entity(texture, size, col)
{
	this->type = type;

	Vector2i offset(type * size.x, 0);
	sprite.setTextureRect(IntRect(offset, Vector2i(size)));
	setOrigin(Vector2f(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f));
}

ItemType Item::getType() const
{
	return type;
}

bool Item::operator==(const Entity &rhs) const
{
	const Item *item = dynamic_cast<const Item*>(&rhs);
	if (item)
		return sprite.getPosition() == item->sprite.getPosition() && type == item->type;

	return false;
}