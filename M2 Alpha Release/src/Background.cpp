#include "Background.h"
#include "TextureManager.h"


Background::Background()
{
	TextureManager::Instance().load("../Assets/textures/background.jpg", "Background");

	const auto size = TextureManager::Instance().getTextureSize("Background");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(1600.0f, -800.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;
}

Background::~Background()
= default;

void Background::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Level
	TextureManager::Instance().draw("Background", x, y, 0, 255, true);
}

void Background::update()
{
	m_move();
	m_checkBounds();
}

void Background::clean()
{
}

void Background::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void Background::m_checkBounds()
{
}

void Background::m_reset()
{
}
