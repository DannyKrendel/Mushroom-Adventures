#include "pch.h"
#include "Entity.h"

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Entity::Entity()
{
}

Entity::Entity(const Texture &texture, const Vector2u &size, const Collider &col)
{
	this->collider = col;
	this->sprite.setTexture(texture);
}

const Sprite &Entity::getSprite() const
{
	return sprite;
}

const Collider &Entity::getCollider() const
{
	return collider;
}

const Vector2f &Entity::getPosition() const
{
	return sprite.getPosition();
}

float Entity::getRotation() const
{
	return sprite.getRotation();
}

const Color &Entity::getColor() const
{
	return sprite.getColor();
}

void Entity::setPosition(const Vector2f &pos)
{
	sprite.setPosition(pos);
	collider.setPosition(pos);
}

void Entity::setScale(const Vector2f &scale)
{
	sprite.setScale(scale);
	collider.setScale(scale);
}

void Entity::setOrigin(const Vector2f &origin)
{
	sprite.setOrigin(origin);
	collider.setOrigin(origin);
}

void Entity::setRotation(float angle)
{
	sprite.setRotation(angle);
}

void Entity::setColor(const Color &color)
{
	sprite.setColor(color);
}

bool Entity::operator==(const Entity &rhs) const
{
	return sprite.getPosition() == rhs.sprite.getPosition();
}

bool Entity::operator!=(const Entity &rhs) const
{
	return !(*this == rhs);
}
