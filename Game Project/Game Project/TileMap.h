#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

using namespace sf;

class TileMap : public std::vector<Tile>, public Drawable
{
private:
	Texture texture;
	Vector2u mapSize;
	Vector2u tileSize;
	Vector2f tileScale;
	Collider tileCollider;

	Vector2f playerSpawnPos;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	TileMap();
	TileMap(const Image &level, const Texture &texture, const Vector2u &tileSize, const Collider &tileCol, const Vector2f &tileScale = Vector2f(1.0f, 1.0f));

	const Texture &getTexture() const;
	const Vector2u &getMapSize() const;
	const Vector2u &getTileSize() const;
	const Collider &getTileCollider() const;
	const Vector2f &getPlayerSpawnPos() const;

	Tile *find(const Tile &tile);
	Tile *find(const Vector2f &pos);

	void reset(const Image& level);
};