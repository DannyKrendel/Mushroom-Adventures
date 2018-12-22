#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

using namespace sf;

enum TileType
{
	Ground, Border, Rock, Spikes, Health, Mana, Gold, Water, Lava, 
	None
};

struct Tile : public Collider
{
private:
	Sprite sprite;
	TileType tileType;
public:
	Tile();
	Tile(TileType type, Texture *texture, Vector2u size, Vector2f pos = Vector2f());

	virtual FloatRect getCollisionRect();
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	TileType getTileType();

	void draw(RenderWindow &window);

	bool operator==(const Tile &rhs);
	bool operator!=(const Tile &rhs);
};

