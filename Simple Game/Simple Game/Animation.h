#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
private:
	Vector2u imgCount;
	Vector2u currentImgIdx;

	float totalTime;
	float switchTime;
public:
	Animation(Texture *texture, Vector2u imgCount, float switchTime);

	IntRect uvRect;

	void update(int row, float deltaTime);
};

