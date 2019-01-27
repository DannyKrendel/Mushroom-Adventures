#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"

using namespace sf;

extern View view;

void clampView(const Vector2f &playerPos, const TileMap &tileMap);

void changeView(float deltaTime);