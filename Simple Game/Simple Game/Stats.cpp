#include "pch.h"
#include "Stats.h"

Stats::Stats(Text text, float health, float gold, float mana, float score)
{
	this->text = text;
	this->health = health;
	this->gold = gold;
	this->mana = mana;
	this->score = score;
}

void Stats::draw(RenderWindow &window, const View &view)
{
	text.setPosition(view.getCenter().x - view.getSize().x / 2 + view.getSize().x / 100, view.getCenter().y - view.getSize().y / 2 + view.getSize().y / 100);
	text.setString(String(String
	("Здоровье: " + std::to_string(int(health)) + "\n" +
		"Золото: " + std::to_string(int(gold)) + "\n" +
		"Мана: " + std::to_string(int(mana)) + "\n" +
		"Очки: " + std::to_string(int(score)) + "\n"), std::locale("rus")));
	window.draw(text);
}
