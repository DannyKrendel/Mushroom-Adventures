#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Collider
{
public:
	Collider();

	virtual FloatRect getCollisionRect() = 0;

	bool isCollidingWith(Collider *other);
};