#include "pch.h"
#include "TileMap.h"

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto &tile : *this)
	{
		target.draw(tile, states);
	}
}

TileMap::TileMap(const Image &level, const Texture &texture, const Vector2u &tileSize, const Collider &tileCol, const Vector2f &tileScale)
{
	this->texture = texture;
	this->mapSize = level.getSize();
	this->tileSize = tileSize;
	this->tileCollider = tileCol;
	this->tileScale = tileScale;

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

			Tile newTile = Tile(tileType, &this->texture, tileSize, tileCol);

			newTile.setPosition(Vector2f(i * tileSize.x * tileScale.x, j * tileSize.y * tileScale.y));
			newTile.setScale(tileScale);

			this->push_back(newTile);
		}
	}
}

const Vector2u & TileMap::getMapSize() const
{
	return mapSize;
}

const Vector2u & TileMap::getTileSize() const
{
	return Vector2u(tileSize.x * tileScale.x, tileSize.y * tileScale.y);
}

const Vector2f &TileMap::getPlayerSpawnPos(const Image &level) const
{
	for (size_t i = 0; i < level.getSize().x; i++)
	{
		for (size_t j = 0; j < level.getSize().y; j++)
		{
			if (level.getPixel(i, j) == Color::White)
				return Vector2f(i * tileSize.x, j * tileSize.y);
		}
	}
	return Vector2f();
}

void TileMap::spawnTiles(TileType tileType, size_t amount)
{
	srand(time(0));

	Vector2f randomPos;

	while (amount > 0)
	{
		do
		{
			randomPos.x = (1 + rand() % (mapSize.x - 2)) * tileSize.x * tileScale.x;
			randomPos.y = (1 + rand() % (mapSize.y - 2)) * tileSize.y * tileScale.y;
		} while (find(randomPos));

		Tile newTile(tileType, &texture, tileSize, tileCollider);
		newTile.setPosition(randomPos);
		newTile.setScale(tileScale);

		this->push_back(newTile);

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