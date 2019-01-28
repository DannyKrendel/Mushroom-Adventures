#include "pch.h"
#include "Stats.h"

void Stats::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(text, states);
}

Stats::Stats()
{
}

Stats::Stats(const View &view, const Text &text, float health, float score)
{
	this->view = &view;
	this->text = text;
	this->lives = health;
	this->berriesToFind = score;
}

void Stats::update()
{
	text.setPosition(view->getCenter().x - view->getSize().x / 2 + view->getSize().x / 100, view->getCenter().y - view->getSize().y / 2 + view->getSize().y / 100);
	text.setString(String(String
	("√рибо-жизни: x" + std::to_string(int(lives)) + "\n" + "ягод осталось: " + std::to_string(int(berriesToFind)) + "\n"), std::locale("rus")));
}