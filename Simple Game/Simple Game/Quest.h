#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

struct Quest
{
private:
	Text text;
	Sprite sprite;
public:
	Quest(Text text, Texture *texture);

	int currentQuest;
	
	void draw(RenderWindow &window, const View &view);
};