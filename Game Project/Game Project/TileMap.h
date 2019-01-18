#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

using namespace sf;

class TileMap : public std::vector<Tile>, public Drawable
{
private:
	// �������� �����
	Texture texture;
	// ������� �����
	Vector2u mapSize;
	// ������� �����
	Vector2u tileSize;
	// ������� �����
	Vector2f tileScale;
	// ��������� �����
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