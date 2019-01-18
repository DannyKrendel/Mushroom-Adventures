#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

using namespace sf;

class TileMap : public std::vector<Tile>, public Drawable
{
private:
	// текстуры тайла
	Texture texture;
	// размеры карты
	Vector2u mapSize;
	// размеры тайла
	Vector2u tileSize;
	// масштаб тайла
	Vector2f tileScale;
	// коллайдер тайла
	Collider tileCollider;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	TileMap(const Image &level, const Texture &texture, const Vector2u &tileSize, const Collider &tileCol, const Vector2f &tileScale = Vector2f());

	const Vector2u & getMapSize() const;
	const Vector2u & getTileSize() const;
	const Vector2f & getPlayerSpawnPos(const Image &level) const;

	void spawnTiles(TileType tileType, size_t amount);
	bool find(Tile tile);
	bool find(Vector2f pos);
};