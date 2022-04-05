#include "bg.h"
#include "TextureManager.h"


bg::bg()
{
	TextureManager::Instance().load("../Assets/textures/background.jpg", "bg");

	const auto size = TextureManager::Instance().getTextureSize("bg");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(1600.0f, -800.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;
}

bg::~bg()
= default;

void bg::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Level
	TextureManager::Instance().draw("bg", x, y, 0, 255, true);
}

void bg::update()
{
	m_move();
	m_checkBounds();
}

void bg::clean()
{
}

void bg::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void bg::m_checkBounds()
{
}

void bg::m_reset()
{
}