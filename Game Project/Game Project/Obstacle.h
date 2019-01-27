#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

using namespace sf;

enum ObstacleType
{
	Spikes
};

class Obstacle : public Entity
{
private:
	ObstacleType type;
public:
	Obstacle();
	Obstacle(const ObstacleType &type, const Texture &texture, const Vector2u &size, const Collider &col);

	ObstacleType getType() const;

	bool operator==(const Entity &rhs) const;
};

