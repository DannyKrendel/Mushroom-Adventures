#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

using namespace sf;

class TileMap : public std::vector<Tile>
{
private:
	// texture map
	Texture texture;
	// size of map
	Vector2u mapSize;
	// size of a tile
	Vector2u tileSize;
public:
	TileMap(Texture *texture, Vector2u mapSize, Vector2u tileSize);

	Vector2u getMapSize();
	Vector2u getTileSize();

	void spawnTiles(TileType tileType, size_t amount);
	bool find(Tile tile);
	bool find(Vector2f pos);
	void draw(RenderWindow &window);
};