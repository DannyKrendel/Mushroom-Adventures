#include "pch.h"
#include "Leaves.h"

Leaves::Leaves()
{
}

Leaves::Leaves(const Texture &texture, const Vector2u &size, const Collider &col) : Entity(texture, size, col)
{
}