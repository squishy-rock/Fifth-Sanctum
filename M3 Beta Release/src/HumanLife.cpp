#include "HumanLife.h"

#include <Windows.h>

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

	setHumanLife(3);

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

	hitCount++;

}

void HumanLife::clean()
{
}

void HumanLife::m_move()
{
	
}

void HumanLife::m_checkBounds()
{
}

void HumanLife::m_reset()
{
}

void HumanLife::m_hit()   // for invincible time
{
	if (hitCount++ >= maxCount)
	{
		setHumanLife(getHumanLife() - 1);
		maxCount = 180;
		hitCount = 0;
	}
}
