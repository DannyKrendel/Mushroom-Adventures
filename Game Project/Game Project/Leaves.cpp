#include "pch.h"
#include "Leaves.h"

Leaves::Leaves()
{
}

Leaves::Leaves(const Texture &texture, const Vector2u &size, const Collider &col) : Entity(texture, size, col)
{
}

bool Leaves::operator==(const Entity &rhs) const
{
	const Leaves *leaves = dynamic_cast<const Leaves*>(&rhs);
	if (leaves)
		return sprite.getPosition() == leaves->sprite.getPosition();

	return false;
}