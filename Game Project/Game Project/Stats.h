#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

struct Stats : public Drawable
{
private:
	const View *view;
	Text text;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	float health, score;

	Stats();
	Stats(const View *view, Text text, float health = 100, float score = 0);

	void update();
};

