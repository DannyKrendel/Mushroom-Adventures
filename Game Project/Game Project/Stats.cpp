#include "pch.h"
#include "Stats.h"

void Stats::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(text, states);
}

Stats::Stats()
{
}

Stats::Stats(const View *view, Text text, float health, float score)
{
	this->view = view;
	this->text = text;
	this->health = health;
	this->score = score;
}

void Stats::update()
{
	text.setPosition(view->getCenter().x - view->getSize().x / 2 + view->getSize().x / 100, view->getCenter().y - view->getSize().y / 2 + view->getSize().y / 100);
	text.setString(String(String
	("Çהמנמגüו: " + std::to_string(int(health)) + "\n" + "Ñקוע: " + std::to_string(int(score)) + "\n"), std::locale("rus")));
}
