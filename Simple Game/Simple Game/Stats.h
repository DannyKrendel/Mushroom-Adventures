#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

struct Stats
{
private:
	Text text;
public:
	float health, gold, mana, score;

	Stats(Text text, float health = 100, float gold = 0, float mana = 0, float score = 0);

	void draw(RenderWindow &window, const View &view);
};

