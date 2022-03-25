#include "StartBackground.h"
#include "TextureManager.h"


StartBackground::StartBackground()
{
	TextureManager::Instance().load("../Assets/textures/bgtitle.png", "StartBackground");

	const auto size = TextureManager::Instance().getTextureSize("StartBackground");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(1600.0f, -800.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(START_BACKGROUND);
}

StartBackground::~StartBackground()
= default;

void StartBackground::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the StartBackground
	TextureManager::Instance().draw("StartBackground", x, y, 0, 255, true);
}

void StartBackground::update()
{
	m_move();
	m_checkBounds();
}

void StartBackground::clean()
{
}

void StartBackground::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void StartBackground::m_checkBounds()
{
}

void StartBackground::m_reset()
{
}
