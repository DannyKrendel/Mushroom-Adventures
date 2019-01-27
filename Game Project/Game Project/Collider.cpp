#include "pch.h"
#include "Collider.h"

Collider::Collider()
{
}

Collider::Collider(float left, float top, float width, float height)
{
	setPosition(Vector2f(left, top));
	setSize(Vector2f(width, height));
}

const FloatRect &Collider::getRect() const
{
	return FloatRect(getPosition(), getSize());
}

bool Collider::isCollidingWith(const Collider &other) const
{
	return getRect().intersects(other.getRect());
}

bool Collider::isCollidingWith(const Vector2f &point) const
{
	return getRect().contains(point);
}
