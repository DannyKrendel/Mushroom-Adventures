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

	// ����� ��������� ��������
	finished = false;

	// ���������� ������� ����� ������� ����������� 
	// �� ������������ ������� �������� ������� �� ���������� ������ � ���
	float switchTime = duration / float(framesCount);

	// ��� ������� ����������� �� ������ ����� update,
	// � �����, ����� ������ ����� ������������� �� ��������� ����
	if (passedTime >= switchTime)
	{
		passedTime -= switchTime;

		// ������� �� ��������� ���� ��������
		currentFrame++;

		// ���� ������ ������ ���, �������� ����������� ��� ���������� ������ � ������� �����
		if (currentFrame >= framesCount)
		{
			if (isLooping)
				currentFrame = 0;
			else
				finished = true;
		}
	}

	// ��������� ������ �������� � �������������� �������
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