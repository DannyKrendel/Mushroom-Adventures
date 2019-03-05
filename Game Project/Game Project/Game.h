#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TileMap.h"
#include "View.h"
#include "Player.h"
#include "Collider.h"
#include "EntityManager.h"
#include "Item.h"
#include "Obstacle.h"
#include "Leaves.h"

class Game
{
private:
	RenderWindow window;
	Text text;
	Image level;
	TileMap tileMap;
	EntityManager<Item> itemManager;
	EntityManager<Obstacle> obstacleManager;
	EntityManager<Leaves> leavesManager;
	Player player;

	int lives = 2;
	int berries = 3;
	int spikes = 2;

	int currentLvl = 1;
public:
	Game();

	int loop();
	void spawnItems(EntityManager<Item> &itemManager, TileMap &tileMap, const ItemType &itemType, int amount, const Vector2f &playerPos);
	void spawnObstacles(EntityManager<Obstacle> &obstacleManager, EntityManager<Item> &itemManager, 
		TileMap &tileMap, const ObstacleType &obstacleType, int amount, const Vector2f &playerPos);
	void spawnLeaves(EntityManager<Leaves> &leavesManager, EntityManager<Obstacle> &obstacleManager, EntityManager<Item> &itemManager);
	bool loadNextLevel(int lvlNum, Image &level);
	void showGameOver(Text text, RenderWindow &window, View &view);
};