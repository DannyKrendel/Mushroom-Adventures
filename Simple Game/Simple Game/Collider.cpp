#include "pch.h"
#include "Collider.h"

Collider::Collider()
{
}

bool Collider::isCollidingWith(Collider *other)
{
	return getCollisionRect().intersects(other->getCollisionRect());
}
