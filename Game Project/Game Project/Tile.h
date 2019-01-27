#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace sf;

enum TileType
{
	Ground, Border, Water, None
};

struct Tile : public Entity
{
private:
	TileType type;
public:
	Tile();
	Tile(const TileType &type, const Texture &texture, const Vector2u &size, const Collider &col);

	TileType getType() const;

	bool operator==(const Entity &rhs) const;
};