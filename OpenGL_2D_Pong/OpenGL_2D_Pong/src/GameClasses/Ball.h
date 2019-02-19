#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "GameClasses/GameObject.h"

static const glm::vec2 BALL_SIZE(25, 25);

class Ball : public GameObject
{
public:
	Ball();
	Ball(glm::vec2 startingPos, glm::vec2 velocity, Texture sprite);
	~Ball();

	void moveBall(float deltaTime);
	void resetBall(glm::vec2 position, glm::vec2 velocity);

	void reflectBall(bool reflectX = true);
};

