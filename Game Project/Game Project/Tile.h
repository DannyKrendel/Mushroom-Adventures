#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

using namespace sf;

enum TileType
{
	Ground, Border, Water, Spores, Spikes, Health, None
};

struct Tile : public Drawable
{
private:
	Sprite sprite;
	TileType tileType;
	Collider collider;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Tile();
	Tile(TileType type, Texture *texture, Vector2u size, Collider col);

	void setPosition(const Vector2f &pos);
	void setScale(const Vector2f &scale);
	void setOrigin(const Vector2f &origin);

	const Vector2f & getPosition() const;
	const Collider & getCollider() const;
	TileType getTileType() const;

	bool operator==(const Tile &rhs);
	bool operator!=(const Tile &rhs);
};

