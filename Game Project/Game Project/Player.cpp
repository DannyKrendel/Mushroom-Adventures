#include "pch.h"
#include "Player.h"

Player::Player(const Vector2f &size, const Vector2u &step, Texture texture, Collider col, Stats stats, const Vector2f &maxVelocity)
{
	isAlive = true;
	faceRight = true;
	this->texture = texture;
	this->step = step;
	this->collider = col;
	this->stats = stats;
	this->maxVelocity = maxVelocity;

	body.setSize(size);
	body.setTexture(&this->texture);
	setOrigin(Vector2f(body.getSize().x / 2.0f, body.getSize().y));
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
		if (t.getTileType() == TileType::Border && t.getCollider().isCollidingWith(nextPosition))
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

void Player::update(TileMap &tileMap, float deltaTime)
{
	// если у персонажа нет здоровь€ - он умер
	if (stats.health <= 0)
		isAlive = false;

	// если персонаж не двигаетс€ и не в прыжке
	if (currentVelocity == Vector2f(0, 0) && currentAnim != &jumpAnim)
	{
		// включаетс€ стандартна€ анимаци€
		currentAnim = &idleAnim;

		// проверка нажатых клавиш
		handeInput();

		// если скорость персонажа изменилась
		if (currentVelocity != Vector2f(0, 0))
		{
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
	if (hurtTime > 0)
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

	// если анимаци€ прыжка закончилась, переключение на стандартную анимацию
	if (currentAnim == &jumpAnim && currentAnim->isFinished())
	{
		currentAnim = &idleAnim.reset();
	}

	// перемещение персонажа на следующий тайл
	move(currentVelocity * deltaTime);

	// если игрок уже на следующем тайле, прекратить движение
	if (Vector2i(getPosition()) == Vector2i(nextPosition))
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
	for (auto &tile : tileMap)
	{
		if (collider.isCollidingWith(tile.getCollider()))
		{
			TileType tileType = tile.getTileType();

			switch (tileType)
			{
			case Spores:
				stats.score += 1;
				break;
			case Health:
				stats.health += 1;
				break;
			case None:
				return;
			}

			if (tileType == Water && isSlowedDown == false)
			{
				isSlowedDown = true;
				maxVelocity *= 0.5f;
			}
			else if (tileType != Water && isSlowedDown == true)
			{
				isSlowedDown = false;
				maxVelocity /= 0.5f;
			}

			if (hurtTime <= 0 && tileType == Spikes)
			{
				stats.health -= 20;
				hurtTime = invincibilityTime;
			}

			if (tileType == Spores || tileType == Health)
			{
				int idx = std::find(tileMap.begin(), tileMap.end(), tile) - tileMap.begin();
				tileMap.erase(tileMap.begin() + idx);
			}
		}
	}
}