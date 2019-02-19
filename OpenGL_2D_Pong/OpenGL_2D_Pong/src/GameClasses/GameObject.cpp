#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture& sprite, glm::vec3 color) : position(pos), size(size), velocity(glm::vec2(0.0f,0.0f)), color(color), sprite(sprite)
{
}


GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture& sprite, glm::vec2 velocity, glm::vec3 color) : position(pos), size(size), velocity(velocity), color(color), sprite(sprite)
{
}

void GameObject::draw(SpriteRenderer& renderer)
{
	renderer.drawSprite(this->sprite, this->position, this->size, this->rotation, this->color);
}

void GameObject::moveObject(float x, float y)
{
	position = glm::vec2(position.x + x, position.y + y);
}

void GameObject::moveObject(glm::vec2 direction)
{
	position += direction;
}

glm::vec2 GameObject::getPosition()
{
	return position;
}

glm::vec2 GameObject::getSize()
{
	return size;
}

glm::vec2 GameObject::getVelocity()
{
	return velocity;
}
