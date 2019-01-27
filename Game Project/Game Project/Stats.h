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
	float lives, berriesToFind;

	Stats();
	Stats(const View &view, const Text &text, float lives, float berries);

	void update();
};