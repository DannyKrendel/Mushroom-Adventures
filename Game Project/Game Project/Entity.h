#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Entity : public Drawable
{
protected:
	Sprite sprite;
	Collider collider;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Entity();
	Entity(const Texture &texture, const Vector2u &size, const Collider &col);

	const Sprite &getSprite() const;
	const Collider &getCollider() const;
	const Vector2f &getPosition() const;
	float getRotation() const;
	const Color &getColor() const;

	void setPosition(const Vector2f &pos);
	void setScale(const Vector2f &scale);
	void setOrigin(const Vector2f &origin);
	void setRotation(float angle);
	void setColor(const Color &color);

	virtual bool operator==(const Entity &rhs) const;
	virtual bool operator!=(const Entity &rhs) const;
};

