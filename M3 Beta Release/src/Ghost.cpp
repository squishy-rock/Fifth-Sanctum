#include "Ghost.h"
#include "TextureManager.h"


Ghost::Ghost()
{
	TextureManager::Instance().load("../Assets/textures/ghost6.png", "ghost");

	const auto size = TextureManager::Instance().getTextureSize("ghost");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(GHOST);
}

Ghost::~Ghost()
= default;

void Ghost::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Ghost
	TextureManager::Instance().draw("ghost", x, y, 0, 255, true);
}

void Ghost::update()
{
	m_move();
	m_checkBounds();
}

void Ghost::clean()
{
}

void Ghost::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void Ghost::m_checkBounds()
{
}

void Ghost::m_reset()
{
}
