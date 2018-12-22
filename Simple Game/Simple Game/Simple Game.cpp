#include "pch.h"
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "View.h"
#include "Quest.h"
#include "Player.h"

using namespace sf;

int main()
{
	srand(time(0));

	#pragma region Setup
	// Creating window and view
	RenderWindow window(VideoMode(1280, 720), "Simple Game");
	view.reset(FloatRect(0, 0, 720, 405));

	// Creating font and text
	Font font;
	font.loadFromFile("fonts/default.otf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(50);
	text.setScale(0.5f, 0.5f);
	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(2);

	// Creating tile map
	Texture tilesTexture;
	tilesTexture.loadFromFile("img/tiles.png");
	TileMap tileMap(&tilesTexture, Vector2u(23, 23), Vector2u(32, 32));

	// Creating player
	Image playerImg;
	playerImg.loadFromFile("img/player.png");
	playerImg.createMaskFromColor(Color(41, 33, 59));
	Texture playerTexture;
	playerTexture.loadFromImage(playerImg);
	Animation playerAnim(&playerTexture, Vector2u(3, 4), 0.2f);
	Stats stats(text);
	Player player(&playerTexture, playerAnim, stats);

	// Spawn in map center
	player.setPosition(Vector2f(tileMap.getMapSize().x * tileMap.getTileSize().x / 2, tileMap.getMapSize().y * tileMap.getTileSize().y / 2));

	// Creating quest
	Texture questTexture;
	questTexture.loadFromFile("img/quest background.jpg");
	text.setScale(0.37f, 0.37f);
	Quest quest(text, &questTexture);
	quest.currentQuest = 0;

	bool showStats = true;
	bool showQuest = false;

	Clock clock;
	float deltaTime = 0;
	float tileSpawnTime = 1;
	float tileSpawnTimer = 0;

	#pragma endregion

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		if (player.isAlive == false)
		{
			window.close();
		}

		#pragma region Events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Tab && showQuest == false)
					showQuest = true;
			}
			else if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Tab && showQuest == true)
					showQuest = false;
			}
		}
		#pragma endregion

		TileType randomType = static_cast<TileType>(2 + rand() % (TileType::None - 2));

		if (tileSpawnTimer >= tileSpawnTime) {
			tileMap.spawnTiles(randomType, 1);
			tileSpawnTimer = 0;
		}
		else
		{
			tileSpawnTimer += deltaTime;
		}

		player.update(deltaTime);
		player.interactionWithMap(tileMap, deltaTime);
		clampView(player.getPosition(), tileMap);

		window.clear();

		window.setView(view);
		changeView(deltaTime);

		tileMap.draw(window);
		player.draw(window, view);

		if (showQuest)
		{
			quest.draw(window, view);
		}

		window.display();
	}

	return 0;
}