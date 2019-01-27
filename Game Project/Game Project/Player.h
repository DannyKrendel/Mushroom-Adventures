#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.h"
#include "Animation.h"
#include "Collider.h"
#include "Stats.h"
#include "EntityManager.h"
#include "Item.h"
#include "Obstacle.h"
#include "Leaves.h"

using namespace sf;

class Player : public Drawable
{
private:
	Texture texture;
	RectangleShape body;
	Collider collider;
	Vector2f currentVelocity;
	Vector2f maxVelocity;
	Stats stats;
	Animation *currentAnim;
	Vector2u step;
	Vector2f nextPosition;
	float invincibilityTime = 2;
	float hurtTime;
	bool isSlowedDown;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void move(const Vector2f &offset);
	void handeInput();
	bool checkWalls(const TileMap &tileMap, float deltaTime);
	void updateAnimation(float deltaTime);
	void calcNextPosition();
	bool isOnNextPosition();
public:
	Animation idleAnim;
	Animation jumpAnim;
	Animation attackAnim;
	Animation hurtAnim;
	Animation deathAnim;

	Sound jumpSound;
	Sound hitSound;
	Sound deathSound;
	Sound pickupSound;
	Sound lifeSound;

	bool isAlive;
	bool faceRight;

	const Stats &getStats() const;
	const Collider &getCollider() const;
	const Vector2f &getPosition() const;

	void setPosition(const Vector2f &pos);
	void setScale(const Vector2f &scale);
	void setOrigin(const Vector2f &origin);

	Player();
	Player(const Vector2f &size, const Vector2u &step, const Texture &texture, const Collider &col, const Stats &stats, const Vector2f &maxVelocity);

	void update(TileMap &tileMap, float deltaTime);
	void interactionWithMap(TileMap &tileMap, float deltaTime);
	void interactionWithItems(EntityManager<Item> &itemManager, float deltaTime);
	void interactionWithObstacles(EntityManager<Obstacle> &obstacleManager, float deltaTime);
	void interactionWithLeaves(EntityManager<Leaves> &leavesManager, float deltaTime);

	void reset(const Stats &stats);
};