#include "pch.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(TileType type, Texture *texture, Vector2u size, Vector2f pos)
{
	Vector2i offset(type * size.x, 0);

	Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setTextureRect(IntRect(offset, Vector2i(size)));
	sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
	sprite.setPosition(pos);

	this->tileType = type;
	this->sprite = sprite;
}

FloatRect Tile::getCollisionRect()
{
	return FloatRect(getPosition().x - sprite.getTextureRect().width / 2, getPosition().y - sprite.getTextureRect().height / 2, 
		sprite.getTextureRect().width, sprite.getTextureRect().height);
}

void Tile::setPosition(Vector2f pos)
{
	sprite.setPosition(pos);
}

Vector2f Tile::getPosition()
{
	return sprite.getPosition();
}

TileType Tile::getTileType()
{
	return tileType;
}

void Tile::draw(RenderWindow &window)
{
	window.draw(sprite);
}

bool Tile::operator==(const Tile & rhs)
{
	return sprite.getPosition() == rhs.sprite.getPosition() && tileType == rhs.tileType;
}

bool Tile::operator!=(const Tile & rhs)
{
	return !(*this == rhs);
}