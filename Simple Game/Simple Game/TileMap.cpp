#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(Texture *texture, Vector2u mapSize, Vector2u tileSize)
{
	this->texture = *texture;
	this->mapSize = mapSize;
	this->tileSize = tileSize;

	for (size_t i = 0; i < mapSize.x; i++)
	{
		for (size_t j = 0; j < mapSize.y; j++)
		{
			Tile newTile;
			if (i == 0 || i == mapSize.x - 1 || j == 0 || j == mapSize.y - 1)
				newTile = Tile(TileType::Border, texture, tileSize, Vector2f(i * tileSize.x, j * tileSize.y));
			else
				newTile = Tile(TileType::Ground, texture, tileSize, Vector2f(i * tileSize.x, j * tileSize.y));

			this->push_back(newTile);
		}
	}
}

Vector2u TileMap::getMapSize()
{
	return mapSize;
}

Vector2u TileMap::getTileSize()
{
	return tileSize;
}

void TileMap::spawnTiles(TileType tileType, size_t amount)
{
	srand(time(0));

	Vector2f randomPos;

	while (amount > 0)
	{
		do
		{
			randomPos.x = (1 + rand() % (mapSize.x - 2)) * tileSize.x;
			randomPos.y = (1 + rand() % (mapSize.y - 2)) * tileSize.y;
		} while (find(randomPos));

		this->push_back(Tile(tileType, &texture, tileSize, randomPos));

		amount--;
	}
}

bool TileMap::find(Tile tile)
{
	for (auto &t : *this)
	{
		if (t == tile)
			return true;
	}
	return false;
}

bool TileMap::find(Vector2f pos)
{
	for (auto &t : *this)
	{
		if (t.getTileType() != Ground && t.getPosition() == pos)
			return true;
	}
	return false;
}

void TileMap::draw(RenderWindow &window)
{
	for (auto &tile : *this)
	{
		tile.draw(window);
	}
}
