#include "pch.h"
#include "Obstacle.h"

Obstacle::Obstacle()
{

}

Obstacle::Obstacle(const ObstacleType &type, const Texture &texture, const Vector2u &size, const Collider &col) : Entity(texture, size, col)
{
	this->type = type;

	Vector2i offset(type * size.x, 0);
	sprite.setTextureRect(IntRect(offset, Vector2i(size)));
	setOrigin(Vector2f(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f));
}

ObstacleType Obstacle::getType() const
{
	return type;
}

bool Obstacle::operator==(const Entity &rhs) const
{
	const Obstacle *obstacle = dynamic_cast<const Obstacle*>(&rhs);
	if (obstacle)
		return sprite.getPosition() == obstacle->sprite.getPosition() && type == obstacle->type;

	return false;
}