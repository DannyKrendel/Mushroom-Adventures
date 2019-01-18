#include "pch.h"
#include "View.h"

View view;

void clampView(Vector2f playerPos, TileMap tileMap)
{
	Vector2f tempPos(playerPos);

	if (playerPos.x < view.getSize().x / 2 - tileMap.getTileSize().x / 2)
		tempPos.x = view.getSize().x / 2 - tileMap.getTileSize().x / 2;
	if (playerPos.x > tileMap.getMapSize().x * tileMap.getTileSize().x - view.getSize().x / 2 - tileMap.getTileSize().x / 2)
		tempPos.x = tileMap.getMapSize().x * tileMap.getTileSize().x - view.getSize().x / 2 - tileMap.getTileSize().x / 2;
	if (playerPos.y < view.getSize().y / 2 - tileMap.getTileSize().y / 2)
		tempPos.y = view.getSize().y / 2 - tileMap.getTileSize().y / 2;
	if (playerPos.y > tileMap.getMapSize().y * tileMap.getTileSize().y - view.getSize().y / 2 - tileMap.getTileSize().x / 2)
		tempPos.y = tileMap.getMapSize().y * tileMap.getTileSize().y - view.getSize().y / 2 - tileMap.getTileSize().x / 2;

	view.setCenter(tempPos);
}

void changeView(float deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Subtract))
	{
		view.zoom(1 + deltaTime);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Add))
	{
		view.zoom(1 - deltaTime);
	}

	if (Keyboard::isKeyPressed(Keyboard::R))
	{
		view.reset(FloatRect(0, 0, 720, 405));
	}
}