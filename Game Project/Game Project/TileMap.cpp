#include "pch.h"
#include "TileMap.h"

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto &tile : *this)
	{
		target.draw(tile, states);
	}
}

TileMap::TileMap()
{
}

TileMap::TileMap(const Image &level, const Texture &texture, const Vector2u &tileSize, const Collider &tileCol, const Vector2f &tileScale)
{
	this->texture = texture;
	this->mapSize = level.getSize();
	this->tileSize = tileSize;
	this->tileCollider = tileCol;
	this->tileScale = tileScale;

	reset(level);
}

const Texture &TileMap::getTexture() const
{
	return texture;
}

const Vector2u &TileMap::getMapSize() const
{
	return mapSize;
}

const Vector2u &TileMap::getTileSize() const
{
	return Vector2u(tileSize.x * tileScale.x, tileSize.y * tileScale.y);
}

const Collider &TileMap::getTileCollider() const
{
	return tileCollider;
}

const Vector2f &TileMap::getPlayerSpawnPos() const
{
	return playerSpawnPos;
}

Tile *TileMap::find(const Tile &tile) 
{
	for (auto &t : *this)
	{
		if (t == tile)
			return &t;
	}
	return NULL;
}

Tile *TileMap::find(const Vector2f &pos)
{
	for (auto &t : *this)
	{
		if (t.getPosition() == pos)
			return &t;
	}
	return NULL;
}

void TileMap::reset(const Image& level)
{
	this->clear();
	for (size_t i = 0; i < mapSize.x; i++)
	{
		for (size_t j = 0; j < mapSize.y; j++)
		{
			Color pixelColor = level.getPixel(i, j);
			TileType tileType;

			if (pixelColor == Color::Black)
			{
				tileType = Border;
			}
			else if (pixelColor.g > 0 && pixelColor.r == 0 && pixelColor.b == 0)
			{
				tileType = Ground;
			}
			else if (pixelColor.b > 0 && pixelColor.r == 0 && pixelColor.g == 0)
			{
				tileType = Water;
			}
			else if (pixelColor == Color::White)
			{
				tileType = Ground;
				playerSpawnPos = Vector2f(i * tileSize.x, j * tileSize.y);
			}
			else
			{
				tileType = None;
			}

			Tile newTile(tileType, texture, tileSize, tileCollider);

			newTile.setPosition(Vector2f(i * tileSize.x * tileScale.x, j * tileSize.y * tileScale.y));
			newTile.setScale(tileScale);

			this->push_back(newTile);
		}
	}
}
