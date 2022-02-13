#include "HumanLife.h"
#include "TextureManager.h"
#include "Human.h"


HumanLife::HumanLife()
{
	TextureManager::Instance().load("../Assets/textures/heart.png", "life");
	TextureManager::Instance().load("../Assets/textures/heart.png", "life2");
	TextureManager::Instance().load("../Assets/textures/heart.png", "life3");
	TextureManager::Instance().load("../Assets/textures/heart.png", "life4");

	const auto size = TextureManager::Instance().getTextureSize("life");

	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(30.0f, 30.0f);

	setHumanLife(4);

	setType(LIFE);
}

HumanLife::~HumanLife()
= default;

void HumanLife::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (getHumanLife())
	{
	case 1:
		TextureManager::Instance().draw("life", x, y, 0, 255, true);
		break;
	case 2:
		TextureManager::Instance().draw("life", x, y, 0, 255, true);
		TextureManager::Instance().draw("life2", x*2, y, 0, 255, true);
		break;
	case 3:
		TextureManager::Instance().draw("life", x, y, 0, 255, true);
		TextureManager::Instance().draw("life2", x*2, y, 0, 255, true);
		TextureManager::Instance().draw("life3", x*3, y, 0, 255, true);
		break;
	case 4:
		TextureManager::Instance().draw("life", x, y, 0, 255, true);
		TextureManager::Instance().draw("life2", x*2, y, 0, 255, true);
		TextureManager::Instance().draw("life3", x*3, y, 0, 255, true);
		TextureManager::Instance().draw("life4", x*4, y, 0, 255, true);
		break;
	}

}

void HumanLife::update()
{
	m_move();
	m_checkBounds();
}

void HumanLife::clean()
{
}

void HumanLife::m_move()
{
	getTransform()->position = getTransform()->position + getRigidBody()->velocity * 5.0f;
}

void HumanLife::m_checkBounds()
{
}

void HumanLife::m_reset()
{
}