#include "pch.h"
#include "Quest.h"

Quest::Quest(Text text, Texture *texture)
{
	this->text = text;
	this->sprite.setTexture(*texture);
	sprite.setScale(0.6f, 0.6f);
}

void Quest::draw(RenderWindow & window, const View &view)
{
	String str;
	switch (currentQuest)
	{
	case 0:
		str = "\nВыживайте!";
		break;
	default:
		str = "";
		break;
	}

	sprite.setPosition(view.getCenter().x + 115, view.getCenter().y - 130);
	text.setPosition(sprite.getPosition().x + 10, sprite.getPosition().y);
	text.setString(String(str, std::locale("rus")));

	window.draw(sprite);
	window.draw(text);
}