#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "Texture.h"
#include "SpriteRenderer.h"

class GameObject
{
public:
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture& sprite, glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
	GameObject(glm::vec2 pos, glm::vec2 size, Texture& sprite, glm::vec2 velocity, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	virtual ~GameObject();

	void moveObject(float x, float y);
	void moveObject(glm::vec2 direction);
	virtual void draw(SpriteRenderer& renderer);

	glm::vec2 getPosition();
	glm::vec2 getSize();
	glm::vec2 getVelocity();

protected:
	glm::vec2 position, size, velocity;
	glm::vec3 color;
	float rotation;
	Texture sprite;
};

