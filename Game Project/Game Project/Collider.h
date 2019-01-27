#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Collider : public RectangleShape
{
public:
	Collider();
	Collider(float left, float top, float width, float height);

	const FloatRect &getRect() const;

	bool isCollidingWith(const Collider &other) const;
	bool isCollidingWith(const Vector2f &point) const;
};