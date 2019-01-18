#include "pch.h"
#include "Tile.h"

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Tile::Tile()
{
}

Tile::Tile(TileType type, Texture *texture, Vector2u size, Collider col)
{
	Vector2i offset(type * size.x, 0);

	this->tileType = type;
	this->collider = col;

	sprite.setTexture(*texture);
	sprite.setTextureRect(IntRect(offset, Vector2i(size)));
	setOrigin(Vector2f(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f));
}

void Tile::setPosition(const Vector2f &pos)
{
	sprite.setPosition(pos);
	collider.setPosition(pos);
}

void Tile::setScale(const Vector2f &scale)
{
	sprite.setScale(scale);
	collider.setScale(scale);
}

void Tile::setOrigin(const Vector2f &origin)
{
	sprite.setOrigin(origin);
	collider.setOrigin(origin);
}

const Vector2f & Tile::getPosition() const
{
	return sprite.getPosition();
}

const Collider & Tile::getCollider() const
{
	return collider;
}

TileType Tile::getTileType() const
{
	return tileType;
}

bool Tile::operator==(const Tile & rhs)
{
	return sprite.getPosition() == rhs.sprite.getPosition() && tileType == rhs.tileType;
}

bool Tile::operator!=(const Tile & rhs)
{
	return !(*this == rhs);
}