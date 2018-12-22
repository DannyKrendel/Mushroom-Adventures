#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"

using namespace sf;

extern View view;

void clampView(Vector2f playerPos, TileMap tileMap);

void changeView(float deltaTime);