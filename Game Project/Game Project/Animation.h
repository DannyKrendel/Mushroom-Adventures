#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
private:
	int framesCount;
	int currentFrame = 0;

	float duration;
	float passedTime;

	bool isLooping;
	bool finished;
public:
	Animation();
	Animation(const Texture &texture, int framesCount, bool isLooping, float duration = 1);

	IntRect uvRect;

	float getDuration() const;
	void setDuration(float duration);

	bool isFinished();
	Animation &reset();
	void update(float deltaTime, bool faceRight);
};