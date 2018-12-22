#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Animation.h"
#include "Collider.h"
#include "Stats.h"

using namespace sf;

enum Orientation
{
	Horizontal, Vertical
};

class Player : public Collider
{
private:
	RectangleShape body;
	Vector2f velocity;
	Texture texture;
	Animation animation;
	size_t row;
	Orientation orientation;
	Stats stats;
	float speed;
	float actualSpeed;
	float invincibilityTime;
	float tempTime;

	void movement();
	void collision(Tile tile, float deltaTime);
public:
	virtual FloatRect getCollisionRect();
	Vector2f getPosition();
	float getHealth();
	int getScore();
	int getGold();
	int getMana();

	void setPosition(Vector2f pos);
	void setHealth(float health);
	void setScore(int score);
	void setGold(int gold);
	void setMana(int mana);

	bool isAlive;

	Player(Texture *texture, Animation animation, Stats stats, float speed = 100, float invincibilityTime = 2);

	void update(float deltaTime);
	void draw(RenderWindow &window, const View &view);
	void interactionWithMap(TileMap &tileMap, float deltaTime);
};

