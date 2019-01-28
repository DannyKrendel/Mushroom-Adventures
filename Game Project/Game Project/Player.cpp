#include "pch.h"
#include "Player.h"
#include "Item.h"
#include "Obstacle.h"
#include "Leaves.h"
#include <SFML/Audio.hpp>

Player::Player()
{
}

Player::Player(const Vector2f &size, const Vector2u &step, const Texture &texture, const Collider &col, const Stats &stats, const Vector2f &maxVelocity)
{
	this->texture = texture;
	this->step = step;
	this->collider = col;
	this->stats = stats;
	this->maxVelocity = maxVelocity;

	body.setSize(size);
	body.setTexture(&this->texture);
	setOrigin(Vector2f(body.getSize().x / 2.0f, body.getSize().y));

	reset(stats);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(body, states);
	target.draw(stats, states);
}

void Player::move(const Vector2f &offset)
{
	body.move(offset);
	collider.move(offset);
}

void Player::handeInput()
{
	if (!isAlive)
		return;

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		currentVelocity = Vector2f(-int(step.x), 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		currentVelocity = Vector2f(step.x, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		currentVelocity = Vector2f(0, -int(step.y));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		currentVelocity = Vector2f(0, step.y);
	}
	else
	{
		return;
	}

	currentVelocity.x *= maxVelocity.x;
	currentVelocity.y *= maxVelocity.y;
}

bool Player::checkWalls(const TileMap &tileMap, float deltaTime)
{
	for (auto &t : tileMap)
	{
		if (t.getType() == TileType::Border && t.getCollider().isCollidingWith(nextPosition))
			return true;
	}
	return false;
}

void Player::updateAnimation(float deltaTime)
{
	if (currentAnim)
	{
		currentAnim->update(deltaTime, faceRight);

		IntRect uvRect = currentAnim->uvRect;
		if (currentAnim == &idleAnim)
			uvRect.top = 0;
		else if (currentAnim == &jumpAnim)
			uvRect.top = uvRect.height;
		else if (currentAnim == &attackAnim)
			uvRect.top = uvRect.height * 2;
		else if (currentAnim == &hurtAnim)
			uvRect.top = uvRect.height * 3;
		else if (currentAnim == &deathAnim)
			uvRect.top = uvRect.height * 4;

		body.setTextureRect(uvRect);
	}
}

#pragma region Getters

const Stats & Player::getStats() const
{
	return stats;
}

const Collider & Player::getCollider() const
{
	return collider;
}

const Vector2f & Player::getPosition() const
{
	return body.getPosition();
}

#pragma endregion

#pragma region Setters

void Player::setPosition(const Vector2f &pos)
{
	body.setPosition(pos);
	collider.setPosition(pos);
}

void Player::setScale(const Vector2f &scale)
{
	body.setScale(scale);
	collider.setScale(scale);
}

void Player::setOrigin(const Vector2f &origin)
{
	body.setOrigin(origin);
	collider.setOrigin(origin);
}

#pragma endregion

void Player::calcNextPosition()
{
	nextPosition.x = getPosition().x + ((currentVelocity.x > 0) - (currentVelocity.x < 0)) * int(step.x);
	nextPosition.y = getPosition().y + ((currentVelocity.y > 0) - (currentVelocity.y < 0)) * int(step.y);
}

bool Player::isOnNextPosition()
{
	/*if (Vector2i(getPosition()) == Vector2i(nextPosition))
		return true;*/

	Vector2f diff(getPosition().x - nextPosition.x, getPosition().y - nextPosition.y);

	return (diff.x > 0) - (diff.x < 0) == (currentVelocity.x > 0) - (currentVelocity.x < 0) && (diff.y > 0) - (diff.y < 0) == (currentVelocity.y > 0) - (currentVelocity.y < 0);
}

void Player::update(TileMap &tileMap, float deltaTime)
{
	// если у персонажа нет здоровь€ - он умер
	if (stats.lives <= 0 && isAlive == true)
	{
		isAlive = false;
		currentAnim = &deathAnim.reset();
		deathSound.play();
	}

	// если персонаж жив и не двигаетс€
	if (isAlive && currentVelocity == Vector2f(0, 0))
	{
		// если текуща€ анимаци€ не прыжок
		if (currentAnim != &jumpAnim && currentAnim != &deathAnim)
		{
			// проверка нажатых клавиш
			handeInput();
		}

		// если скорость персонажа изменилась
		if (currentVelocity != Vector2f(0, 0))
		{
			// звук прыжка
			jumpSound.play();
			// вычисл€етс€ следующа€ позици€
			calcNextPosition();

			// если впереди стена
			if (checkWalls(tileMap, deltaTime))
			{
				// скорость обнул€етс€
				currentVelocity = Vector2f(0, 0);
			}
			else
			{
				// включаетс€ анимаци€ прыжка
				currentAnim = &jumpAnim.reset();
			}
		}
	}

	// врем€ неу€звимости после получени€ урона
	if (isAlive && hurtTime > 0)
	{
		if (hurtTime == invincibilityTime)
			currentAnim = &hurtAnim.reset();
		hurtTime -= deltaTime;
	}

	// ориентаци€ спрайта персонажа
	if (currentVelocity.x != 0)
	{
		faceRight = currentVelocity.x > 0;
	}

	// обновление анимации
	updateAnimation(deltaTime);

	// если друга€ анимаци€ закончилась, переключение на стандартную анимацию
	if (isAlive && currentAnim != &idleAnim && currentAnim->isFinished())
	{
		currentAnim = &idleAnim.reset();
	}

	// перемещение персонажа на следующий тайл
	move(currentVelocity * deltaTime);

	// если игрок уже на следующем тайле, прекратить движение
	if (isOnNextPosition())
	{
		setPosition(nextPosition);
		collider.setPosition(nextPosition);
		currentVelocity = Vector2f(0, 0);
	}

	// взаимодействие с тайлами
	interactionWithMap(tileMap, deltaTime);

	stats.update();
}

void Player::interactionWithMap(TileMap &tileMap, float deltaTime)
{
	if (isAlive == false)
		return;

	for (auto &tile : tileMap)
	{
		if (collider.isCollidingWith(tile.getCollider()))
		{
			TileType tileType = tile.getType();

			if (tileType == Water && isSlowedDown == false)
			{
				isSlowedDown = true;
				maxVelocity *= 0.5f;
				currentAnim->setDuration(currentAnim->getDuration() / 0.5f);
			}
			else if (tileType != Water && isSlowedDown == true)
			{
				isSlowedDown = false;
				maxVelocity /= 0.5f;
				currentAnim->setDuration(currentAnim->getDuration() * 0.5f);
			}
		}
	}
}

void Player::interactionWithItems(EntityManager<Item> &itemManager, float deltaTime)
{
	if (isAlive == false)
		return;

	for (auto &item : itemManager.getEntities())
	{
		const Item &newItem = *item.get();

		if (collider.isCollidingWith(newItem.getCollider()) && currentVelocity == Vector2f(0, 0))
		{
			switch (newItem.getType())
			{
			case Cherry:
				pickupSound.play();
				stats.berriesToFind -= 1;
				break;
			case Heart:
				lifeSound.play();
				stats.lives += 1;
				break;
			}

			itemManager.erase(item);

			break;
		}
	}
}

void Player::interactionWithObstacles(EntityManager<Obstacle> &obstacleManager, float deltaTime)
{
	if (isAlive == false)
		return;

	for (auto &obstacle : obstacleManager.getEntities())
	{
		const Obstacle &newObstacle = *obstacle.get();

		if (collider.isCollidingWith(newObstacle.getCollider()) && currentVelocity == Vector2f(0, 0))
		{
			switch (newObstacle.getType())
			{
			case Spikes:
				if (hurtTime <= 0)
				{
					stats.lives -= 1;
					hurtTime = invincibilityTime;
					hitSound.play();
				}
				break;
			}

			break;
		}
	}
}

void Player::interactionWithLeaves(EntityManager<Leaves> &leavesManager, float deltaTime)
{
	if (isAlive == false)
		return;

	for (auto &leaves : leavesManager.getEntities())
	{
		const Leaves &newLeaves = *leaves.get();

		if (collider.isCollidingWith(newLeaves.getCollider()))
		{
			leavesManager.erase(leaves);

			break;
		}
	}
}

void Player::reset(const Stats &stats)
{
	isAlive = true;
	faceRight = true;
	hurtTime = 0;
	currentVelocity = Vector2f();
	currentAnim = &idleAnim;

	this->stats = stats;
}
