#include "pch.h"
#include "Game.h"

using namespace sf;
using namespace std::chrono_literals;

Game::Game()
{
	
}

int Game::loop()
{
	// Создание окна и вида
	RenderWindow window(VideoMode(1280, 720), "Game");
	view.reset(FloatRect(0, 0, 384, 216));

	// Создание шрифта и текста
	Font font;
	font.loadFromFile("resources/fonts/default.otf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(60);
	text.setScale(0.25f, 0.25f);
	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(3);

	// Создание карты тайлов
	Texture tilesTexture;
	tilesTexture.loadFromFile("resources/img/tiles.png");
	Image level;
	level.loadFromFile("resources/levels/1.png");
	TileMap tileMap(level, tilesTexture, Vector2u(32, 32), Collider(0, 0, 32, 32));

	// Создание предметов
	Texture itemTexture;
	itemTexture.loadFromFile("resources/img/items.png");
	Collider itemCol(0, 0, 32, 32);
	EntityManager<Item> itemManager(itemTexture, Vector2u(32, 32), itemCol);

	// Создание препятствий
	Texture obstacleTexture;
	obstacleTexture.loadFromFile("resources/img/obstacles.png");
	Collider obstacleCol(0, 0, 32, 32);
	EntityManager<Obstacle> obstacleManager(obstacleTexture, Vector2u(32, 32), obstacleCol);

	// Создание листьев
	Texture leavesTexture;
	leavesTexture.loadFromFile("resources/img/leaves.png");
	Collider leavesCol(0, 0, 32, 32);
	EntityManager<Leaves> leavesManager(leavesTexture, Vector2u(32, 32), leavesCol);

	// Создание игрока
	Image playerImg;
	playerImg.loadFromFile("resources/img/player.png");
	Texture playerTexture;
	playerTexture.loadFromImage(playerImg);

	Stats stats(view, text, lives, berries);

	Vector2f playerMaxVelocity = Vector2f(2.f, 2.f);
	Player player(Vector2f(32, 32), tileMap.getTileSize(), playerTexture, Collider(5, 10, 22, 22), stats, playerMaxVelocity);
	player.setScale(Vector2f(1.5f, 1.5f));

	// Музыка и звуки
	Music music;
	if (!music.openFromFile("resources/music/main.wav"))
		return -1;
	music.play();
	music.setVolume(20);
	music.setLoop(true);

	SoundBuffer jump;
	if (!jump.loadFromFile("resources/sound/jump.wav"))
		return -1;
	SoundBuffer hit;
	if (!hit.loadFromFile("resources/sound/hit.wav"))
		return -1;
	SoundBuffer death;
	if (!death.loadFromFile("resources/sound/death.wav"))
		return -1;
	SoundBuffer pickup;
	if (!pickup.loadFromFile("resources/sound/pickup.wav"))
		return -1;
	SoundBuffer life;
	if (!life.loadFromFile("resources/sound/life.wav"))
		return -1;

	Sound sound;
	sound.setVolume(8);

	sound.setBuffer(jump);
	player.jumpSound = sound;

	sound.setBuffer(hit);
	player.hitSound = sound;

	sound.setBuffer(death);
	player.deathSound = sound;

	sound.setBuffer(pickup);
	player.pickupSound = sound;

	sound.setBuffer(life);
	player.lifeSound = sound;

	// Анимации
	playerTexture.loadFromImage(playerImg, IntRect(0, 0, 32 * 4, 32));
	player.idleAnim = Animation(playerTexture, 4, true);
	playerTexture.loadFromImage(playerImg, IntRect(0, 32, 32 * 11, 32));
	player.jumpAnim = Animation(playerTexture, 11, false, 1 / playerMaxVelocity.x);
	playerTexture.loadFromImage(playerImg, IntRect(0, 32 * 2, 32 * 5, 32));
	player.attackAnim = Animation(playerTexture, 5, false);
	playerTexture.loadFromImage(playerImg, IntRect(0, 32 * 3, 32 * 4, 32));
	player.hurtAnim = Animation(playerTexture, 4, false, 0.4f);
	playerTexture.loadFromImage(playerImg, IntRect(0, 32 * 4, 32 * 9, 32));
	player.deathAnim = Animation(playerTexture, 9, false, 1.5f);

	bool showStats = true;

	Clock clock;
	float deltaTime = 0;
	float gameOverTimer = 0;

	// Спавн игрока
	player.setPosition(tileMap.getPlayerSpawnPos());

	// Спавн остального
	spawnItems(itemManager, tileMap, ItemType::Cherry, berries, player.getPosition());
	spawnItems(itemManager, tileMap, ItemType::Heart, lives, player.getPosition());
	spawnObstacles(obstacleManager, itemManager, tileMap, ObstacleType::Spikes, spikes, player.getPosition());
	spawnLeaves(leavesManager, obstacleManager, itemManager);
	

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		#pragma region Events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed ||
				(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				window.close();
		}
		#pragma endregion

		// Если игрок собрал все ягоды
		if (player.getStats().berriesToFind == 0)
		{
			if (loadNextLevel(++currentLvl, level))
			{
				// Усложнение уровней
				berries += 2;
				lives += 1;
				spikes += 2;
				// Сброс всего
				tileMap.reset(level);
				player.reset(Stats(view, text, lives, berries));
				player.setPosition(tileMap.getPlayerSpawnPos());

				itemManager.reset();
				obstacleManager.reset();
				leavesManager.reset();
				spawnItems(itemManager, tileMap, ItemType::Cherry, berries, player.getPosition());
				spawnItems(itemManager, tileMap, ItemType::Heart, lives, player.getPosition());
				spawnObstacles(obstacleManager, itemManager, tileMap, ObstacleType::Spikes, spikes, player.getPosition());
				spawnLeaves(leavesManager, obstacleManager, itemManager);
			}
			else
			{
				window.close();
			}
		}

		player.update(tileMap, deltaTime);
		clampView(player.getPosition(), tileMap);

		player.interactionWithMap(tileMap, deltaTime);
		player.interactionWithItems(itemManager, deltaTime);
		player.interactionWithObstacles(obstacleManager, deltaTime);
		player.interactionWithLeaves(leavesManager, deltaTime);

		window.clear();

		window.setView(view);
		changeView(deltaTime);

		// Отрисовка всего
		window.draw(tileMap);
		obstacleManager.draw(window);
		itemManager.draw(window);
		leavesManager.draw(window);
		window.draw(player);

		// Если персонаж умер
		if (player.isAlive == false)
		{
			if (gameOverTimer == 0)
			{
				text.setString(String("ТЫ УМЕР!", std::locale("rus")));
				text.setOutlineColor(Color::Red);
				text.scale(3, 3);
				text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
				text.setPosition(view.getCenter().x - view.getSize().x / 2 + view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2 + view.getSize().y / 2);
			}
			window.draw(text);

			if (gameOverTimer >= 3)
				window.close();
			else
				gameOverTimer += deltaTime;
		}

		window.display();
	}
}

void Game::spawnItems(EntityManager<Item> &itemManager, TileMap &tileMap, const ItemType &itemType, int amount, const Vector2f &playerPos)
{
	Vector2f randomPos;

	do
	{
		while (true)
		{
			randomPos.x = (1 + rand() % (tileMap.getMapSize().x - 2)) * tileMap.getTileSize().x;
			randomPos.y = (1 + rand() % (tileMap.getMapSize().y - 2)) * tileMap.getTileSize().y;

			Tile *t = tileMap.find(randomPos);
			if (randomPos != playerPos && t != NULL && t->getType() == TileType::Ground && itemManager.find(randomPos) == NULL)
				break;
		}

		Item newItem(itemType, itemManager.getTexture(), itemManager.getSize(), itemManager.getCollider());
		newItem.setPosition(randomPos);

		itemManager.push(newItem);
	} while (--amount != 0);
}

void Game::spawnObstacles(EntityManager<Obstacle> &obstacleManager, EntityManager<Item> &itemManager, TileMap &tileMap, const ObstacleType &obstacleType, int amount, const Vector2f &playerPos)
{
	Vector2f randomPos;

	do
	{
		while (true)
		{
			randomPos.x = (1 + rand() % (tileMap.getMapSize().x - 2)) * tileMap.getTileSize().x;
			randomPos.y = (1 + rand() % (tileMap.getMapSize().y - 2)) * tileMap.getTileSize().y;

			Tile *t = tileMap.find(randomPos);
			if (randomPos != playerPos && t != NULL && t->getType() == TileType::Ground && obstacleManager.find(randomPos) == NULL && itemManager.find(randomPos) == NULL)
				break;
		}

		Obstacle newObstacle(obstacleType, obstacleManager.getTexture(), obstacleManager.getSize(), obstacleManager.getCollider());
		newObstacle.setPosition(randomPos);

		obstacleManager.push(newObstacle);
	} while (--amount != 0);
}

void Game::spawnLeaves(EntityManager<Leaves> &leavesManager, EntityManager<Obstacle> &obstacleManager, EntityManager<Item> &itemManager)
{
	Leaves newLeaves;
	std::vector<Vector2f> positions;

	for (auto &obstacle : obstacleManager.getEntities())
		positions.push_back(obstacle->getPosition());
	for (auto &item : itemManager.getEntities())
		positions.push_back(item->getPosition());

	for (auto &pos : positions)
	{
		newLeaves = Leaves(leavesManager.getTexture(), leavesManager.getSize(), leavesManager.getCollider());
		newLeaves.setOrigin(Vector2f(newLeaves.getSprite().getLocalBounds().width / 2.0f, newLeaves.getSprite().getLocalBounds().height / 2.0f));
		newLeaves.setScale(Vector2f(1.2f, 1.2f));
		newLeaves.setPosition(pos);

		int randomAngle = rand() % 4;

		switch (randomAngle)
		{
		case 0:
			newLeaves.setRotation(90.f);
			break;
		case 1:
			newLeaves.setRotation(180.f);
			break;
		case 2:
			newLeaves.setRotation(270.f);
			break;
		case 3:
			break;
		}

		leavesManager.push(newLeaves);
	}
}

bool Game::loadNextLevel(int lvlNum, Image &level)
{
	std::stringstream ss;

	ss << "resources/levels/" << lvlNum << ".png";

	return level.loadFromFile(ss.str());
}

void Game::showGameOver(Text text, RenderWindow &window, View &view)
{
	window.setActive(true);
	text.setString(String("ТЫ УМЕР!", std::locale("rus")));
	text.setOutlineColor(Color::Red);
	text.scale(3, 3);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(view.getCenter().x - view.getSize().x / 2 + view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2 + view.getSize().y / 2);
	window.draw(text);
	window.display();
	std::this_thread::sleep_for(2s);
	window.setActive(false);
}