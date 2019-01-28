#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Leaves : public Entity
{
public:
	Leaves();
	Leaves(const Texture &texture, const Vector2u &size, const Collider &col);
};