#include "pch.h"
#include "Tile.h"

Tile::Tile() : Entity()
{
}

Tile::Tile(const TileType &type, const Texture &texture, const Vector2u &size, const Collider &col) : Entity(texture, size, col)
{
	this->type = type;

	Vector2i offset(type * size.x, 0);
	sprite.setTextureRect(IntRect(offset, Vector2i(size)));
	setOrigin(Vector2f(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f));
}

TileType Tile::getType() const
{
	return type;
}

bool Tile::operator==(const Entity &rhs) const
{
	const Tile *tile = dynamic_cast<const Tile*>(&rhs);
	if (tile)
		return sprite.getPosition() == tile->sprite.getPosition() && type == tile->type;

	return false;
}