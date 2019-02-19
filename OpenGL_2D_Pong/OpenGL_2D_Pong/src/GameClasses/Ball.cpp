#include "Ball.h"

Ball::Ball()
{
}

Ball::~Ball()
{
}


Ball::Ball(glm::vec2 startingPos, glm::vec2 velocity, Texture sprite) : GameObject(startingPos, BALL_SIZE, sprite, velocity)
{
}

void Ball::resetBall(glm::vec2 position, glm::vec2 velocity)
{
	this->position = position;
	this->velocity = velocity;
}

void Ball::moveBall(float deltaTime)
{
	glm::vec2 newSpeed = this->velocity * deltaTime;

	moveObject(newSpeed);

	if(position.y <= 0 || position.y >= 600 - BALL_SIZE.y)
	{
		velocity.y = -velocity.y;
	}

	if (position.x <= 0 || position.x >= 800 - BALL_SIZE.x)
	{
		velocity.x = -velocity.x;
	}
}

void Ball::reflectBall(bool reflectX)
{
	if(reflectX)
	{
		velocity.x = -velocity.x;
	}
	else
	{
		velocity.y = -velocity.y;
	}
}
