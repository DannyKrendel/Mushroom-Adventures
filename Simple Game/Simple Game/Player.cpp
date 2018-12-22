#include "pch.h"
#include "Player.h"

Player::Player(Texture *texture, Animation animation, Stats stats, float speed, float invincibilityTime) :
	animation(animation), stats(stats)
{
	isAlive = true;
	this->texture = *texture;
	this->speed = speed;
	this->invincibilityTime = invincibilityTime;
	this->actualSpeed = speed;

	body.setSize(Vector2f(animation.uvRect.width, animation.uvRect.height));
	body.setTexture(texture);
	body.setOrigin(body.getSize() / 2.0f);
}

void Player::movement()
{
	if (!isAlive)
		return;

	velocity = Vector2f(0, 0);

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		velocity = Vector2f(-1, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		velocity = Vector2f(1, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		velocity = Vector2f(0, -1);
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		velocity = Vector2f(0, 1);
	}
}

void Player::collision(Tile tile, float deltaTime)
{
	body.move(-velocity * speed * deltaTime);
}

FloatRect Player::getCollisionRect()
{
	switch (orientation)
	{
	case Horizontal:
		return FloatRect(body.getGlobalBounds().left, body.getGlobalBounds().top + 32, body.getSize().x, body.getSize().y - 64);
	case Vertical:
		return FloatRect(body.getGlobalBounds().left + 32, body.getGlobalBounds().top, body.getSize().x - 64, body.getSize().y);
	}
	
	//return FloatRect(body.getGlobalBounds().left, body.getGlobalBounds().top, body.getSize().x, body.getSize().y);
}

float Player::getHealth()
{
	return stats.health;
}

Vector2f Player::getPosition()
{
	return body.getPosition();
}

int Player::getScore()
{
	return stats.score;
}

int Player::getGold()
{
	return stats.gold;
}

int Player::getMana()
{
	return stats.mana;
}

void Player::setPosition(Vector2f pos)
{
	body.setPosition(pos);
}

void Player::setHealth(float health)
{
	this->stats.health = health;
}

void Player::setScore(int score)
{
	this->stats.score = score;
}

void Player::setGold(int gold)
{
	this->stats.gold = gold;
}

void Player::setMana(int mana)
{
	this->stats.mana = mana;
}

void Player::update(float deltaTime)
{
	if (getHealth() <= 0)
		isAlive = false;

	movement();

	if (velocity.y > 0)
	{
		row = 0;
		orientation = Vertical;
	}
	if (velocity.y < 0)
	{
		row = 3;
		orientation = Vertical;
	}
	if (velocity.x > 0)
	{
		row = 2;
		orientation = Horizontal;
	}
	if (velocity.x < 0)
	{
		row = 1;
		orientation = Horizontal;
	}

	if (velocity.x != 0 || velocity.y != 0)
		animation.update(row, deltaTime);

	body.setTextureRect(animation.uvRect);
	body.move(velocity * speed * deltaTime);

	if (tempTime > 0)
		tempTime -= deltaTime;
}

void Player::draw(RenderWindow &window, const View &view)
{
	stats.draw(window, view);
	if (tempTime > 0)
	{
		if (static_cast<int>(tempTime * 10) % 2 == 0)
			window.draw(body);
	}
	else
		window.draw(body);
}

void Player::interactionWithMap(TileMap &tileMap, float deltaTime)
{
	for (size_t i = 0; i < tileMap.size(); i++)
	{
		if (isCollidingWith(&tileMap[i]))
		{
			TileType tileType = tileMap[i].getTileType();

			switch (tileType)
			{
			case Border:
				collision(tileMap[i], deltaTime);
				break;
			case Rock:
				setScore(getScore() + 1);
				break;
			case Health:
				setHealth(getHealth() + 20);
				break;
			case Mana:
				setMana(getMana() + 1);
				break;
			case Gold:
				setGold(getGold() + 1);
				break;
			case None:
				return;
			}

			if (tileType == Water)
			{
				speed = actualSpeed * 0.5;
			}
			else
			{
				speed = actualSpeed;
			}

			if (tempTime <= 0 && (tileType == Spikes || tileType == Lava))
			{
				setHealth(getHealth() - 20);
				tempTime = invincibilityTime;
			}

			if (tileType == Rock || tileType == Health || tileType == Mana || tileType == Gold)
				tileMap.erase(tileMap.begin() + i);
		}
	}
}