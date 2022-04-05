#include "Level.h"
#include "TextureManager.h"


Level::Level()
{
	TextureManager::Instance().load("../Assets/textures/levelDesign3.png", "Level");

	const auto size = TextureManager::Instance().getTextureSize("Level");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(1600.0f, -800.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(LEVEL);
}

Level::~Level()
= default;

void Level::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Level
	TextureManager::Instance().draw("Level", x, y, 0, 255, true);
}

void Level::update()
{
	m_move();
	m_checkBounds();
}

void Level::clean()
{
}

void Level::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void Level::m_checkBounds()
{
}

void Level::m_reset()
{
}
