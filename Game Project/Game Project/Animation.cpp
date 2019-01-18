#include "pch.h"
#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(const Texture &texture, int framesCount, bool isLooping, float duration)
{
	this->framesCount = framesCount;
	this->isLooping = isLooping;
	this->duration = duration;

	uvRect.width = texture.getSize().x / float(framesCount);
	uvRect.height = texture.getSize().y;
}

float Animation::getDuration() const
{
	return duration;
}

void Animation::setDuration(float duration)
{
	this->duration = duration;
}

bool Animation::isFinished()
{
	return finished;
}

Animation & Animation::reset()
{
	currentFrame = 0;
	finished = false;

	return *this;
}

void Animation::update(float deltaTime, bool faceRight)
{
	passedTime += deltaTime;

	// сброс состояния анимации
	finished = false;

	// промежуток времени между кадрами вычисляется 
	// по длительности текущей анимации делённой на количество кадров в ней
	float switchTime = duration / float(framesCount);

	// это условие выполняется не каждый вызов update,
	// а тогда, когда прийдёт время переключиться на следующий кадр
	if (passedTime >= switchTime)
	{
		passedTime -= switchTime;

		// переход на следующий кадр анимации
		currentFrame++;

		// если дальше кадров нет, анимация завершается или начинается заново с первого кадра
		if (currentFrame >= framesCount)
		{
			if (isLooping)
				currentFrame = 0;
			else
				finished = true;
		}
	}

	// изменение кадров анимации и отзеркаливание спрайта
	if (faceRight)
	{
		uvRect.left = currentFrame * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentFrame + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}