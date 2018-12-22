#include "pch.h"
#include "Animation.h"

Animation::Animation(Texture *texture, Vector2u imgCount, float switchTime)
{
	this->imgCount = imgCount;
	this->switchTime = switchTime;
	totalTime = 0;
	currentImgIdx.x = 0;

	uvRect.width = texture->getSize().x / float(imgCount.x);
	uvRect.height = texture->getSize().y / float(imgCount.y);
}

void Animation::update(int row, float deltaTime)
{
	currentImgIdx.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImgIdx.x++;

		if (currentImgIdx.x >= imgCount.x)
		{
			currentImgIdx.x = 0;
		}
	}

	uvRect.left = currentImgIdx.x * uvRect.width;
	uvRect.top = currentImgIdx.y * uvRect.height;
}
